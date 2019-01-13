#include <conio.h>
#include <stdio.h>


void main()
{
  int  *p1ENT;
  int  *p2ENT;
  int    ENT = 128;

  clrscr(); highvideo();

  p1ENT =&ENT;
  p2ENT =p1ENT;

  if (p1ENT==p2ENT) {
      cprintf("p1ENT y p2ENT APUNTAN A LA MISMA VARIABLE  \r\n\r\n", &ENT);  
  }

  cprintf("La direccion de la variable ENT es: %d\r\n\r\n", &ENT);

  
  cprintf("El valor del puntero p1ENT hacia ENT, es: %d\r\n\r\n", p1ENT);
  
  cprintf("El valor del puntero p2ENT hacia ENT, es: %d\r\n\r\n", p2ENT++);

  cprintf("El valor del puntero p2ENT hacia ENT++, es: %d\r\n\r\n", p2ENT);

  cprintf("El valor de la variable ENT es: %d\r\n\r\n", ENT);
  
  cprintf("El valor de lo apuntado por p1ENT es: %d\r\n\r\n", *p1ENT);
  
  *p1ENT=450;
  
  cprintf("\r\n");
  
  cprintf("El valor de la variable ENT es ahora: %d\r\n\r\n", ENT);
  
  cprintf("El valor de lo apuntado por p1ENT es ahora: %d\r\n\r\n", *p1ENT);
   
  cprintf("%d",sizeof(void *));  
  cprintf("puntero entero %d",sizeof(int *));  
  //getch();
}
