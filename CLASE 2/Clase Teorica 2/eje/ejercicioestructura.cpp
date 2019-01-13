/* --- TALLER DE LENGUAJES I  2015  -  Trabajo Practico Nro 02 --- */


#include <conio.h>
#include <stdlib.h>
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
				double salario;
				fecha cumpleanios;
				fecha contrato;
				};

//------------------------------------------------------------
void main()
{
  persona Persona1;

   clrscr(); 
   strcpy(Persona1.nombre,"Sergio Guardia");
   strcpy(Persona1.direccion,"Av. Independencia 1024");
   Persona1.codigo_postal=4000;
   Persona1.cumpleanios.dia=7;
   strcpy(Persona1.cumpleanios.mes,"Febrero");
   Persona1.cumpleanios.anio=1979;



 cprintf("\r\n\r\n");

   cprintf("Nombre: %s\r\n",Persona1.nombre);
   cprintf("Direccion: %s\r\n",Persona1.nombre);
   cprintf("Cod. Postal: %d\r\n",Persona1.codigo_postal);
   cprintf("Fecha de Nacimiento: %d de %s de %d\r\n",Persona1.cumpleanios.dia,Persona1.cumpleanios.mes,Persona1.cumpleanios.anio);

}
