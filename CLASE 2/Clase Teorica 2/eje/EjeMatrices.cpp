#include <conio.h>
#include <stdlib.h>

const DIM1 = 10;
const DIM2 = 12;

typedef int TMat[DIM1][DIM2];
//void CargarMatriz( int * );

// -----------------------------------------------------------------
void main()
{
  TMat M;
  int *pM;
  int i,j;
pM=(int*)&M[0][0];
pM=(int*)M;
  clrscr(); highvideo(); randomize();
 // CargarMatriz(&M[0][0]);
//CARGA MATRIZ
 for(i=0;i<DIM1*DIM2;i++)
     pM[i]=100+random(900);
//MUSTRA MATRIZ 
  for(i=0;i<DIM1;i++){
      for(j=0;j<DIM2;j++)
	    {
       //M[i][j]=100+random(900);
       cprintf("%4d",M[i][j]);
      }
      cprintf("\r\n");
  }
  getch();
}

// // ----------------------------------------------------------------
// void CargarMatriz(int *pM)
// {
//   int i,j;

//   for(i=0;i<DIM1*DIM2;i++)
// 	  pM[i]=100+random(900);

// }
// // ----------------------------------------------------------------