#include <conio.h>
#include <stdlib.h>

typedef unsigned int INT;
const            int DIM = 12;
const            int ESC = 27;

void main()
{
  char   Buff[DIM*sizeof(INT)];
  INT   *pENT = (INT *)&Buff[0];
  int    i;

  clrscr(); highvideo(); randomize();

  // --- Llenado del arreglo de char --------------------

  for(i=0;i<DIM-1;i++) 
    *pENT++=500+random(501);
  
  *(pENT)=(INT)(&Buff[0]);

  pENT = (INT *) (*((INT *)&Buff[44]));
  cprintf("Direcc de Buff=%u  =%u\r\n",Buff,pENT);
  if(getch()==ESC) return;

  for(pENT=(INT *)(*((INT *)&Buff[44]));;) {
      cprintf(" %d ",*pENT++);
      if(*pENT==(INT)&Buff[0]) {
	     pENT=(INT *)(*((INT *)&Buff[44]));
	     if(getch()==ESC) return; else cprintf("\r\n");
      }
  }

}
// ----------------------------------------------------------


