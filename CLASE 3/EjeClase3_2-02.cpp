#include <conio.h>
#include <stdio.h>

const DIM=4;

void main()
{
int i; 
char *err[]={
				"no puedo abrir archivo",
				"error de lectura",
				"error de escritura",
				"fallo de soporte"
};

	


  clrscr(); highvideo();

  for(i=0;i<DIM;i++){
  	 cprintf("posibles errores: %s\r\n\r\n", err[i]);// no se pone el *err ya que como es una referencia a char va con la direccion de memoria del inicio de la cadena
  }

   
 }


