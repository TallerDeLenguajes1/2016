#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define TAB 9

void gotoxy(int x, int y)
{
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);
}
void OcultarCursor()	// FUNCION PARA OCULTAR EL CURSOR
{ 
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci; // CONTROLAR LAS CARACTERISTICAS DEL CURSOR EN PANTALLA
	cci.dwSize = 50; 		 // CAMBIA LA APARIENCIA O TAMAÑO DEL CURSOR
	cci.bVisible = FALSE;	 // 
	SetConsoleCursorInfo(hCon, &cci); // PRIM PARAMETRO: IDENTIFICADOR DE CONSOLA. 
									  // SEG PARAMETRO: ESTRUCTURA DE DATOS
}
void pintar_limites()
{
	for (int i = 0; i < 79; i++)  // LIMITES HORIZONTALES
	    {
	      gotoxy(i,0); textcolor(LIGHTRED); cprintf("%c", 205);   //(desde el punto de coordenadas (x=i, y=0) hasta el punto(x=80, y=0)
	      gotoxy(i,24); textcolor(LIGHTRED); cprintf("%c", 205); //(desde el punto de coordenadas (x=i, y=25) hasta el punto(x=80, y=25)
	    }
	for (int i = 0; i < 24; ++i)  // LIMITES VERTICALES
	    {
	      gotoxy(0,i); textcolor(LIGHTRED); cprintf("%c", 186);//(desde el punto de coordenadas (x=0, y=i) hasta el punto(x=0, y=25)
	      gotoxy(79,i); textcolor(LIGHTRED); cprintf("%c", 186);//(desde el punto de coordenadas (x=80, y=i) hasta el punto(x=80, y=25)
	    }
	// ESQUINAS DEL CUADRO DE LIMITES
	gotoxy(0,0); textcolor(LIGHTRED); cprintf("%c", 201);   // ARIBBA IZQUIERDA
	gotoxy(0,24); textcolor(LIGHTRED); cprintf("%c", 200);  // ABAJO IZQUIERDA
	gotoxy(79,0); textcolor(LIGHTRED); cprintf("%c", 187);  // ARRIBA DERECHA
	gotoxy(79,24); textcolor(LIGHTRED); cprintf("%c", 205); // ABAJO DERECHA
	gotoxy(0,1); textcolor(LIGHTRED); cprintf("%c", 175);   // ARIBBA IZQUIERDA
	gotoxy(79,23); textcolor(LIGHTRED); cprintf("%c", 175);   // ARIBBA IZQUIERDA
}
void generar_laberinto()
{
	FILE *archivoEntrada=fopen("binario.dat", "rb");
	FILE *archivoSalida;
	int x = 1, y = 1;
	int paredes[24][79];
	if (archivoEntrada==NULL)
	{
		cprintf("NO SE PUDO CREAR ARCHIVO DE ENTRADA");
		fclose(archivoEntrada); getch();
	}
	bool game_over = FALSE;
	if (archivoEntrada != NULL) 
	{	//Recorremos la matriz con ceros
		for (int i = 0; i < 24; ++i) 
		{
			for (int j = 0; j < 79; ++j)
			{
				fread(&paredes[i][j],sizeof(int),1,archivoEntrada);	//Guardamos lo del archivo en el arreglo 
				printf("%d", paredes[i][j]);						//Mostramos los valores en pantalla		 
			}
			printf("\n");
		}
		fclose(archivoEntrada);
		printf("\nPRESIONE TAB PARA GUARDAR\n\n");
		while(!game_over)
		{
			if (kbhit())	// MOVIMIENTO DEL CURSOR
			{
				char tecla = getch();
				gotoxy(x,y); printf("1");
		
				if (tecla == IZQUIERDA && x > 1){ 
					x--;
					paredes[y][x]=1;			//Guardamos lo generado en la matriz paredes
				}
				if (tecla == DERECHA && x < 78){ 
					x++;
					paredes[y][x]=1;
				}
				if (tecla == ARRIBA && y > 1){
				 	y--;
				 	paredes[y][x]=1;
				}
				if (tecla == ABAJO && y+1 < 24){ 
					y++;
					paredes[y][x]=1;
				}
				if (tecla == TAB || (x==79 && y==23))
				{	
					paredes[23][78]=4;
					system("cls");
					archivoSalida=fopen("binarioSalida.dat", "wb");

					if (archivoSalida==NULL)
					{
						cprintf("NO SE PUDO CREAR ARCHIVO DE DESTINO");
						fclose(archivoSalida); 
					}
					for (int i = 0; i < 24; ++i)	//Mostramos por pantalla el laberinto generado
					{
						for (int j = 0; j < 79; ++j)
						{	
							printf("%d", paredes[i][j]);	
							fwrite(&paredes[i][j],sizeof(int),1,archivoSalida);
						}
						printf("\n");
					}
					fclose(archivoSalida);
				} 
			}
			pintar_limites();
			// Sleep(5);
		}
	}
}

int main()
{
	OcultarCursor(); 
	generar_laberinto();
	return 0;
}