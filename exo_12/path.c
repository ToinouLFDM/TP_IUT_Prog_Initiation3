
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/*
################################################################################
#	appel recursivité sur les 4 case autour du player init											 #
#	comparrer la valeur de tab entre elle avec le positon du player prendre la 	 #
#	plus faible. 																																 #
#rajouter detection wall dans la recursivité donc rajouter en parametre la map #
################################################################################
*/
void print_tab(int tab [][5]);
void rec_path(int tab[][5], int i, int j);
int main()
{
  int tab[5][5]={0};
  print_tab(tab);
  printf("\n\n\n");
  rec_path(tab,0,0);
  print_tab(tab);
}

void print_tab(int tab[][5]){
  for (int i = 0 ; i<5;i++){
    for (int j = 0 ; j <5;j++)
      printf("%d ",tab[i][j]);
    printf("\n");
  }
}


void rec_path(int tab[][5], int i, int j)
{
  if (i-1>=0){
    if (tab[i-1][j] == 0){
      tab[i-1][j]=tab[i][j]+1;
      rec_path(tab,i-1,j);
    }
    else if (tab[i-1][j] > tab[i][j]){
      tab[i-1][j]=tab[i][j]+1;
      rec_path(tab,i-1,j);
    }
  }

  if (j-1>=0){
    if (tab[i][j-1] == 0){
      tab[i][j-1]=tab[i][j]+1;
      rec_path(tab,i,j-1);
    }
    else if (tab[i][j-1] > tab[i][j]){
      tab[i][j-1]=tab[i][j]+1;
    rec_path(tab,i,j-1);
    }
	}


	if (i+1<5){
		if (tab[i+1][j] == 0){
		  tab[i+1][j]=tab[i][j]+1;
		  rec_path(tab,i+1,j);
		}
		else if (tab[i+1][j] > tab[i][j]){
		  tab[i+1][j]=tab[i][j]+1;
		  rec_path(tab,i+1,j);
		}
	}

	if (j+1<5){
		if (tab[i][j+1] == 0){
		  tab[i][j+1]=tab[i][j]+1;
		  rec_path(tab,i,j+1);
		}
		else if (tab[i][j+1] > tab[i][j]){
		  tab[i][j+1]=tab[i][j]+1;
		  rec_path(tab,i,j+1);
		}
	}


}
