#include <conio.h>
#include <stdlib.h>
#include <stdio.h>







void main( )
{
	 const  TOT_NUM = 100;

	 FILE  *Archivo;
	 FILE  *Fuente;
	 char  NombArchivo[128] = "putw_getw.dat";
	 int   NumGen;
	 int   i,j,contcol,contnum;

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
	 contcol=0;
	 contnum=0;
	 while(!feof(Archivo))
	 {
	    contnum++;
	    NumGen = getw(Archivo);
	    if(NumGen>0)
	    {	
	    	cprintf("%4d",NumGen);
	    	contcol++;
	    	if(contcol==10 )
	    	{	
	        	cprintf("\r\n");
	    		contcol=0;
	 		}    	
	 	}    	
	 }
	 rewind(Archivo);
	 contcol=0;
	 contnum=0;
	 cprintf("Otra forma\r\n");
	 while(!feof(Archivo))
	 {
		for(i=0;i<10;i++)
		{	
			for(j=0;j<10;j++)
			{
	    	    NumGen = getw(Archivo);
	    		cprintf("%4d",NumGen);
	    	}    	
	    	cprintf("\r\n");
	 	}    	
	 	NumGen = getw(Archivo);//para llegar al fin de archivo
	 }
  	cprintf("cont num: %d",contnum);
 	fclose(Archivo); 	
}
     
