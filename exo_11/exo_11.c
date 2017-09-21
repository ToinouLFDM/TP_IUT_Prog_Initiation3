#include "../lib/libgraphique.h"
#include<stdio.h>

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
	for (i=0;i< W;i+=20)
	{
		for (j=0;j<H;j+=20)
		{
			count +=1;
			Point p={i,j};
			if((count%2)==0)
			{
				carre(p,vert);
			}
			else
			{
				carre(p,bleu);
			}
		}
	}

	int i;
	for (i=0; i<10; i++)
	{
		Point P1=attendre_clic();
		Point p1={P1.x-(P1.x%20)+1,P1.y-(P1.y%20)+1};
		Carre(p1,rouge);
		actualiser();
		Carre(p1,noir);
	}
	
	



	
  	 // fin de la session graphique
    	attendre_clic();
    	fermer_fenetre();
    	return 0;
}
void Carre(Point p1, Couleur couleur_)
	{	
		
		
		dessiner_rectangle(p1, 19, 19,couleur_);
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
