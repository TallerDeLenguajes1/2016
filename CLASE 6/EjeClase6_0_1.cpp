#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
typedef struct persona 
{
  char Nombre[30];
  char SegundoNombre[30];
  char Apellido[30];
  int Edad;
}TPersona;

void main ()
{
FILE *pf;
int i;
int leidos;
//int v1[6]={1,3,5,7,9,11};
//int v2[6];
TPersona per2;
TPersona per1={"Sergio","Antonio","Guardia",37};
cprintf("%s\r\n",per1.Nombre);
cprintf("%s\r\n",per1.SegundoNombre);
cprintf("%s\r\n",per1.Apellido);
cprintf("%d\r\n",per1.Edad);
pf = fopen ("DatosPersonas.dat", "wb+");//abro el archivo de lectura y escritura
fwrite(&per1,sizeof(TPersona),1,pf);

rewind(pf);

leidos=fread(&per2,sizeof(TPersona),1,pf);

cprintf("Los datos leidos en disco son:%d\r\n",leidos);
//for(i=0; i<6; i++)
cprintf("%s\r\n",per2.Nombre);
cprintf("%s\r\n",per2.Apellido);
cprintf("%s\r\n",per2.SegundoNombre);
cprintf("%d\r\n",per2.Edad);
fclose(pf);
}