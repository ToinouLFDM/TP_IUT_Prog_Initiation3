#include "../lib/libgraphique.h"
#include<stdio.h>
#include<math.h>
#define W 800
#define H 640
#define difficulty 6
#define taille_Case 80

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
	Point path_monster(Case map[][H/taille_Case], Point monster, Point player);
	void path_monster_rec (Case map[][H/taille_Case], int tab[][H/taille_Case], int i, int j);
	int min(  int a, int b, int c, int d);
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
	m.x=5;
	m.y=5;
	map[m.x][m.y].monster=1;
	while(life)
	{
		//reinitialiser_evenements() ;
		//printf("is moving %d \n",isMoving );
		p=deplacement_player(map,p, &isMoving );
		//printf("is moving %d \n",isMoving );	
		
		
			m=path_monster(map, m, p);
		
		

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
		Point path_monster(Case map[][H/taille_Case], Point m, Point p)
		{
			int tabx1[W/taille_Case][H/taille_Case]= {0};
			int tabx2[W/taille_Case][H/taille_Case]= {0};
			int taby1[W/taille_Case][H/taille_Case]= {0};
			int taby2[W/taille_Case][H/taille_Case]= {0};
			
			printf("player %d %d \n",p.x,p.y );
			printf("monster %d %d \n",m.x,m.y );
			if (m.x<(W/taille_Case) && !map[m.x][m.y].wall_r)
			{	
				path_monster_rec(map, tabx1, m.x+1, m.y);
				//printf("path1\n" );
			}
			if (m.x>0 && !map[m.x-1][m.y].wall_r)
			{	
				path_monster_rec(map, tabx2, m.x-1, m.y);
				//printf("path2\n" );
			}
			if (m.y<(H/taille_Case) && !map[m.x][m.y].wall_b)
			{	
				path_monster_rec(map, taby1, m.x, m.y+1);
				//printf("path3\n" );
			}
			if (m.y>0 && !map[m.x][m.y-1].wall_b)
			{	
				path_monster_rec(map, taby2, m.x, m.y-1);
				//printf("path4\n" );
			}
			printf("%d %d %d %d\n", tabx1[p.x][p.y],tabx2[p.x][p.y],taby1[p.x][p.y],tabx2[p.x][p.y]);
			int mini = min(tabx1[p.x][p.y],tabx2[p.x][p.y],taby1[p.x][p.y],tabx2[p.x][p.y]);
			map[m.x][m.y].monster=0;
			graphisme_case(m.x,m.y, jaune);
			switch (mini)
			{
				case 1:
				m.x+=1;
				break;
				
				case 2:
				m.x -=1;
				break;
				
				case 3:
				m.y+=1;
				break;
				
				case 4:
				m.y-=1;
				break;
			}
			map[m.x][m.y].monster=1;
			graphisme_case(m.x,m.y, jaune);
			
			printf("monster %d %d \n",m.x,m.y );
			return m;
		}
		int min( int a, int b, int c, int d)
		{
			
			if (a<=b && a>0)
			{
				if (a<=c)
				{
					if (a<=d)
					{
						return 1;
					}		
				}
			}
			if (b<=a && b>0)
			{
				if (b<=c)
				{
					if (b<=d)
					{
						return 2;
					}		
				}
			}
			if (c<=a && c>0)
			{
				if (c<=b)
				{
					if (c<=d)
					{
						return 3;
					}		
				}
			}
			if (d<=a && d>0)
			{
				if (d<=b)
				{
					if (d<=c)
					{
						return 4;
					}		
				}
			}
			return 0;
		}
		
		void path_monster_rec (Case map[][H/taille_Case], int tab[][H/taille_Case], int i, int j)
		{
			if (i-1>=0 && !map[i-1][j].wall_r)
			{
		  	if (tab[i-1][j] == 0)
		  	{
				  tab[i-1][j]=tab[i][j]+1;
				  path_monster_rec(map, tab,i-1,j);
    		}
		  	else if (tab[i-1][j] > tab[i][j])
		  	{
				  tab[i-1][j]=tab[i][j]+1;
				  path_monster_rec(map, tab,i-1,j);
    		}
 		 	}

			if (j-1>=0 && !map[i][j-1].wall_b)
			{
				if (tab[i][j-1] == 0)
				{
				  tab[i][j-1]=tab[i][j]+1;
				  path_monster_rec(map, tab,i,j-1);
				}
				else if (tab[i][j-1] > tab[i][j])
				{
				  tab[i][j-1]=tab[i][j]+1;
					path_monster_rec(map, tab,i,j-1);
				}
			}


			if (i+1<(W/taille_Case) && !map[i][j].wall_r)
			{
				if (tab[i+1][j] == 0)
				{
					tab[i+1][j]=tab[i][j]+1;
					path_monster_rec(map, tab,i+1,j);
				}
				else if (tab[i+1][j] > tab[i][j])
				{
					tab[i+1][j]=tab[i][j]+1;
					path_monster_rec(map, tab,i+1,j);
				}
			}

			if (j+1<(H/taille_Case) && !map[i][j].wall_b)
			{
				if (tab[i][j+1] == 0)
				{
				tab[i][j+1]=tab[i][j]+1;
				path_monster_rec(map, tab,i,j+1);
				}
				else if (tab[i][j+1] > tab[i][j])
				{
					tab[i][j+1]=tab[i][j]+1;
					path_monster_rec(map, tab,i,j+1);
				}
			}
			//printf("%d ",tab[i][j]);
		}


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
