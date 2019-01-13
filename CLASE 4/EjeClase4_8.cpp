#include <conio.h>

const DIM = 5;

void MostrarCadena ( char **);

// ----------------------------------------------------------

void main()
{
  char *MT[] = {"TUCUMAN"   ,
		  	"SALTA"     ,
		  	"JUJUY"     ,
		  	"CATAMARCA" ,
		  	"SANTIAGO"    };
  int    i;

  clrscr(); highvideo();

  for(i=0;i<DIM;i++) MostrarCadena(&MT[i]);

  getch();
}

// ----------------------------------------------------------

void MostrarCadena(char **Cad)
{ cprintf("%s\r\n",*Cad); }
