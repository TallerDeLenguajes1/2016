#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void main ()
{
FILE *pf;
int i;
int leidos;
char v1[6]={"abcdef"};
char v2[6];
pf = fopen ("Datos_char.dat", "wb+");//abro el archivo de lectura y escritura
fwrite(v1,sizeof(char),3,pf);
rewind(pf);
leidos=fread(v2,sizeof(char),6,pf);
cprintf("Los datos leidos en disco son:%d\r\n",leidos);
for(i=0; i<6; i++)
cprintf("%c ",v2[i]);
fclose(pf);
}