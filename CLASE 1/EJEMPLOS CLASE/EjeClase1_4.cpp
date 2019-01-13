#include <conio.h>
#include <stdio.h>

#include <math.h>
#include <string.h>

typedef unsigned int INT;

// ----------------------------------------------------------
void main()
{
  INT     Direcc[4] = { 0,0,0,0 };
  INT Direcc1;
  double  UnDouble  =  M_PI;
  char   *UnaCadena = "UNA CADENA CUALQUIERA";
  int     UnEntero  =  15620;
  long    UnLong    =  6128635;

  clrscr(); highvideo();
  
  Direcc1=(INT)&UnDouble;

  Direcc[0]=(INT)&UnDouble;
  Direcc[1]=(INT)UnaCadena;
  Direcc[2]=(INT)&UnEntero;
  Direcc[3]=(INT)&UnLong;

cprintf(" Un  Double = %lf \r\n",*(double *)Direcc1);
//   cprintf(" Un  Double = %lf\r\n",*((double *)Direcc[0]) );
  //cprintf(" Una Cadena = %s\r\n",     (char *)Direcc[1]  ); 
  //cprintf(" Un  Entero = %d\r\n",    *((int *)Direcc[2]) );
  //cprintf(" Un  Long   = %ld\r\n",  *((long *)Direcc[3]) );
  cprintf(" Un  Double = %lf \r\n",*(double *)Direcc[0]);
  cprintf(" Una Cadena = %u \r\n",Direcc[1]  ); 
  cprintf(" Un  Entero = %d\r\n",    *((int *)Direcc[2]) );
  cprintf(" Un  Long   = %ld\r\n",  *((long *)Direcc[3]) );

//cprintf("%d",12*sizeof(INT));
  getch();
}
// -----------------------------------------------------------
