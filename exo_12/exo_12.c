#include "../lib/libgraphique.h"
#include<stdio.h>
#include<math.h>
#define W 820
#define H 600
#define difficulty 4
#define taille_Case 20

typedef struct CASE {
	
	Couleur c;
	int player;
	int monster;
	int wall_b;
	int wall_r;
}Case;



//foncion calcul initialision
Point init_damier(Case map[][H/taille_Case]);

//fonction calcul inGame
Point deplacement_player(Case map[][H/taille_Case], Point player, int *isMoving );
void Game(Case map[][H/taille_Case], Point p, Point m);
	//fonction Pathfiniding

//fonction graphique
void init_ecran(Couleur c);
void graphisme_case(int i, int j, Couleur c);
void graphisme_wall(int i, int j, int wall_r, int wall_b);
void graphisme_damier(Case map[][H/taille_Case]);



int main(int argc, char *argv[])
{	
	// début de la session graphique
	ouvrir_fenetre(W,H);
	
	
	//initialision map
	Case map[W/taille_Case][H/taille_Case];
	Point player,monster;
	player=init_damier(map);
	graphisme_damier(map);
	
	 //Game
	 Game(map, player, monster);
	 
	
	// fin de la session graphique
  attendre_clic();
  fermer_fenetre();
	return 0;
}


//foncion calcul initialision
Point init_damier(Case map[][H/taille_Case])
{
	int i=0,j=0, count=0;
	
	while (j<(H/taille_Case))
	{
		while(i<(W/taille_Case))
		{
			
			map[i][j].c=((count%2)==0)?gray:darkgray;
			map[i][j].wall_r=(entier_aleatoire(difficulty)==1)?1:0;
			map[i][j].wall_b=(entier_aleatoire(difficulty)==1)?1:0;
			map[i][j].player=0;
			map[i][j].monster=0;
			i++;
			count+=1;
		}
		i=0;
		j++;
	}
	Point p={0,0};
	map[0][0].player=1;
	return p;
}




//fonction calcul inGame
void Game(Case map[][H/taille_Case], Point p, Point m)
{
	int life=1;
	int isMoving=0;
	while(life)
	{
		//reinitialiser_evenements() ;
		//printf("is moving %d \n",isMoving );
		p=deplacement_player(map,p, &isMoving );
		//printf("is moving %d \n",isMoving );	

		actualiser();
		
	}
}
Point deplacement_player(Case map[][H/taille_Case], Point p, int *isMoving  )
{
	int touche=0;
	
	touche = attendre_touche();
	if(touche == SDLK_DOWN && !map[p.x][p.y].wall_b && p.y<(H/taille_Case) && !*isMoving)
	{
		//*isMoving=1;
		map[p.x][p.y].player=0;
		graphisme_case(p.x,p.y, map[p.x][p.y].c);
		p.y+=1;
		map[p.x][p.y].player=1;
		graphisme_case(p.x,p.y, darkblue);
	}
	if(touche == SDLK_RIGHT && !map[p.x][p.y].wall_r && p.y<(W/taille_Case) && !*isMoving)
	{
		//*isMoving=1;
		map[p.x][p.y].player=0;
		graphisme_case(p.x,p.y, map[p.x][p.y].c);
		p.x+=1;
		map[p.x][p.y].player=1;
		graphisme_case(p.x,p.y, darkblue);
	}
	if(touche == SDLK_UP && !map[p.x][p.y-1].wall_b && p.y>0 && !*isMoving)
	{
		//*isMoving=1;
		map[p.x][p.y].player=0;
		graphisme_case(p.x,p.y, map[p.x][p.y].c);
		p.y-=1;
		map[p.x][p.y].player=1;
		graphisme_case(p.x,p.y, darkblue);
	}
	if(touche == SDLK_LEFT && !map[p.x-1][p.y].wall_r && p.y>0 && !*isMoving)
	{
		//*isMoving=1;
		map[p.x][p.y].player=0;
		graphisme_case(p.x,p.y, map[p.x][p.y].c);
		p.x-=1;
		map[p.x][p.y].player=1;
		graphisme_case(p.x,p.y, darkblue);
	}
	
	if (*isMoving)
	{
		*isMoving=0;
		attente(200);
	}
	else 
	{
		*isMoving=touche;
		//printf("is moving yolo \n" );
	}
	return p;
}
		//fonction Pathfiniding
		



//fonction graphique
void init_ecran(Couleur c)
{
	int i=0,j=0;
	while(j<H)
	{
		while(i<W)
		{
			Point p={i,j};
			changer_pixel(p,c);
			i++;
		}	
		i=0;
		j++;
	}
}
void graphisme_case(int i, int j, Couleur c)
{
	Point p={i*taille_Case,j*taille_Case};
	dessiner_rectangle(p, taille_Case-1, taille_Case-1, c);
}

void graphisme_wall(int i, int j, int wall_r, int wall_b)
{
	Point p={i*taille_Case,j*taille_Case};
	Point p2={i*taille_Case,j*taille_Case};
	p.x+= (wall_r)?taille_Case-1:0;
	p.y+= (wall_r)?0:taille_Case-1;
	p2.x+=taille_Case-1;
	p2.y+=taille_Case-1;
	printf("p1 %d %d, p2 %d %d \n",p.x,p.y,p2.x,p2.y );
	dessiner_ligne(p,p2,black);
}
 
void graphisme_damier(Case map[][H/taille_Case])
{
	int i=0, j=0;
	init_ecran(gray);
	while (j<(H/taille_Case))
	{
		while(i<(W/taille_Case))
		{
			graphisme_case(i,j,map[i][j].c);
			if(map[i][j].wall_r)
			{
				
				graphisme_wall(i,j, 1, 0);
			}
			if(map[i][j].wall_b)
			{
				
				graphisme_wall(i,j, 0, 1);
			}
			
			i++;
		}
		j++;
		i=0;
	}
	actualiser();
}
