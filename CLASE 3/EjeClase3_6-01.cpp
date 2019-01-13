#include <conio.h>
#include <stdlib.h>
#include <alloc.h>
#include <process.h>

typedef struct Nodo{ 
                      int N; 
                      Nodo *Next; 
                    }TNodo;

const   NNodos = 15;

void *ReservarMemoria(int TotBytes);

// --------------------------------------------------------

void main()
{
  TNodo *Start;
  TNodo *pAux;
  int    i;

  clrscr(); highvideo(); randomize();

  // --- Generación de la lista enlazada ----------

  for(i=0;i<NNodos;i++)

      if(i==0) {
     Start=pAux=(TNodo*)ReservarMemoria(sizeof(TNodo));
     pAux->N=50+random(50);
     pAux->Next=NULL;
      }
      else {
       pAux->Next=(TNodo*)ReservarMemoria(sizeof(TNodo));
       pAux=pAux->Next;
       pAux->N=50+random(50);
       pAux->Next=NULL;
     }

  for(pAux=Start;pAux;pAux=pAux->Next) 
    cprintf("%4d",pAux->N);

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

