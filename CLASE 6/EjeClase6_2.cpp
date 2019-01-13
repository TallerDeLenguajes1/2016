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
int leidos,escritos;
TPersona per3[10];
TPersona per2;
TPersona per1={"Sergio","Antonio","Guardia",37};
cprintf("%s\r\n",per1.Nombre);
cprintf("%s\r\n",per1.SegundoNombre);
cprintf("%s\r\n",per1.Apellido);
cprintf("%d\r\n",per1.Edad);
pf = fopen ("DatosPersonas.dat", "wb+");//abro el archivo de lectura y escritura
fwrite(&per1,sizeof(TPersona),2,pf);
per1.Edad=31;
fwrite(&per1,sizeof(TPersona),2,pf);
per1.Edad=33;
fwrite(&per1,sizeof(TPersona),1,pf);

rewind(pf);


while(!feof(pf))
{	leidos=fread(&per2,sizeof(TPersona),1,pf);
	if(leidos>0)
	{		
		cprintf("Los datos leidos en disco son:%d\r\n",leidos);
		cprintf("%d\r\n",per2.Edad);
		getch();
	}
1
getch();
rewind(pf);
leidos=fread(per3,sizeof(TPersona),5,pf);
cprintf("%d\r\n",leidos);
for(i=0;i<leidos;i++)
{	
	cprintf("%d\r\n",per3[i].Edad);
	getch();
}

escritos=fwrite(&per3,sizeof(TPersona),5,pf);
cprintf("escritos %d\r\n",escritos);
rewind(pf);
leidos=fread(per3,sizeof(TPersona),10,pf);
cprintf("%d\r\n",leidos);
for(i=0;i<leidos;i++)
{	
	cprintf("%d\r\n",per3[i].Edad);
	getch();
}
fclose(pf);
}
