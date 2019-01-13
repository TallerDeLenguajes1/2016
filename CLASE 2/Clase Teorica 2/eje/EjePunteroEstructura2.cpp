#include <conio.h>
#include <alloc.h>
#include <process.h>
#include <string.h>

typedef struct  {
                 	char *  Domic;
        					char *  Prov;
        					int     CP;
		      	    }TResid;

typedef struct  { 	
                    char *   Nombre;
          					int      Edad;
          					float    Peso;
          					TResid * Resid;
          		  }TDatos;

void *ReservarMemoria(int TotBytes);

// -----------------------------------------------------------
void main()
{
  TDatos *Datos;

  clrscr(); highvideo();

  // --- REALIZA RESERVAS DINAMICAS ---------------------

  Datos             = (TDatos *)ReservarMemoria(sizeof(TDatos));
  Datos->Resid      = (TResid *)ReservarMemoria(sizeof(TResid));

  Datos->Nombre      = (char *)ReservarMemoria(32);
  Datos->Resid->Domic= (char *)ReservarMemoria(32);
  Datos->Resid->Prov = (char *)ReservarMemoria(32);

  // --- ASIGNA DATOS A LAS ESTRUCTURAS -----------------

  strcpy(Datos->Nombre,"Sergio Guardia");
  Datos->Edad=37;
  Datos->Peso=85;

  strcpy(Datos->Resid->Domic,"AV. Independencia 1700");
  strcpy(Datos->Resid->Prov,"TUCUMAN");
  Datos->Resid->CP=4000;

  // --- MUESTRA DATOS POR PANTALLA ---------------------

  cprintf("NOMBRE    : %s\r\n",   Datos->Nombre);
  cprintf("EDAD      : %d\r\n",   Datos->Edad);
  cprintf("PESO      : %2.2f\r\n",Datos->Peso);

  cprintf("DOMICILIO : %s\r\n",   Datos->Resid->Domic);

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

