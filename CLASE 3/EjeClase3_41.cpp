#include <conio.h>
#include <stdlib.h>

typedef struct   { 	char * Voc_A[10];
		      		char * Voc_E[10];
		      		char * Voc_I[10];
		      		char * Voc_O[10];
		      		char * Voc_U[10];
		    		}TVoc;

// ----------------------------------------------------------
void main()
{
  char  T[64] = "LA ACUARELA HABIA DESAPARECIDO";
  TVoc  Voc   = { 	{ 0,0,0,0,0,0,0,0,0,0 },
		  		{ 0,0,0,0,0,0,0,0,0,0 },
		  		{ 0,0,0,0,0,0,0,0,0,0 },
		  		{ 0,0,0,0,0,0,0,0,0,0 },
		  		{ 0,0,0,0,0,0,0,0,0,0 }  };

  int i,i_A,i_E,i_I,i_O,i_U;

  clrscr(); highvideo();

  i_A=i_E=i_I=i_O=i_U=0;

  for(i=0;T[i];i++)

      switch(T[i]) {
	  case 'A' : Voc.Voc_A[i_A++]=&T[i]; break;
	  case 'E' : Voc.Voc_E[i_E++]=&T[i]; break;
	  case 'I' : Voc.Voc_I[i_I++]=&T[i]; break;
	  case 'O' : Voc.Voc_O[i_O++]=&T[i]; break;
	  case 'U' : Voc.Voc_U[i_U++]=&T[i]; break;
      }

  cprintf(" %s\r\n\r\n",T);
  cprintf(" La cadena comienza en %u\r\n\r\n",&T[0]);

  	cprintf("\r\nPosiciones de las A:");
	for(i=0;i<i_A;i++) 
	  	cprintf(" %d",Voc.Voc_A[i]-&T[0]+1);

	cprintf("\r\nPosiciones de las E:");
	for(i=0;i<i_E;i++) 
	  	cprintf(" %d",Voc.Voc_E[i]-&T[0]+1);

	cprintf("\r\nPosiciones de las I:");
	for(i=0;i<i_I;i++) 
	  	cprintf(" %d",Voc.Voc_I[i]-&T[0]+1);

	cprintf("\r\nPosiciones de las O:");
	for(i=0;i<i_O;i++) 
	  	cprintf(" %d",Voc.Voc_O[i]-&T[0]+1);

	cprintf("\r\nPosiciones de las U:");
	for(i=0;i<i_U;i++) 
	  	cprintf(" %d",Voc.Voc_U[i]-&T[0]+1);

  getch();

}
