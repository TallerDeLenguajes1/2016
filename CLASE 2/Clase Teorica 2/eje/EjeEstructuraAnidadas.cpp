#include <conio.h>
#include <string.h>


struct fecha {
				int dia;
				char mes[15];
				int anio;
			};


struct persona {
				char nombre[30];
				char direccion[60];
				long codigo_postal;
				long dni;
				fecha cumpleanios;
				};

//------------------------------------------------------------
void main()
{
  persona Persona1;

   
  clrscr(); highvideo();
    // --- ASIGNA DATOS A LAS ESTRUCTURAS -----------------
   strcpy(Persona1.nombre,"Sergio Guardia");
   strcpy(Persona1.direccion,"Av. Independencia 1024");
   Persona1.dni=25458679;
   Persona1.codigo_postal=4000;
   Persona1.cumpleanios.dia=7;
   strcpy(Persona1.cumpleanios.mes,"Febrero");
   Persona1.cumpleanios.anio=1979;

 // --- MUESTRA DATOS POR PANTALLA ---------------------

   cprintf("Nombre: %s\r\n",Persona1.nombre);
   cprintf("DNI: %d\r\n",Persona1.dni);
   cprintf("Direccion: %s\r\n",Persona1.nombre);
   cprintf("Cod. Postal: %d\r\n",Persona1.codigo_postal);
   cprintf("Fecha de Nacimiento: %d de %s de %d\r\n",Persona1.cumpleanios.dia,Persona1.cumpleanios.mes,Persona1.cumpleanios.anio);

}
