#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "f.h"

void main(){

	int i, j, **Mat, m, n, N, x, x_p, y_p, pasos, vPasos[10], mayor, **WIN;
	char **Lista, blanco[30]="                 ", TopTen[10][11], c, name[17];
	bool win=false, jugando=true;
	char player[10]; // Toma el nombre del nuevo jugador.
	clrscr();
	N=cantidadListas()-1;
	Lista=obtenerLista(N);
	
	i=33;
	j=5;
		
		textcolor(LIGHTRED);
		gotoxy(18, 1);
		cprintf(" Elija una opcion: ");
		gotoxy(20, 5);
		textcolor(LIGHTGREEN);
		cprintf(" Jugar");
		gotoxy(20, 7);
		cprintf(" Ver Top 10");
		gotoxy(33, 5);
		x=moverMenu(&i, &j, 7, 5, false);

	if(x!=5){//Si x es distinto de 5 (la posición Y de JUGAR) muestra los mejores puntajes
			clrscr();
			leerTopTen(TopTen, vPasos);
			printf("\n\n Estos son los mejores jugadores:\n");
			for (i = 0; i < 10; i++)				
				printf("\n\n\n   %s %d", TopTen[i], vPasos[i]);
			printf("\n\n Presione Enter para volver al Menu Principal");
			getchar();
			system("JugarLab.exe");
			return;
	}
	clrscr();

	printf("\n\tSeleccione el laberinto donde desea jugar\n\n\n");
	for (i = 0; i < N; i++){
		textcolor(GREEN);
		cprintf("\r\n%s%s", blanco, Lista[i]);
	}

	printf("\n\n\n\n");
	i=34; j=6; int aux=j;

	gotoxy(i, j);
	x=moverMenu(&i, &j, j-1, N+(j-1), true);
	x=x-aux;
	LeerDeCabecera(&m, &n, &x_p, &y_p, name, Lista[x]);
	Mat=asignar_matriz(m, n);
	leerMatriz(Mat, m, n, name);
	jugar(m, n, x_p, y_p, Mat, &win, jugando, &pasos);
	clrscr();
	gotoxy(0,0);

	if(win){		
		WIN=asignar_matriz(25, 80);
		leerMatriz(WIN, 25, 80, "GANASTE.dat");
		mostrarMatriz(WIN, 25, 80, true);
		
		cprintf("\n Usted ha ganado con %d pasos.", pasos);
		leerTopTen(TopTen, vPasos);

		if (pasos < vPasos[9]){
			do{
				cprintf("\r\n\n Ingrese su nombre (Desde 1 Hasta 10 caracteres alfabeticos): ");
				gets(player);
			}while(strlen(player)>9||strlen(player)<1);
			clrscr();
			guardarTopTen(TopTen, vPasos, pasos, player);
			leerTopTen(TopTen, vPasos);
			printf("\n\n Estos son los mejores jugadores:\n");
			for (i = 0; i < 9; i++)				
				printf("\n\n\n   %s %d", TopTen[i], vPasos[i]);

		}else{
			printf("\n\n Buen puntaje, esfuerzate mas para estar en el Top 10.\n");
		}
	}else{
		system("JugarLab.exe");
	}

	printf("\n\n\t Desea jugar otro laberinto?\n");
	i=25; j=35;
	gotoxy(20, 35);
	textcolor(LIGHTGREEN);
	cprintf(" Si");
	gotoxy(20, 37);
	cprintf(" No");
	gotoxy(25, 35);
	x=moverMenu(&i, &j, 37, 35, false);
	
	if (x==35){	
		clrscr();
		gotoxy(0,0);
		system("JugarLab.exe");
	}else{
		exit(0);
	}
}