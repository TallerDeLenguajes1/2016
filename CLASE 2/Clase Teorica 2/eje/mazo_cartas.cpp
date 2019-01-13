#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
struct carta {
	int numero;
	char palo[7];
};

typedef carta Carta;

typedef char Palo[7];

void inicializar_mazo(Carta m[],Palo p[]);
void barajar(Carta m[]);
void imprimo(Carta m[]);

void copiar(char *a, char *b, int largo);

void barajar(Carta m[]);

void imprimir(Carta m[]);

void main ()
{
Carta mazo[48];
Palo p[4] = {"copa","oro","espada","basto"};
srand(time(NULL));
inicializar_mazo(mazo,p);
cprintf("mazo ordenado\r\n");
imprimir(mazo);
system("PAUSE");
barajar(mazo);
imprimir(mazo);
system("PAUSE");
}

void copiar(char *a, char *b, int largo)
{
int i;
for (i=0;i < largo;i++)
a[i]=b[i];
}

void inicializar_mazo(Carta m[],Palo p[])
{
int i;

for (i=0; i < 48;i++)
{
m[i].numero=(i % 12)+1;
copiar((char*)m[i].palo,(char*)p[i/12],7);
}
}

void barajar(Carta m[])
{
int i,j;
Carta temp;
for (i=0; i < 48; i++)
{
j = 1+random(47);
temp = m[i];
m[i] = m[j];
m[j] = temp;
}
}

void imprimir(Carta m[])
{
int i,j;
char c;
for (i=0; i < 48; i++)
{
printf (" %i de ", m[i].numero);
printf (" %s ", m[i].palo);
printf ("\n");
}
}