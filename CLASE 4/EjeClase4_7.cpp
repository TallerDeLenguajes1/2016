#include <conio.h>
#include <stdlib.h>
#include <alloc.h>
#include <process.h>

const DIM1 = 15;

typedef struct nodo
{
  int dato;
  nodo * next;
}TNodo;

void *ReservarMemoria(int TotBytes);
TNodo *NuevoNodo();  
TNodo *CrearNodo(TNodo **Start);

void main( )
{

   int  i,j;
   TNodo *start=NULL;
   TNodo *pLista;
   
   clrscr( ); highvideo( ); randomize( );
//CARGO LA LISTA ENLAZADA
   
  for(i=0;i<DIM1;i++)
  {
    pLista=CrearNodo(&start);
    pLista->dato=4+random(12-4+1);
  }

  pLista=start;
  while(pLista)
  {
    cprintf("%d\r\n",pLista->dato);
    pLista=pLista->next;
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

TNodo *NuevoNodo()
{
  TNodo *p;
  p=(TNodo *)ReservarMemoria(sizeof(TNodo));
  return(p);
}


TNodo *CrearNodo(TNodo **Start)
{
  TNodo *pAux;

  if(*Start==NULL) {
     *Start=NuevoNodo();
     (*Start)->next=NULL;
     return(*Start);
  }
  else {
    pAux=*Start;
   while(pAux->next){
    pAux=pAux->next; //este while es para llegar al ultimo nodo
   }

   pAux->next=NuevoNodo();//pAux->next=(TNodo *)ResMem(sizeof(TNodo));
   pAux=pAux->next;
   pAux->next=NULL;
   return(pAux);
  }
}

