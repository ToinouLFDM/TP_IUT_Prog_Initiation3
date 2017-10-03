#include "../lib/libgraphique.h"
#include<stdio.h>
#define H 600
#define W 800

void diviser_ecran();
int a_gauche(Point p);
int main(void)
    {
    //indispensable pour commencer
    ouvrir_fenetre(W,H);
		diviser_ecran();
		actualiser();
		int i=0;
		int gauche;
		Point clic;
		for(i; i<5;i++)
		{
			clic=attendre_clic();
			gauche=a_gauche(clic);
			printf("%d \n",gauche);
		}
  	
    
    //fin du programme
    attendre_clic() ;
    fermer_fenetre() ;
    return 0 ;
    }

void diviser_ecran()
	{
		Point a={W/2,0}, b={W/2,H};
		dessiner_ligne(a,b,white);
	}

int a_gauche(Point p)
	{
		return (p.x < W/2);
		
	}

