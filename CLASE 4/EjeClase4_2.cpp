#include <conio.h>
#include <stdlib.h>
#include <alloc.h>
#include <process.h>

const DIM1 = 7;
const DIM2 = 8;

void *ReservarMemoria(int TotBytes);
void main()
{
  int **M;
  int    i,j;

  clrscr( ); highvideo( ); randomize( );

  // --- Genera y asigna la matriz dinámica -------------------------

  M = (int **)ReservarMemoria(DIM1*sizeof(int *));
  for(i=0;i<DIM1;i++) {
	  M[ i ] = (int *)ReservarMemoria(DIM2*sizeof(int));
	  for(j=0;j<DIM2;j++) 
	  	M[ i ][ j ] = 50 + random(50);
  }

  // --- Muestra por pantalla los valores asignados ----------------

  for(i=0;i<DIM1;i++) {
	  for(j=0;j<DIM2;j++) 
	  	cprintf("%4d",M[ i ][ j ]);
	  cprintf("\r\n");
  }

  getch( );
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

