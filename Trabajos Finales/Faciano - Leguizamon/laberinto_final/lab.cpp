#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
 
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define PARED 219

FILE *archivoEntrada=fopen("binarioSalida.dat", "rb");
int codigo;
int maxCol;
bool flag=true;
char caracter;

int m[25][80]; // Matriz que guarda los datos del archivo. El maximo del laberinto son 25 filas por 80 columnas. 
                 //Se puede modificar
int f=25,c=80; // filas y columnas del laberinto
int fp=1,cp=1; // coordenadas del jugador
int fs,cs; // coordenadas de la salida o meta
int arriba, abajo, izquierda, derecha; // Aqui guardamos la informacion de la matriz de las 


void gotoxy(int x, int y)
{
  HANDLE hCon;
  hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD dwPos;
  dwPos.X = x;
  dwPos.Y = y;

  SetConsoleCursorPosition(hCon, dwPos);
}

void OcultarCursor()  // FUNCION PARA OCULTAR EL CURSOR
{ 
  HANDLE hCon;
  hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cci; // CONTROLAR LAS CARACTERISTICAS DEL CURSOR EN PANTALLA
  cci.dwSize = 50;     // CAMBIA LA APARIENCIA O TAMAÑO DEL CURSOR
  cci.bVisible = FALSE;  // 

  SetConsoleCursorInfo(hCon, &cci); // PRIM PARAMETRO: IDENTIFICADOR DE CONSOLA. 
                    // SEG PARAMETRO: ESTRUCTURA DE DATOS
}                                             // cuatro direcciones junto al jugador

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

void RecorrerLaberinto()
{
  bool game_over = FALSE;
  char direccion;
  gotoxy(1,1); 
  printf("*");
  
  while(!game_over)
  {
    if (kbhit()) //Movimiento del cursor
    {
      direccion = getch();
      
      derecha=m[fp][cp+1];
      izquierda=m[fp][cp-1];
      arriba=m[fp-1][cp];
      abajo=m[fp+1][cp];

      if (direccion == DERECHA) //Obtenemos las teclas
      {
        
        if (derecha == 1) 
        { 
          if(m[fp][cp] == 0)
          {
            gotoxy(cp,fp);
            printf ("%c", PARED);
          }
          else
          {
            gotoxy(cp,fp);
            printf(" ");
          }
          cp++;
          gotoxy(cp,fp);
          printf("*"); 
        } 
        else if (derecha != 1 && derecha != 0)
        { 
          cprintf ("\n\n\nEL JUGADOR LLEGO A LA META\n");
          game_over = true;
        }
      }
      if (direccion == IZQUIERDA)
      {
        if (izquierda == 1) //Si la posicion siguiente contiene 1 avanza
        { 
          if(m[fp][cp] == 0) //Si la siguiente posicion contiene 0 no avanza
          {
            gotoxy(cp,fp);
            printf ("%c", PARED);
          }
          else
          {
            gotoxy(cp,fp);
            printf(" ");
          }
           cp--;
           gotoxy(cp,fp); 
           printf("*"); // Posicion actual del jugador
        }
         else if (izquierda != 1 && izquierda != 0) // Si no es 0 ni 1 es la meta del juego
        { 
          cprintf ("\n\n\nEL JUGADOR LLEGO A LA META\n");
          game_over = true;
        }
      }
      if (direccion == ARRIBA)
      {  
        if (arriba == 1) 
        { 
           if(m[fp][cp] == 0)
          {
            gotoxy(cp,fp);
            printf ("%c", PARED);
          }
          else
          {
            gotoxy(cp,fp);
            printf(" ");
          }
          fp--;
          gotoxy(cp,fp);
          printf("*"); 
        } 
        else if (arriba != 1 && arriba != 0)
        { 
          cprintf ("\n\n\nEL JUGADOR LLEGO A LA META\n");
          game_over = true;
        }
      }
      if (direccion == ABAJO)
      {
        if (abajo == 1) 
        { 
           if(m[fp][cp] == 0)
          {
            gotoxy(cp,fp);
            printf ("%c", PARED);
          }
          else
          {
            gotoxy(cp,fp);
            printf(" ");
          }
          fp++; 
          gotoxy(cp,fp);
          printf("*");
        }
        else if (abajo != 1 && abajo != 0)
        { 
          cprintf ("\n\n\nEL JUGADOR LLEGO A LA META\n");
          game_over = true;
        } 
      }
    }
  } 
}

void leer_archivo()
{
  if (archivoEntrada==NULL)
  {
    cprintf("NO SE PUDO CREAR ARCHIVO DE ENTRADA");
    fclose(archivoEntrada);
    system("pause");
    exit (EXIT_FAILURE); // Terminacion del programa por falla
  }
  else
  {
    while(!feof(archivoEntrada)) 
    { // Este ciclo sirve para dimensionar nuestra matriz
      for (int i = 0; i < 24; ++i)
      {
        for (int j = 0; j < 79; ++j)
        {
          fread(&m[i][j],sizeof(int),1,archivoEntrada);
          if(m[i][j] == 0)
          {
            printf ("%c", PARED);
          }
          else
          {
            printf(" ");  
          }
          
        }
        printf("\n");
      }
      caracter=fgetc(archivoEntrada);
      codigo = caracter; // obtenemos el codigo Ascii de el caracter
    }
  } 
  pintar_limites();
  RecorrerLaberinto();

  fclose(archivoEntrada);
}

int main() 
{  
  OcultarCursor();  
  leer_archivo();
  return 0;
}