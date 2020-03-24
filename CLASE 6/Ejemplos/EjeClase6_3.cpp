#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const  CR = 13;
const  LF  = 10;

void main()
{
  FILE   *Destino;
  char    NombDestino[128] = "Eje6_31.txt";
  int     Codigo  = 3518;
  char    Nombre[30]= "JOSE JULIAN JUAREZ";
  float   SupCub   = 324.58;
  char    Estado[20]= "INMEJORABLE";
  char    Linea[128];
  int       i;


      clrscr();

      if((Destino=fopen(NombDestino,"rb"))==NULL) {
      	    cprintf("NO PUDO CREAR ARCHIVO DESTINO");
      	    getch(); return;
      }

     // sprintf(Linea,"%10d%30s%10.2f%20s\r\n",Codigo,Nombre,SupCub,Estado);
    
      for(i=0;i<10;i++) {      
            fread(Linea,sizeof(char),1,Destino);
            cprintf("%s",Linea);
      }      
      fclose(Destino);
      getch();
}
