#include "../lib/libgraphique.h"
#include<stdio.h>
#define H 600
#define W 800

void diviser_ecran();
void a_gauche(Point p);
int main(void)
    {
    //indispensable pour commencer
    ouvrir_fenetre(800,600);
		diviser_ecran();
		actualiser();
		int i=0;
		Point clic;
		for(i; i<5;i++)
		{
			clic=attendre_clic();
			a_gauche(clic);
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

void a_gauche(Point p)
	{
		if (p.x < W/2)
		{
			printf("a Gauche\n");
		}
		else
		{
			printf("a Droite\n");
		}
	}
