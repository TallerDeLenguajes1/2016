#include <conio.h>
#include <stdlib.h>

void main()
{
  int A;  //variable
  int *pA; //puntero 
  int **ppA;//puntero doble
  
  A=5;
  cprintf("dato de A: %d\r\n",A);
  pA=&A;  
  cprintf("direccion de pA: %d, dato de *pA: %d\r\n",pA,*pA);
  
  ppA=&pA;
  cprintf("direccion de ppA:%u, dato de *ppA:%u\r\n",ppA,*ppA);
  cprintf("lo que apunta el dato de **ppA: %d \r\n",**ppA);
  
  **ppA=25;

  cprintf("variable a: %d",A);
}



