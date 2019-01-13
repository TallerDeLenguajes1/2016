#include <conio.h>
#include <stdlib.h>

const DIM1 = 10;
const DIM2 = 12;

typedef int TMat[DIM1][DIM2];


// -----------------------------------------------------------------
void main()
{
  TMat M;
  int *pM;
  int i,j;
pM=&M[0][0];//formas de asignar un puntero a una matriz
pM=(int*)M;//esta es otra forma
  clrscr(); highvideo(); randomize();

//CARGA MATRIZ
 for(i=0;i<DIM1*DIM2;i++)
     pM[i]=100+random(900);

//OTRA FORMA DE CARGAR LA MATRIZ
for(i=0;i<DIM1;i++){
      for(j=0;j<DIM2;j++)
      {
     // *(pM+((i*DIM2) + j))=100+random(900);
      cprintf("%4d",*(pM+((i*DIM2) + j)));
      }
      cprintf("\r\n");
 }
cprintf("\r\notra forma de cargar y mostrar una matriz\r\n\r\n");
//MUSTRA MATRIZ 
  for(i=0;i<DIM1;i++){
      for(j=0;j<DIM2;j++)
	    {
       M[i][j]=100+random(900);
       cprintf("%4d",M[i][j]);
      }
      cprintf("\r\n");
  }
  getch();
}
