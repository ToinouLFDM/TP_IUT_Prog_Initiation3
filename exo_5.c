// ***************************************************************************
// 1. directives préprocesseur
// ***************************************************************************
#include "../lib/libgraphique.h"
#include<stdio.h>
#define H 600
#define W 800

// ***************************************************************************
//2. déclarations des fonctions
// ***************************************************************************
void diviser_ecran();
void mondrian();
void dessiner_rectangle_par_coins(Point,Point, Couleur);
int min(int,int);
int abs(int);
// ***************************************************************************
// 3. définition fonction main
// ***************************************************************************

int main(void)
    {
    //indispensable pour commencer
    ouvrir_fenetre(W,H);


		Point clic1;
		Point clic2;
		
		int i=0;
		for(;i<5;i++)
		{
			clic1=attendre_clic();
			clic2=attendre_clic();
			dessiner_rectangle_par_coins(clic1,clic2,jaune);
			actualiser();
		}
  	
    
    //fin du programme
    attendre_clic() ;
    fermer_fenetre() ;
    return 0 ;
    }
    
// ***************************************************************************
// 4. définition autres fonctions
// ***************************************************************************
void diviser_ecran()
	{
	 	Point a={W/2,0}, b={W/2,H};
		dessiner_ligne(a,b,white);
		Point c={0,H/2}, d={W,H/2};
		dessiner_ligne(c,d,white);
		actualiser();	
	}
void mondrian(Point a, Point b)
	{
		
	}
void dessiner_rectangle_par_coins(Point a, Point b, Couleur c)
{
	Point S={min(a.x,b.x),min(a.y,b.y)};
	int hauteur=abs(b.y-a.y);
	int longueur=abs(b.x-a.x);
	dessiner_rectangle(S,longueur,hauteur,c);
}

int min(int a,int b)
{
	return (a<b)?a:b;
}
int abs(int a)
{
	return (a<0)?-a:a;
}

