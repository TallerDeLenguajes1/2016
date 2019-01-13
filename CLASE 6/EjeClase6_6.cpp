#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <alloc.h>

typedef struct  { int   Codigo;
             	    char  Domicilio[30];
              	  float SupCub;
              	  char  Estado[16];
               	 } TDatos;

void *ReservarMemoria(int TotBytes);
// ------------------------------------------------------------------

void main()
{
  TDatos *Datos;
  FILE   *Fuente;
  FILE   *Destino;
  char    NombFuente [128] = "listado de propiedades.txt";
  char    NombDestino[128] = "listado de propiedades.bin";

  clrscr();

  Datos=(TDatos *)ReservarMemoria(sizeof(TDatos));

  if((Fuente=fopen(NombFuente,"rt"))==NULL) {
    cprintf("NO PUDO ABRIR ARCHIVO FUENTE");
    getch(); return;
  }

  if((Destino=fopen(NombDestino,"wb"))==NULL) {
     cprintf("NO PUDO CREAR ARCHIVO DESTINO"); 
     fclose(Fuente);
     getch(); return;
  }

     while(fscanf(Fuente,"%d%*[^\A-Za-z]%30c%f%*[^\A-Za-z]%s\n",&Datos->Codigo,Datos->Domicilio,&Datos->SupCub,Datos->Estado)!=EOF) 
     {
        cprintf("Codigo      : %d\r\n",Datos->Codigo);
        cprintf("Domicilio   : %s\r\n",Datos->Domicilio);
        cprintf("SupCubierta : %6.2f\r\n",Datos->SupCub);
        cprintf("Estado      : %s\r\n",Datos->Estado);
        fwrite(Datos,sizeof(TDatos),1,Destino);
        cprintf("-------------------------------------\r\n");
        getch();
     }
     fclose(Fuente); 
     fclose(Destino); 
     getch();
}                        

void *ReservarMemoria(int TotBytes)
{
void *pAux;
  
  if((pAux=malloc(TotBytes))==NULL) {
    cprintf("No pudo reservar memoria dinámica");
    getch( ); exit(1);
  }
  return(pAux);
}