#include <conio.h>
#include <alloc.h>
#include <string.h>
#include <process.h>
#include <stdlib.h>
const DIM = 5;
struct TRectang { 
int Ancho; 
int Largo;
       } ;
//-----------------------------
//typedef struct { 
//int Ancho; 
//int Largo;
  //     } TRectang1;

//------------------------------------------------------------
void *ReservarMemoria(int TotBytes);

void main()
{
  int i;
  TRectang Rec1;
  TRectang Rec2={5,10};//inicializacion
  TRectang ArrRec[DIM];
  TRectang *pArrRec;

  pArrRec = (TRectang *) ReservarMemoria(sizeof(TRectang)*DIM);


  clrscr(); highvideo();
    // --- ASIGNA DATOS A LAS ESTRUCTURAS -----------------
   Rec1.Ancho=6;
   Rec1.Largo=12;
 // --- MUESTRA DATOS POR PANTALLA ---------------------

   cprintf("Rec1.Ancho: %d\r\n",Rec1.Ancho);
   cprintf("Rec1.Largo: %d\r\n",Rec1.Largo);

   cprintf("Rec2.Ancho: %d\r\n",Rec2.Ancho);
   cprintf("Rec2.Largo: %d\r\n",Rec2.Largo);

   ArrRec[0].Ancho=Rec1.Ancho;
   ArrRec[0].Largo=Rec1.Largo;
   ArrRec[1].Ancho=Rec2.Ancho;
   ArrRec[1].Largo=Rec2.Largo;
 for(i=0;i<DIM;i++)

  {
    ArrRec[i].Ancho=random(100);
    ArrRec[i].Largo=random(100);
  }
  for(i=0;i<DIM;i++)
  {
    cprintf("pArrRec[%d].Ancho: %d\r\n",i,ArrRec[i].Ancho);
    cprintf("pArrRec[%d].Largo: %d\r\n",i,ArrRec[i].Largo);
  }

  for(i=0;i<DIM;i++)
  {
    pArrRec[i].Ancho=random(100);
    pArrRec[i].Largo=random(100);
  }

  for(i=0;i<DIM;i++)
  {
    cprintf("utilizando forma sub indexada pArrRec[%d].Ancho: %d\r\n",i,pArrRec[i].Ancho);
    cprintf("utilizando forma sub indexada pArrRec[%d].Largo: %d\r\n",i,pArrRec[i].Largo);
  }
    for(i=0;i<DIM;i++)
  {
    cprintf("otra forma de escribir usando aritmetica de punteros pArrRec[%d].Ancho: %d\r\n",i,(pArrRec+i)->Ancho);
    cprintf("otra forma de escribir usando aritmetica de punteros pArrRec[%d].Largo: %d\r\n",i,(pArrRec+i)->Largo);
  }
cprintf("%d",sizeof(char));

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

