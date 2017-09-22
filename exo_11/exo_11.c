#include "../lib/libgraphique.h"
#include<stdio.h>
#include<math.h>

void Carre(Point p1, Couleur couleur_);
void quadrillage(int W,int H);
float yoloabs(float a);
typedef struct CASE {
	Point position;
	Couleur c;
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
			count +=1;
			Point posCarre={i,j};
			tableau[i/20][j/20].position=posCarre;
			if((count%2)==0)
			{
				tableau[i/20][j/20].c=vert;
				Carre(posCarre,vert);
			}
			else
			{
				tableau[i/20][j/20].c=bleu;
				Carre(posCarre,bleu);
			}
		}
		count +=1;
	}
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
		
		clic=attendre_clic();
		//if ( (fabs(player.x-((clic.x/20)*20)) <=2) && (fabs(player.y-((clic.y/20)*20)<=2))) 
		if( (yoloabs(tableau[clic.x/20][clic.y/20].position.x-player.x)<21) && (yoloabs(tableau[clic.x/20][clic.y/20].position.y-player.y)<21))
		{
			//printf("%f,%f",fabs(player.x-(clic.x%20)),fabs(player.y-(clic.y%20)));
			player.x=clic.x-(clic.x%20);
			player.y=clic.y-(clic.y%20);
		}
		
		Carre(player,rouge);
		actualiser();
		Carre(player,tableau[player.x/20][player.y/20].c);
	}
	
	



	
  	 // fin de la session graphique
    	attendre_clic();
    	fermer_fenetre();
    	return 0;
}

float yoloabs (float a){
	if (a < 0){
		return -a;
	}
	return a;
}

void Carre(Point p1, Couleur couleur_)
	{	
		
		
		dessiner_rectangle(p1, 20, 20,couleur_);
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
		dessiner_ligne(p1,p2,white);
		
		}

	actualiser();
	}
