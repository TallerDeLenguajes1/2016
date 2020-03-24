#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct 
{
  char Nombre[100];
  char Apellido[100];
}TDatos;
// ----------------------------------------------------------------
void main()
{
  FILE *Fuente;
  TDatos Datos;
  char   NombFuente[128]  = "Texto.txt";
  char   Linea[1024];
  int     longitud, i;

	 clrscr();

	 if((Fuente=fopen(NombFuente,"rb"))==NULL){
	      cprintf("NO PUDO ABRIR ARCHIVO FUENTE");
	      getch(); return;
	 }
	
  while(fread(Datos,sizeof(TDatos),1,Fuente)!=NULL){
        //longitud=strlen(Linea);
    	   //for(i=0;i<longitud;i++) {
    	   	 //   if((Linea[i]==13) || (Linea[i]==10)){  
           //     textcolor(LIGHTRED);
           //     cprintf("%d",Linea[i]);}//para mostrar el codigo ascii correspondiente al enter
    	   	 //   else {
           //     textcolor(WHITE);
                cprintf("%s",Datos.Nombre);
                cprintf("%s",Datos.Apellido);
              
    	   
    	}
      getch();cprintf("\r\n"); 
    
    }
    
  
    fclose(Fuente);
}
