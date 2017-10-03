#include "../lib/libgraphique.h"
#include<stdio.h>
#define H 600
#define W 800

void dessiner_verticale(Point);

int main(void)
    {
    //indispensable pour commencer
    ouvrir_fenetre(800,600);
	
		actualiser();
		int i=0;
		Point clic;
		for(i; i<5;i++)
		{
			clic=attendre_clic();
			dessiner_verticale(clic);
			actualiser();
		}
  
    
    //fin du programme
    attendre_clic() ;
    fermer_fenetre() ;
    return 0 ;
    }

void dessiner_verticale(Point p)
	{
		Point a={p.x,0}, b={p.x,H};
		dessiner_ligne(a,b,white);
	}


