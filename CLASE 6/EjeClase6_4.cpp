#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

void main( )
{
	 const  TOT_NUM = 128;

	 FILE  *Archivo;
	 FILE  *Fuente;
	 char  NombArchivo[128] = "putw_getw.dat";
	 int   NumGen;
	 int   i;

	 clrscr(); randomize();

	 if((Archivo=fopen(NombArchivo,"wb+"))==NULL) {
	    cprintf("NO PUDO GENERAR EL ARCHIVO");
	    getch( ); return;
	 }

	 for(i=0;i<TOT_NUM;i++) 
	 {
	    NumGen=100+random(900);
	    putw(NumGen,Archivo);
	 } 	   

	 rewind(Archivo);
	 while(!feof(Archivo))
	 {
	    NumGen = getw(Archivo);
	    if(NumGen>0)
	    {	
	        cprintf("%4d",NumGen);
	 	}    	
	 }
  	
 	fclose(Archivo); 	
}
     
