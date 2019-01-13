#include <conio.h>
#include <alloc.h>
#include <string.h>
#include <process.h>


struct fecha {
				int dia;
				char mes[15];
				int anio;
			};


typedef struct {
				char nombre[30];
				char direccion[60];
				long codigo_postal;
				long dni;
				fecha cumpleanios;
				}TPersona;

//------------------------------------------------------------
void *ReservarMemoria(int TotBytes);

void main()
{
  TPersona * Persona1;

   
  clrscr(); highvideo();
   
   // --- REALIZA RESERVAS DINAMICAS ---------------------
   Persona1 = (TPersona *) ReservarMemoria(sizeof(TPersona));
   
   // --- ASIGNA DATOS A LAS ESTRUCTURAS -----------------
   strcpy(Persona1->nombre,"Sergio Guardia");
   strcpy(Persona1->direccion,"Av. Independencia 1024");
   Persona1->dni=25458679;
   Persona1->codigo_postal=4000;
   Persona1->cumpleanios.dia=7;
   strcpy(Persona1->cumpleanios.mes,"Febrero");
   Persona1->cumpleanios.anio=1979;

   // --- MUESTRA DATOS POR PANTALLA ---------------------
   cprintf("Nombre: %s\r\n",Persona1->nombre);
    cprintf("DNI: %d\r\n",Persona1->dni);
   cprintf("Direccion: %s\r\n",Persona1->direccion);
   cprintf("Cod. Postal: %d\r\n",Persona1->codigo_postal);
   cprintf("Fecha de Nacimiento: %d de %s de %d \r\n",Persona1->cumpleanios.dia,Persona1->cumpleanios.mes,Persona1->cumpleanios.anio);

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
