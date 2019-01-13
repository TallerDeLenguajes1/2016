#include <conio.h>
#include <stdlib.h>

const DIM = 12;

// ----------------------------------------------------------

void main()
{
  int  V[DIM]   = { 32,18,6,45,72,4,10,25,90,14,200,37 };
  int *Ind[DIM];
  int  i,j,k;
  int *Aux;

  clrscr(); highvideo();

  // --- Todos los apuntadores a domicilios homonimos ----

  for(i=0;i<DIM;i++) 
    Ind[i]=&V[i];

  for(k=0;k<DIM-1;k++){
    for(i=0;i<(DIM-1-k);i++){
       if(*Ind[i+1]<*Ind[i]){
    	   Aux     =Ind[i];
    	   Ind[i]  =Ind[i+1];
    	   Ind[i+1]=Aux;
  	   }
    }
  }

  cprintf("arreglo \r\n");
  for(i=0;i<DIM;i++) 
    cprintf("%4d",V[i]); 
 
  cprintf("\r\narreglo ordenado\r\n");

  for(i=0;i<DIM;i++) 
    cprintf("%4d",*Ind[i]);

  getch();

}
