#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <malloc.h> 

void *ReservarMemoria(int TotBytes);
int ** asignar_matriz(int x); // asigna la memoria de la matriz
void diagonal_matriz(int **m,int x); // carga la diagonal principal con 1
void imprimir_matriz(int **m,int x); // imprime la matriz

void main(void){
    
    int n; // dimensión de la matriz
    int i,j; // contadores
    int **matriz=NULL; // puntero doble para la matriz dinámica
    clrscr( ); highvideo( );
    cprintf("Introduce el tamanio de la matriz:");
    scanf("%d",&n);
    
    matriz=asignar_matriz(n);
    diagonal_matriz(matriz,n); // paso de la matriz a funciones
    imprimir_matriz(matriz,n); // paso de la matriz a funciones

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
// asigna la memoria de la matriz

int ** asignar_matriz(int x){
    
     int i;
     int **m;
         
     m=(int **)ReservarMemoria(x*sizeof(int *)); // se reserva memoria  para la matriz de x filas 
     //que contiene direcciones de memoria a las segundas dimensiones.
     
     for (i=0;i<x;i++){
        m[i]=(int *)ReservarMemoria(x*sizeof(int)); // se reserva memoria para las x columnas
     }

      // en memoria ya tenemos reservado espacio para una matriz de x por x --> m[x][x]
         return m; // retorno de un puntero doble
    }

// rellena de 1s la diagonal

void diagonal_matriz(int **m,int x){
     
     int i,j;
     
     for (i=0;i<x;i++)
        for (j=0;j<x;j++)
            if (i==j) 
                m[i][j]=1;
            else
                m[i][j]=0;
     
     }

// imprime la matriz

void imprimir_matriz(int **m,int x){
     
     int i,j;
     cprintf("\nIMPRIMIENDO MATRIZ\r\n");
     cprintf("\n==================\r\n");

     // manejo del puntero doble recibido como si fuese una matriz

     for (i=0;i<x;i++){
             for (j=0;j<x;j++){
             		if (i==j)
             			textcolor(LIGHTRED);//para resaltar la diagonal principal
             		else
						textcolor(WHITE);
                    cprintf("%d ",m[i][j]);
                }
             cprintf("\r\n");
    }
   
}


