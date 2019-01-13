#include <conio.h>
#include <stdio.h>


void main()
{
  int  Fuerza = 125;
  int  Superficie = 63;
  double Presion;

  clrscr(); highvideo();

  Presion = Fuerza/Superficie;
  
  cprintf("Sin  cast Presion es:%5.2f \r\n", Presion);

  Presion = (double)Fuerza/(double)Superficie;
  
  cprintf("Con Cast Presion es:%5.2f \r\n", Presion);
  
  getch();
}

