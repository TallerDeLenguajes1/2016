//Ejemplo de punteros y arrays unidimensionales
//Acceso al contenido de los elementos de un array
//Ver la direccion de memoria de cada elemento del array
//Usando indexación del array y aritmética de punteros.
#include<stdio.h>
#include<stdlib.h>
void main()
{
int numeros[5] = {5,15,30,10,35};
int *p;
char *pChar;
int i;
p=numeros;
pChar=(char*)&numeros[0];

//printf("valor d %d",*(p++));

//Accediendo a los elementos mediante indexación del array
printf("numeros[0] = %d \n", numeros[0]);
printf("numeros[1] = %d \n", numeros[1]);
printf("numeros[2] = %d \n", numeros[2]);
printf("numeros[3] = %d \n", numeros[3]);
printf("numeros[4] = %d \n\n", numeros[4]);

//Accediendo a los elementos del array mediante aritmética de punteros
printf("numeros[0] = %d \n", *p);
printf("numeros[1] = %d \n", ++(*(p++)));
printf("numeros[2] = %d \n", *(p));
printf("numeros[3] = %d \n", *(p+3));
printf("numeros[4] = %d \n\n", *(p+4));
//Accediendo a los elementos del array mediante aritmética de punteros haciendo cast

for (i=0;i<5;i++)
printf("haciendo cast numeros[%d] = %d \n",i ,*((int*)pChar+i));

system("pause");
//mediante
//aritmética de punteros subindexada
printf("numeros[0] = %d \n", p[0]);
printf("numeros[1] = %d \n", p[1]);
printf("numeros[2] = %d \n", p[2]);
printf("numeros[3] = %d \n", p[3]);
printf("numeros[4] = %d \n\n", p[4]);

//Accediendo a los elementos mediante aritmetica de punteros con el array
//numeros
printf("numeros[0] = %d \n", *numeros);
printf("numeros[1] = %d \n", *(numeros+1));
printf("numeros[2] = %d \n", *(numeros+2));
printf("numeros[3] = %d \n", *(numeros+3));
printf("numeros[4] = %d \n\n", *(numeros+4));
//El nombre del array (números) es un puntero al primer elemento del array:
//Conociendo la direccion de memoria de cada elemento del array mediante
//aritmética de punteros
//usando el nombre del arreglo como puntero
printf("La direccion de numeros[0] = %p \n", numeros);
printf("La direccion de numeros[1] = %p \n", (numeros+1));
printf("La direccion de numeros[2] = %p \n", (numeros+2));
printf("La direccion de numeros[3] = %p \n", (numeros+3));
printf("La direccion de numeros[4] = %p \n\n", (numeros+4));
//Conociendo la direccion de memoria de cada elemento del array mediante
//aritmética de punteros
printf("La direccion de numeros[0] = %p \n", p);
printf("La direccion de numeros[1] = %p \n", (p+1));
printf("La direccion de numeros[2] = %p \n", (p+2));
printf("La direccion de numeros[3] = %p \n", (p+3));
printf("La direccion de numeros[4] = %p \n\n", (p+4));
//Conociendo la direccion de memoria de cada elemento del array 

}