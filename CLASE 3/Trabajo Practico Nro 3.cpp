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
TNodo *NodoNuevo(); 

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
          start=NodoNuevo();
          start->dim2=4+random(12-4+1);
          start->next=NULL;
          pLista=start;
        }
        else{
          aux=NodoNuevo();
          aux->dim2=4+random(12-4+1);
          aux->next=NULL;
          pLista->next=aux;
          pLista=pLista->next;//ME MUEVO AL SIGUIENTE NODO
        }
    }
 pLista=start;
  
  for(i=0;i<DIM1;i++) {
      d2=pLista->dim2;//recorro la lista en lazada y voy dandole el valor a d2
      M[i]=(int *)ReservarMemoria(d2*sizeof(int));
      for(j=0;j<d2;j++)
      { 
        M[i][j]=50+random(50);
        cprintf("%3d",M[i][j]);
      }
      cprintf("\r\n");
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

TNodo *NodoNuevo()
{
  TNodo *Direcc;
  Direcc=(TNodo *)ReservarMemoria(sizeof(TNodo));
  return(Direcc);
}

