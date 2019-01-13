#include <conio.h>
#include <alloc.h>
#include <process.h>
#include <string.h>

typedef struct  { char *  Domic;
			  char *  Prov;
			  int     CP;
			} TResid;

typedef struct {  char *   Nombre;
			  int      Edad;
			  float    Peso;
			  TResid   Resid;
		     }  TDatos;
         
void *ReservarMemoria(int TotBytes);
// ----------------------------------------------------------
void main()
{
  TDatos *Datos;

  clrscr(); highvideo();

  // --- REALIZA RESERVAS DINAMICAS ---------------------

  Datos             = (TDatos *)ReservarMemoria(sizeof(TDatos));
  Datos->Nombre     = (char   *)ReservarMemoria(32);
  Datos->Resid.Domic= (char   *)ReservarMemoria(32);
  Datos->Resid.Prov = (char   *)ReservarMemoria(32);

  // --- ASIGNA DATOS A LAS ESTRUCTURAS -----------------

  strcpy(Datos->Nombre,"JUAN PEREZ");
  Datos->Edad=56;
  Datos->Peso=105;


  strcpy(Datos->Resid.Domic,"AV. BELGRANO 1240");
  strcpy(Datos->Resid.Prov,"TUCUMAN");
  Datos->Resid.CP = 4000;

  // --- MUESTRA DATOS POR PANTALLA ---------------------

  cprintf("NOMBRE    : %s\r\n",   Datos->Nombre);
  cprintf("EDAD      : %d\r\n",   Datos->Edad);
  cprintf("PESO      : %2.2f\r\n",Datos->Peso);

  cprintf("DOMICILIO : %s\r\n",   Datos->Resid.Domic);
  cprintf("PROVINCIA : %s\r\n",   Datos->Resid.Prov);

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

