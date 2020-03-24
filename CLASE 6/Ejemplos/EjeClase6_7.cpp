#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <alloc.h>

typedef struct TDatos { 	int   Codigo;
                        		char  Domicilio[30];
                        		float SupCub;
                        		char  Estado[16];

                    		 } TDatos;

// ---------------------------------------------------------------------------------------------------------------------
void main( )
{
     TDatos *Datos;
     FILE     *Fuente;
     char       NombFuente[128]  = "listado de propiedades.bin";
     int          NroReg[4]      = { 3,10,28,0 };  // ... registros a leer aleatoriamente.
     int          i;

     clrscr( );

     if((Datos=(TDatos *)malloc(sizeof(TDatos)))==NULL){
     	   cprintf("NO PUDO RESERVAR MEMORIA DINAMICA");
     	   getch(); return;
     }

     if((Fuente=fopen(NombFuente,"rb"))==NULL) {
           cprintf("NO PUDO ABRIR ARCHIVO FUENTE");
           getch(); return;
     }
 
     for(i=0;i<4;i++) {

          fseek(Fuente,NroReg[i]*sizeof(TDatos),SEEK_SET);
          fread(Datos,sizeof(TDatos),1,Fuente);

          cprintf("Codigo      : %d\r\n",     Datos->Codigo);
          cprintf("Domicilio   : %s\r\n",     Datos->Domicilio);
          cprintf("SupCubierta : %6.2f\r\n", Datos->SupCub);
          cprintf("Estado      : %s\r\n",     Datos->Estado);
          cprintf("---------------------------------------------------------\r\n");
     }
fclose(Fuente); getch();
}                        
