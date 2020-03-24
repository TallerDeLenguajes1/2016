#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

const DIM1 = 12;
const DIM2 = 10;

typedef int TMat[DIM1][DIM2];

// ------------------------------------------------------------------------------------------------------------------
void main()
{

     FILE  *pArchivo;
     char    NombArchivo[128] = "Lista_Num.dat";
     TMat   M;
     int       NumGen;
     int       i, j;

     clrscr();

     if((pArchivo=fopen(NombArchivo,"wb+"))==NULL) {
         		cprintf("NO PUDO GENERAR ARCHIVO DESTINO");
        		 getch( ); return;
     }

     for(i=0;i<DIM1*DIM2;i++) {
           		NumGen=100+random(900); 
           		putw(NumGen,pArchivo);
     }
     rewind(pArchivo);
     for(i=0;i<DIM1;i++) {
     	   for(j=0;j<DIM2;j++) {
     	   	     M[ i ][ j ] = getw(pArchivo);
     	   	     cprintf("%4d",M[ i ][ j ]);
     	   }
     	   cprintf("\r\n");
     }	
     fclose(pArchivo);
     getch();
}
