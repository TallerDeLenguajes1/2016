#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct persona 
{
  char Nombre[30];
  char SegundoNombre[30];
  char Apellido[30];
}TPersona;
// ----------------------------------------------------------------
void main()
{
  FILE *Fuente;
  TPersona Datos[4];
  char   NombFuente[128]  = "texto.txt";
  char   Linea[1024];
  int   leidos,  longitud, i;
  char buffer[1000];
  char  c;
	clrscr();

	 if((Fuente=fopen(NombFuente,"rb"))==NULL){
	      cprintf("NO PUDO ABRIR ARCHIVO FUENTE");
	      getch(); return;
	 }
	
  //leidos=fread(&Datos[0],sizeof(TPersona),sizeof(TPersona),Fuente);
  leidos = fread (buffer, 1, 30, Fuente);
  while (!feof(Fuente)){
  cprintf("%d",leidos);
  //cprintf("%s",Datos[0].Nombre);
  //cprintf("%s",Datos[0].SegundoNombre);
  buffer[30]='\0';//para que le agregue el caracter terminador de lina
  cprintf("%s\r\n",buffer);
  leidos = fread(buffer, 1, 30, Fuente);
  }            
    	
       
    
    
    
  
    fclose(Fuente);
}
