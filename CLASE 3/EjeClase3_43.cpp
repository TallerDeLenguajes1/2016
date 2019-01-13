#include <conio.h>
#include <stdlib.h>
#include <alloc.h>
#include <process.h>

const DIM1 = 7;
const DIM2 = 8;

void *ReservarMemoria(int TotBytes);

void main( )
{
   int *M[DIM1];
   int  i,j;

   clrscr( ); highvideo( ); randomize( );
   for(i=0;i<DIM1;i++) {
      M[i]=(int *)ReservarMemoria(DIM2*sizeof(int));
      for(j=0;j<DIM2;j++){ 
      M[i][j]=50+random(50);
      cprintf("%3d",M[i][j]);
      }
      cprintf("\r\n");

  }
}

void *ReservarMemoria(int TotBytes)
{
void *pAux;
  
  if((pAux=malloc(TotBytes))==NULL) {
    cprintf("No pudo reservar memoria dinámica");
    getch( ); exit(1);
  }
  return(pAux);
}

