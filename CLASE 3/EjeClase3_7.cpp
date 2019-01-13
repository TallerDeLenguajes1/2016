/* --------- Ejemplo de clase Nro. 7--------------------------------------------------------- */
#include <conio.h>
#include <stdlib.h>
#include <alloc.h>
#include <process.h>

const   NNodos = 15;
typedef struct Nodo { 
                      int N; 
                      Nodo *Next; 
                      Nodo *Back;
                    }TNodo;

void* ReservarMemoria(int TotBytes);

void main()
{
  TNodo* Start;
  TNodo* pAux;
  TNodo* End;
   int   i;

  clrscr(); highvideo(); randomize();


  //--- GENERA LA LISTA DOBLE ENLAZADA --------------------

  for(i=0;i<NNodos;i++)
      if(i==0) {
   Start=pAux=(TNodo*)ReservarMemoria(sizeof(TNodo));
   pAux->N=50+random(50);
   pAux->Back=NULL;
   pAux->Next=NULL;
   End=pAux;
      }
      else { pAux->Next=(TNodo*)ReservarMemoria(sizeof(TNodo));
       pAux->Next->Back=pAux;
       pAux=pAux->Next;
       pAux->N=50+random(50);
       pAux->Next=NULL;
          End=pAux;
     }

  //--- MUESTRA LISTA DE IZQUIERDA A DERECHA -----------------

  for(pAux=Start;pAux;pAux=pAux->Next) 
      cprintf("%5d",pAux->N);
  
  cprintf("\r\n\r\n");

  //--- MUESTRA LISTA DE DERECHA A IZQUIERDA -----------------

  for(pAux=End;pAux;pAux=pAux->Back) 
      cprintf("%5d",pAux->N);


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

