#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

// -------------------------------------------------------------------------------------------------------------------
void main()
{
	 FILE *Fuente;
	 FILE *Destino;
	 char  NombFuente [128]  = "lenguajes.png"; 
	 char  NombDestino[128]  = "lenguajes2.png";
	 char  BuffFuente [32768];
	 int   Leidos;
	 int   i;

    if((Fuente=fopen(NombFuente,"rb"))==NULL) {
    	  cprintf("ARCHIVO FUENTE NO ENCONTRADO\r\n");
    	  getch(); return;
    }

    if((Destino=fopen(NombDestino,"wb"))==NULL) {
    	  cprintf("ARCHIVO DESTINO NO ENCONTRADO\r\n");
    	  getch(); fclose(Fuente); return;
    }


    while((Leidos=fread(BuffFuente,1,32768,Fuente))!=0){
    	                fwrite(BuffFuente,1,Leidos,Destino);
                        cprintf("Bloques de bytes Leidos: %d\r\n",Leidos);
    }
    fclose(Fuente); fclose(Destino);
    cprintf("ARCHIVO REPLICADO\r\n");
}
