#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void main ()
{
FILE *pf;
int i;
int leidos;
int v1[6]={1,3,5,7,9,11};
int v2[6];
pf = fopen ("Datos.dat", "wb+");//abro el archivo de lectura y escritura
fwrite(v1,sizeof(int),3,pf);
rewind(pf);
leidos=fread(v2,sizeof(int),6,pf);
cprintf("Los datos leidos en disco son:%d\r\n",leidos);
for(i=0; i<6; i++)
cprintf("%d ",v2[i]);
fclose(pf);
}