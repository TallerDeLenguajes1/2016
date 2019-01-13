#include <conio.h>
#include <alloc.h>
#include <stdlib.h>
#include <process.h>

const DIM=10;

typedef struct {
			char *pENT;
			int Total;
		     }TDirecc;

typedef struct {
			int * pMax;
			int * pMin;
		     }TDatos;

void *ReservarMemoria(int TotByte);
// ----------------------------------------------------------
int main()
{
clrscr(); highvideo(); randomize();

TDirecc Direcc[DIM];
TDatos *PDatos;

int i,j,Z,N,auxMax,auxMin;

PDatos=(TDatos*)ReservarMemoria(sizeof(TDatos)*DIM);


for( i=0; i<DIM;i++ )
{
  Direcc[i].Total=N=5+random(11);
  Direcc[i].pENT=(char*)ReservarMemoria(sizeof(int)*N);
  for(j=0;j<N;j++)
  {
	do
	{
	Z=100+random(900);
	((int*)Direcc[i].pENT)[j]=Z;
	}while(((Z/10)%10)!=i);

  }
}

for( i=0; i<DIM;i++ )
{
  N=Direcc[i].Total;
  cprintf(" fila %d:",i);
  auxMax=0;
  auxMin=900;
  for(j=0;j<N;j++)
  {
     Z=((int*)Direcc[i].pENT)[j];
     cprintf("%d ",((int*)Direcc[i].pENT)[j]);
     if(Z>auxMax)
     {
	auxMax=Z;
	PDatos[i].pMax=((int*)Direcc[i].pENT)+j;
     }
     if(Z<auxMin)
     {
	auxMin=Z;
	PDatos[i].pMin=((int*)Direcc[i].pENT)+j;
     }
  }
  cprintf("\n\r");
  }
  for(i=0;i<DIM;i++)
  {
   cprintf("fila %d: max=%d min=%d\n\r ",i,*(PDatos[i].pMax),*(PDatos[i].pMin));
  //en este caso se usa esta notacion ya que en PDatos[i].pMax esta una direccion de memoria 
   //y como lo que yo quiero es su contenido le pongo el asterisco  *(PDatos[i].pMax)
  }

getch();

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