#ifndef head
#define head

#include <iostream>
using namespace std;

typedef struct header{
	char nombre[30]; 	    //Nombre del mapa
	int tamX; 			    //Tamanio del mapa X
	int tamY;			    //Tamanio del mapa Y
	int inX; 			    //Pos X de inicio
	int inY; 			    //Pos Y de Inicio
	int outX; 			    //Pos X de salida
	int outY; 			    //Pos Y de salida
	float record; 		    //Record de nivel
	char recordnombre[10];  //jugador del record
}cabecera;

#endif
