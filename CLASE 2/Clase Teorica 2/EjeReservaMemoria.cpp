#include <conio.h>
#include <alloc.h>
#include <string.h>
#include <process.h>
#include <stdlib.h>

const DIM = 2;


void *ReservarMemoria(int TotBytes);

void main()
{
  const DIM = 15;

int * pVect;
int      i;

	int *p;
 	p = (int *)malloc(sizeof(int));
 	*p=5;
 	cprintf("contenido de  %d\r\n",*p);
 	free(p);
 	cprintf("libero memoria %d\r\n",*p);
 	//*p=5;
 	//cprintf("libero memoria %d",*p);

pVect = (int *)ReservarMemoria(DIM*sizeof(int));

for(i=0;i<DIM;i++){ 
  pVect[i] = 100+random(900-100+1);
  cprintf("pVect[%d]: %d \r\n",i,pVect[i]);
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

