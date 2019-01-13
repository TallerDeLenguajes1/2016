#include<conio.h>
#include<stdlib.h>

const DIM = 10;


// -----------------------------------------------------------

void main()
{
  char   Buff[DIM*sizeof(int)];
  int*  pBuff;
  int    i;

  clrscr(); highvideo(); randomize();

  pBuff=(int *)&Buff[0];

  // --- PRIMERA FORMA DE RECORRER UN ARREGLO ---------
 cprintf("\r\nusando puntero auxiliar\r\n"); 
  for(i=0;i<DIM;i++)
	{
  //  *(pBuff+i)=10+random(41);
 //   cprintf("%4d",*(pBuff+i));
    cprintf("%4d",*(pBuff+i)=10+random(41));
}
     cprintf("\r\nusando puntero implicito\r\n"); 
//usando puntero implicito
  for(i=0;i<DIM;i++)
  {
  //  *(pBuff+i)=10+random(41);
 //   cprintf("%4d",*(pBuff+i));
    cprintf("%4d",*((int*)	&Buff[0]+i));
} 
  cprintf("\r\nusando puntero implicito subindexado\r\n");
//usando puntero implicito subindexado
  for(i=0;i<DIM;i++)
  {
  //  *(pBuff+i)=10+random(41);
 //   cprintf("%4d",*(pBuff+i));
    cprintf("%4d",((int*)&Buff[0])[i]);
} 
  cprintf("\r\n\r\n");
  // --- SEGUNDA FORMA DE RECORRER UN ARREGLO ---------

  for(i=0;i<DIM;i++) 
      cprintf("%4d",((int *)Buff)[i]);
  cprintf("\r\n\r\n");


  // --- TERCERA FORMA DE RECORRER UN ARREGLO ---------

  for(i=0;i<DIM;i++)
      cprintf("%4d",  *(((int *)Buff)+i));

  getch();
}

