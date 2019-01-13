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
  TPersona Datos;
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
	
  leidos=fread(&Datos,sizeof(TPersona),1,Fuente);
  //leidos = fread (buffer, 1, 30, Fuente);
  //Datos.Nombre[30]='\n';
  //Datos.SegundoNombre[30]='\n';
  //Datos.Apellido[30]='\n';
  cprintf("%s",Datos.Nombre);
  //cprintf("%s",Datos[0].SegundoNombre);
  //cprintf("%s",Datos[0].Apellido);
  //buffer[30]='\0';//para que le agregue el caracter terminador de lina
  //cprintf("%s\r\n",buffer);
  //leidos=fread(&Datos[0],1,sizeof(TPersona),Fuente);
  //}            
    	
       
    
    
    
  
    fclose(Fuente);
}
