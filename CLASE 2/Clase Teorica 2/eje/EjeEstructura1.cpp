#include <conio.h>
#include <string.h>

struct TRectang { 
int Ancho; 
int Largo;
       } ;
//-----------------------------
typedef struct { 
int Ancho; 
int Largo;
       } TRectang1;

//------------------------------------------------------------
void main()
{
  TRectang Rec1;
  TRectang Rec2={5,10};//inicializacion
   
  clrscr(); highvideo();
    // --- ASIGNA DATOS A LAS ESTRUCTURAS -----------------
   Rec1.Ancho=6;
   Rec1.Largo=12;
 // --- MUESTRA DATOS POR PANTALLA ---------------------

   cprintf("Rec1.Ancho: %d\r\n",Rec1.Ancho);
   cprintf("Rec1.Largo: %d\r\n",Rec1.Largo);

   cprintf("Rec2.Ancho: %d\r\n",Rec2.Ancho);
   cprintf("Rec2.Largo: %d\r\n",Rec2.Largo);
}
