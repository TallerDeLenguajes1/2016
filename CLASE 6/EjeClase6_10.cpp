#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------------------------------------------------
void main()
{
	 FILE *Fuente1;
	 FILE *Fuente2;
	 char  NombFuente1[128] = "Travesura.mp3"; 
	 char  NombFuente2[128] = "Texto para lectura con diferencias.txt";
	 char  Buff1[128];
	 char  Buff2[128];
	 int     Tam1,Tam2;
	 int     Leidos;
             int     ComDeDiff = 0;
	 int     i;

    if((Fuente1=fopen(NombFuente1,"rb"))==NULL) {
    	  cprintf("ARCHIVO FUENTE 1 NO ENCONTRADO\r\n");
    	  getch(); return;
    }

    if((Fuente2=fopen(NombFuente2,"rb"))==NULL) {
    	  cprintf("ARCHIVO FUENTE 2 NO ENCONTRADO\r\n");
    	  getch(); fclose(Fuente1); return;
    }

    fseek(Fuente1,0,SEEK_END);  Tam1=ftell(Fuente1);
    fseek(Fuente2,0,SEEK_END);  Tam2=ftell(Fuente2);

    fseek(Fuente1,0,SEEK_SET);   // ... reposiciona al comienzo.
    fseek(Fuente2,0,SEEK_SET);   // ... reposiciona al comienzo.

    if(Tam1!=Tam2) {
    	  cprintf("POSEEN DISTINTOS TAMANIOS");
    	  getch(); fclose(Fuente1); fclose(Fuente2);
    	  return;
    }

    while((Leidos=fread(Buff1,1,128,Fuente1))!=0) {
    	fread(Buff2,1,128,Fuente2);
           for(i=0;i<Leidos;i++) {
                 if(Buff1[i]!=Buff2[i])  {
                      ComDeDiff+=i;
                      cprintf("Los archivos son diferentes.\r\n");
                      cprintf("Las diff se dieron a partir del byte : %d\r\n",ComDeDiff);
                      cprintf("Caracteres diferentes: %c   %c\r\n",Buff1[i],Buff2[i]);
                      getch ( ); fclose(Fuente1); fclose(Fuente2); 
                      exit(1);
                 }
     
           }  
           ComDeDiff+=Leidos; 
    }
    getch();
}
