#include <stdio.h> 
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "funciones.h"

int inicio(int, int, int *, int *, int **, int **);
int final (int, int, int *, int *, int **, int **);

void main(){

	clrscr();
 	int i=0, j=0, x, k, l, m, n, pasos=0;
 	FILE * AText;
 	int **Mat, *pFin, *pInicio, x_p, y_p;
 	bool win;
 	char c[3];

 	i=30;
	j=5;

		gotoxy(0, 0);
		textcolor(WHITE);
		cprintf("\n Seleccione el tamanio del laberinto que desea crear: ");
		gotoxy(20, 5);
		textcolor(LIGHTGREEN);
		cprintf(" Grande");
		gotoxy(20, 7);
		cprintf(" Pequenio");
		gotoxy(30, 5);
		x=moverMenu(&i, &j, 7, 5, false);

	if(x==7){
		m=20;n=50;
	}else{
		m=25;n=80;
	}

 	Mat=asignar_matriz(m, n);
 	genMat(Mat, m, n);
 	mostrarMatriz(Mat, m, n, false);

	pInicio = &Mat[0][1];
	pFin    = &Mat[m-1][n-2];
	*pFin=64;
	*pInicio=35;

 	i = 1; j = 1;
	x=e;
 	do{
 		textcolor(LIGHTRED);
		switch (x){
			case ti:
			case tI:x=inicio(m, n, &i, &j, Mat, &pInicio);
					gotoxy(i, j);
					mostrarMatriz(Mat, m, n, false); break;
			case s:
			case S: gotoxy(1, m);
				 	printf("\n [S] marca senderos, [R] Rellena [B] rellena todo(reset), [E] solo mueve el cursor");
 					printf("\n [I] marca el Inicio, [F] final, [G] genera el laberinto y [ESC] Salir");
 					x=senderos(m, n, &i, &j, Mat); break;
			case e:
			case E: clrscr();
					mostrarMatriz(Mat, m, n, false);
					gotoxy(1, m);
				 	printf("\n [S] marca senderos, [R] Rellena [B] rellena todo(reset), [E] solo mueve el cursor");
 					printf("\n [I] marca el Inicio, [F] final, [G] genera el laberinto y [ESC] Salir              ");
 					x=noEscribir(m, n, &i, &j); break;
			case r:
			case R: gotoxy(1, m);
				 	printf("\n [S] marca senderos, [R] Rellena [B] rellena todo(reset), [E] solo mueve el cursor");
 					printf("\n [I] marca el Inicio, [F] final, [G] genera el laberinto y [ESC] Salir             ");
 					x=reescribir(m, n, &i, &j, Mat); break;
			case b:
			case B: genMat(Mat, m, n);
					*pFin=64;
 					*pInicio=35;
 					mostrarMatriz(Mat, m, n, false);
					x=e; break;
			case f:
			case F: x=final(m, n, &i, &j, Mat, &pFin);
					gotoxy(i, j);
					mostrarMatriz(Mat, m, n, false); break;
			case g:	
			case G:	if(obtenerInicio(Mat, m, n, &x_p, &y_p)){
						jugar(m, n, x_p, y_p, Mat, &win, false, &pasos);
					}
					if(win==true){
						guardarMatriz(Mat, m, n, x_p, y_p);
						x=ESC;
					}else{
						x=e;
					}break;
			default: break;
		}
	}while( x!=ESC );

	i=15;
	j=5;

		clrscr();
		gotoxy(0, 0);
		textcolor(LIGHTRED);
		cprintf("\n Desea crear otro laberinto?: ");
		gotoxy(10, 5);
		textcolor(LIGHTGREEN);
		cprintf(" Si");
		gotoxy(10, 7);
		cprintf(" No");
		gotoxy(15, 5);
		x=moverMenu(&i, &j, 7, 5, false);
		printf("\n\n\n");

	if(x==5)
		system("genLab.exe");

}

int inicio(int m, int n, int *i, int *j, int **Mat, int **pInicio){
	int x;
	do{
		gotoxy(0, m+4);
		textcolor(GREEN);
		cprintf(" Usted esta por posicionar un Inicio (Solo contorno)                                        ");
		gotoxy(*i, *j);
		x=mover(m, n, i, j, 1);
	}while(x!=ESC && x!=Ent && x!=s && x!=S && x!=e && x!=E && x!=r && x!=R && x!=b && x!= B && x!=f && x!=F && x!=g && x!=G);

	if(x==Ent){
		if( !contorno(m, n, *i, *j) ){
			gotoxy(0, m+5);
			//cprintf(" No se puede poner un inicio aqui                                               ", *j, *i);
			gotoxy(*i, *j);
		}else{
				if(Mat[*j][*i]!=64){//Para que no se pueda superponer un Inicio y un Final
					**pInicio=1;
					Mat[*j][*i] = 35;// Escribo un numeral en la posicion de la Matriz que sera el inicio del laberinto.
					*pInicio=&Mat[*j][*i];
					gotoxy(0, m+4);
					//cprintf(" El Inicio se coloco correctamente                                   ", *j, *i);
					gotoxy(*i, *j);
					// gotoxy(0, m+4);
					// cprintf(" No se puede poner un inicio aqui, ya que hay un Final                  ", *j, *i);
					// gotoxy(*i, *j);
				}
		}
		x=e;
	}

	return x;
}

int final(int m, int n, int *i, int *j, int **Mat, int **pFin){
	int x;
	do{
		gotoxy(0, m+4);
		textcolor(GREEN);
		cprintf(" Usted esta por posicionar un Final (Solo contorno)                                          ");
		gotoxy(*i, *j);
		x=mover(m, n, i, j, 1);
	}while(x!=ESC && x!=Ent && x!=s && x!=S && x!=e && x!=E && x!=r && x!=R && x!=b && x!=B && x!=ti && x!=tI && x!=g && x!=G);

	if(x==Ent){
		if( !contorno(m, n, *i , *j) ){
			gotoxy(0, m+4);
			//cprintf(" No se puede poner un Final aqui                                                ", *j, *i);
			gotoxy(*i, *j);
		}else{
			if(Mat[*j][*i]!=35){//Para que no se pueda superponer un Inicio y un Final
				**pFin=1;
				Mat[*j][*i] = 64; // Escribo un arroba en la posicion de la Matriz que sera el inicio del laberinto.
				*pFin=&Mat[*j][*i];
				gotoxy(0, m+4);
				//cprintf(" El final se coloco correctamente                                           ", *j, *i);
				gotoxy(*i, *j);
			}

				// gotoxy(0, m+4);
				// cprintf(" No se puede poner un Final aqui, ya que hay un Inicio                      ", *j, *i);
				// gotoxy(*i, *j);
		}

		x=e;
	}

	return x;
}
