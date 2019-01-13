#include <conio.h>
#include <alloc.h>
#include <string.h>
#include <process.h>
#include <stdlib.h>

const DIM = 2;
struct TRectang { 
int Ancho; 
int Largo;
       } ;

void *ReservarMemoria(int TotBytes);

void main()
{
  const DIM = 15;

char * pVect;
int      i;

pVect = (char *)ReservarMemoria(DIM*sizeof(int));

for(i=0;i<DIM;i++){ 
  ((int*)pVect)[i] = 100+random(900-100+1);
  cprintf("pVect[%d]: %d \r\n",i,((int*)pVect)[i]);
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

