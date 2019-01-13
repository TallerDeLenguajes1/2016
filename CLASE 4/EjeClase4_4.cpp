#include <conio.h>
#include <stdlib.h>
#include <alloc.h>
#include <process.h>

const DIM1 = 7;
const DIM2 = 8;

void *ReservarMemoria(int TotBytes);
void AsignarValor(double**);

void main( )
{
   double *pDouble;

   AsignarValor(&pDouble); 
   cprintf("\r\ndireccion de pDouble:%u\r\n",&pDouble);
   cprintf("direccion de donde apunta pDouble:%u\r\n",pDouble);
   cprintf("valor asignado = %4.2lf\r\n",*pDouble);
}

void AsignarValor(double** p)
{ 
	*p = (double*)ReservarMemoria(sizeof(double));
	**p = 9812;

	cprintf("direccion de p:%u\r\n",p);
	cprintf("direccion de donde apunta p:%u\r\n",*p);
   	cprintf("valor asignado = %4.2lf\r\n",**p);
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

