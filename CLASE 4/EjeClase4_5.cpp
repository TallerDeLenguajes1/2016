#include <conio.h>
#include <stdlib.h>
#include <alloc.h>
#include <process.h>

const DIM1 = 15;
//const DIM2 = 8;

typedef struct nodo
{
  int dim2;
  nodo * next;
}TNodo;

void *ReservarMemoria(int TotBytes);
TNodo *NuevoNodo(); 

void main( )
{
   int *M[DIM1];
   int  i,j;
   int d2;
   TNodo *start;
   TNodo *pLista;
   TNodo *aux;
  
   clrscr( ); highvideo( ); randomize( );
//CARGO LA LISTA ENLAZADA
   for(i=0;i<DIM1;i++)
    {
        if (i==0){
          start=NuevoNodo();
          start->dim2=4+random(12-4+1);
          start->next=NULL;
          pLista=start;
        }
        else{
          aux=NuevoNodo();
          aux->dim2=4+random(12-4+1);
          aux->next=NULL;
          pLista->next=aux;
          pLista=pLista->next;//ME MUEVO AL SIGUIENTE NODO
        }
    }
 pLista=start;
  while(pLista)
  {
    cprintf("%d\r\n",pLista->dim2);
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

TNodo *NuevoNodo() //devolviendo un puntero simple a estructura
{
  TNodo *p;
  p=(TNodo *)ReservarMemoria(sizeof(TNodo));
  return(p);
}

