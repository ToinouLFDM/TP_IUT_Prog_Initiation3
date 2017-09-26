#include "../lib/libgraphique.h"
#include<stdio.h>
#include<math.h>

void Carre(Point p1, Couleur couleur_);
void quadrillage(int W,int H);
Point pathfindingMonster(Point p, Point m);
void Wall (Point p, int wall);
float yoloabs(float a);
typedef struct CASE {
	Point position;
	Couleur c;
	int valeur;
	int wall[3];
}Case;
int main(int argc, char *argv[])
{	
	// début de la session graphique
	int W=800;
	int H=600;
	ouvrir_fenetre(W,H);
    	
	//init damier
	//quadrillage(W,H);
	int i;
	int j;
	int count =0;
	Case tableau[W/20][H/20];
	
	for (i=0;i< W;i+=20)
	{
		for (j=0;j<H;j+=20)
		{
			//attribition des mur du labyrinthe
			int I;
			for (I=0; I<4;I++)
			{
				if(tableau[i/20][j/20].wall[I]>2)
				{
					tableau[i/20][j/20].wall[I]=entier_aleatoire(400)+1;
				}
			}

			
			
			count +=1;
			tableau[i/20][j/20].valeur=count;
			Point posCarre={i,j};
			tableau[i/20][j/20].position=posCarre;
			if((count%2)==0)
			{
				tableau[i/20][j/20].c=darkgray;
				Carre(posCarre,darkgray);
			}
			else
			{
				tableau[i/20][j/20].c=gray;
				Carre(posCarre,gray);
			}
			//creation des mur du labyrinthe
			
			for (I=0; I<4;I++)
			{
				//repatison des mur sur les case adjacente
				if(tableau[i/20][j/20].wall[I]==1)
				{
					if(((j/20)-1)>0 && I==0)
					{
						tableau[i/20][(j/20)-1].wall[I+2]=1;
					}
					if( ((i/20)-1)>0 && I==1)
					{
						tableau[(i/20)-1][j/20].wall[I+2]=1;
					}
					if(((j/20)+1)>0 && I==2)
					{
						tableau[i/20][(j/20)+1].wall[I-2]=1;
					}
					if( ((i/20)+1)>0 && I==3)
					{
						tableau[(i/20)+1][j/20].wall[I-2]=1;
					}
					Wall(posCarre, I);
				}
				if(tableau[i/20][j/20].wall[I]>1)
				{
					if(((j/20)-1)>0 && I==0)
					{
						tableau[i/20][(j/20)-1].wall[I+2]=2;
					}
					if( ((i/20)-1)>0 && I==1)
					{
						tableau[(i/20)-1][j/20].wall[I+2]=2;
					}
					if(((j/20)+1)>0 && I==2)
					{
						tableau[i/20][(j/20)+1].wall[I-2]=2;
					}
					if( ((i/20)+1)>0 && I==3)
					{
						tableau[(i/20)+1][j/20].wall[I-2]=2;
					}
					
				}
			}
			
		}
		count +=1;
	}
	

	int n=0;
	//init wall
	i=0;
	for(i=0;i<W;i+=20)
	{
		for (j=0;j<H;j+=20)
		{
			
			while(n<4)
			{
				//if (tableau[i/20][j/20].wall[n]==1)
				//{
					Point posWall={i,j};
					//posWall.x=i*20;
					//posWall.y=j*20;
					//Wall(posWall,n);
				//}
				n+=1;
			}
		}
	}
	actualiser();
	//init monster
	int a=entier_aleatoire(W/20);	
	int b=entier_aleatoire(H/20); 
	Point monster= {a*20,b*20};
	
	
	
	tableau[a][b].position.x=a*20;
	tableau[a][b].position.y=b*20;
	
	Carre(tableau[a][b].position,jaune);
	actualiser();
	//Initilisation 1er tour
	Point clic=attendre_clic();
	Point player={clic.x-(clic.x%20),clic.y-(clic.y%20)};
	Carre(player,rouge);
	actualiser();
	Carre(player,tableau[player.x/20][player.y/20].c);
	//boucle du jeu
	int life =1;
	while (life >=1)
	{
		int I=0;
		clic=attendre_clic();
		int a=fabs((player.x/20)-(clic.x/20)), b=fabs((player.y/20)-(clic.y/20));
		if ( a<=1 && b<=1 && a!=b  )
		//if( (yoloabs(tableau[clic.x/20][clic.y/20].position.x-player.x)<21) && (yoloabs(tableau[clic.x/20][clic.y/20].position.y-player.y)<21))
		{
			
			player.x=clic.x-(clic.x%20);
			player.y=clic.y-(clic.y%20);
			//deplacement monster
				//reinit case
			
			Carre(monster,tableau[monster.x/20][monster.y/20].c);
			for(I=0; I<4; I++)
			{
				if (tableau[monster.x/20][monster.y/20].wall[I]==1)
				{
					Wall (monster,I);
				}
				
			}
			
				//pathfinding
			monster=pathfindingMonster(player,monster);
			
			Carre(monster,jaune);
			for(I=0; I<4; I++)
			{
				if (tableau[monster.x/20][monster.y/20].wall[I]==1)
				{
					Wall (monster,I);
				}
				
			}
		}
		
		
		//depaclement joeur
		Carre(player,rouge);
		for(I=0; I<4; I++)
			{
				if (tableau[player.x/20][player.y/20].wall[I]==1)
				{
					Wall (player,I);
				}
				
			}
		actualiser();
		//Game Over
		if (player.x==monster.x && player.y==monster.y)
		{
			life=0;
		}

		Carre(player,tableau[player.x/20][player.y/20].c);
		for(I=0; I<4; I++)
			{
				if (tableau[player.x/20][player.y/20].wall[I]==1)
				{
					Wall (player,I);
				}
				
			}
	}
	
	



	
  	 // fin de la session graphique
    	attendre_clic();
    	fermer_fenetre();
    	return 0;
}

