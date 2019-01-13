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
  unsigned int * pM2;
  int i,j;

pM2=(unsigned int *)M;//esta es otra forma
  clrscr(); highvideo(); randomize();


//OTRA FORMA DE CARGAR Y MOSTRAR LA MATRIZ HACIENDO CAST
for(i=0;i<DIM1;i++){
      for(j=0;j<DIM2;j++)
      {
      *((int*)pM2+((i*DIM2) + j))=100+random(900);
      cprintf("%4d",*((int*)pM2+((i*DIM2) + j)));
      }
      cprintf("\r\n");
 }

}
