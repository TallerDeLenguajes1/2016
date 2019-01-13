/* --------- Ejemplo de clase Nro 1 ------------------------------------------------------------ */
#include <conio.h>
#include <stdio.h>

const DIM=5;

void main()
{
  
int* pInt[5];		
	
int i,a=43, b=45, c=72, d=3, e=65;	

pInt[0] = &a;		
pInt[1] = &b;		
pInt[2] = &c;		
pInt[3] = &d;		
pInt[4] = &e;	


  clrscr(); highvideo();

  for(i=0;i<DIM;i++){
  	 cprintf("Contenido del Vector: %d\r\n\r\n", pInt[i]);
  }

   for(i=0;i<DIM;i++){
  	 cprintf("Contenido de lo que apunta el Vector: %d\r\n\r\n", *pInt[i]);
  }
 }