Point pathfindingMonster(Point p, Point m)
	{
	
	m.x+=((p.x-m.x)>0)?20:(((p.x-m.x)==0)?0:(-20));
	m.y+=((p.y-m.y)>0)?20:(((p.y-m.y)==0)?0:(-20));
	
	return m;
	}
float yoloabs (float a){
	if (a < 0){
		return -a;
	}
	return a;
}
void Wall (Point p, int wall)
{
	Point p2;
	Point p3;
	switch (wall)
	{
		case 0:
		p3.x=p.x;
		p3.y=p.y;
		p2.x=p.x+19;
		p2.y=p.y;
		dessiner_ligne(p2,p3,white);
		break;
	
	
		case 1:
		p3.x=p.x;
		p3.y=p.y+19;
		p2.x=p.x+19;
		p2.y=p.y+19;
		dessiner_ligne(p2,p3,white);
		break;

		case 2:
		p2.x=p.x;
		p2.y=p.y+19;
		p3.x=p.x;
		p3.y=p.y;
		dessiner_ligne(p2,p3,white);
		break;

		case 3:
		p2.x=p.x+19;
		p2.y=p.y;
		p3.x=p.x+19;
		p3.y=p.y+19;
		dessiner_ligne(p2,p3,white);
		break;
	}
	
	
	
}
void Carre(Point p1, Couleur couleur_)
	{	
		Point p2;
		p2.x= p1.x +1;
		p2.y=p1.y +1;
		dessiner_rectangle(p2, 18, 18,couleur_);
	}
void quadrillage(int W,int H)
	{
	Point p1={0,0};
	Point p2={0,H};
	int i=0;
	for(i; i<(W/20);i+=1)
		{
		p1.x+=20;
		p2.x+=20;
		dessiner_ligne(p1,p2,white);
		
		}
	actualiser();	
	i=0;
	p1.x=0;
	p1.y=0;
	p2.x=800;
	p2.y=0;
	for(i; i<(H/20);i+=1)
		{
		p1.y+=20;
		p2.y+=20;
		dessiner_ligne(p1,p2,black);
		
		}

	actualiser();
	}
