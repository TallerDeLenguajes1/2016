#include <time.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

// Caracteres usados para dibujar el laberinto
	//Caracteres del laberinto
		const CAR_PARED			= 219;
		const CAR_VACIO			= 32;
		const CAR_PREMIO		= 42;
		const CAR_PUERTA		= 177;

	//Caracteres del jugador
	const CAR_JUG_CENTRO	= 197;
	const CAR_JUG_ARR		= 193;
	const CAR_JUG_AB		= 194;
	const CAR_JUG_DER		= 195;
	const CAR_JUG_IZQ		= 180;

// Constantes para detectar teclas
	const ENTER				= 13;
	const FLECHA_ARR		= 72;
	const FLECHA_AB			= 80;
	const FLECHA_DER		= 77;
	const FLECHA_IZQ		= 75;

//Tamaño en bytes de la cabecera
	const TAM_CABECERA		= 1024;

const struct PUNTO	//Es un punto en la matriz del mapa
{
	int x;			//Valor x del punto
	int y;			//Valor y del punto
} error = {-1, -1};	//Constante de invalidez

struct CELL			//Es una celda del mapa
{
	PUNTO pos;		//Punto con su posicion en la matriz
	bool wall;		//true = es pared, false = es vacio o premio
	bool visited;	//Se usa para revisar si fue generado el camino en la generacion del laberinto
	bool prize;		//true = es premio, false = es vacio
};

struct JUGADOR		//Es la representacion del jugador y el pincel en la funcion de dibujo
{
	PUNTO pos;		//Punto con su posicion en el mapa
	char caracter;	//El caracter que se muestra por pantalla
};

struct MAP			//El mapa en si
{
	CELL **cell;	//Doble puntero a celda, se usa para hacer una matriz dinamica
	int dimx;		//El tamaño en x del mapa y la matriz
	int dimy;		//El tamaño en y del mapa y la matriz
};

typedef PUNTO ITEM;	//Stack o Pila implementada con lista enlazada

struct nodo			//Nodo de lista enlazada de la Pila
{
	ITEM dato;
	nodo * next;
};

typedef nodo * PILA;//ADT PILA implementado con lista enlazada

struct header		//Estructura de la cabecera
{
	char name[20];	//Nombre del mapa
	PUNTO start;	//Punto de inicio
	PUNTO end;		//Punto del final
	int dim_x;		//Tamaño en x del mapa
	int dim_y;		//Tamaño en y del mapa
};

struct step			//Lista enlazada para guardar los pasos del jugador y usar en la replay
{
	JUGADOR p;
	step * next;
};

PUNTO new_point(int x, int y);		//Constructora del punto
bool equal_points(PUNTO a, PUNTO b);//Devuelve verdadero si los puntos son iguales

void Oculta_cursor();//Oculta el cursor, se usa durante el juego

PILA PilaVacia();				//Constructora de pila vacia
bool EsPilaVacia(PILA P);		//Test
PILA PUSH(PILA P, ITEM item);	//Constructora PILA x ITEM
ITEM TOP(PILA P);				//Devuelve el elemento del tope de la pila
PILA POP(PILA P);				//Elimina el elemento del tope

void * ReservarMemoria(int cant);	//Reserva de memoria dinamica

bool unvisited_cells(MAP mapa);						//Revisa si existe alguna celda del mapa que no haya sido visitada
PUNTO rand_choose_cell(MAP mapa, PUNTO current);	//Elige una celda adyacente al punto dado
bool exist_unvisited_neighbors(MAP mapa, PUNTO p);	//Revisa si existen celdas adyacentes a un punto dado que no hayan sido visitadas
void remove_walls(PUNTO c, PUNTO p, MAP mapa);		//Destruye la pared entre 2 celdas

MAP new_map(int x, int y);								//Inicializa el mapa
void print_unfinished_map(MAP mapa);					//Dibuja el mapa cuando esta incompleto, solo muestra paredes y vacios
void print_map(MAP mapa, PUNTO start, PUNTO end);		//Dibuja el mapa completo, con premios, entrada y salida
void generate_maze(MAP * mapa, PUNTO start, PUNTO end);	//Genera un laberinto aleatorio
void pregen_maze(char * source, MAP *maze);				//Genera un laberinto desde un string fuente
bool check_prize(CELL celda);							//Devuelve verdadero si la celda dada tiene premio

header save_header(MAP mapa, char name[20], PUNTO start, PUNTO end);	//Guarda los datos del mapa en una cabecera
void save_source(MAP mapa, char *source);								//Guarda el mapa en un string fuente

JUGADOR nuevo_jugador(PUNTO start);						//Inicializa el jugador
void dibujarjugador(JUGADOR player);					//Dibuja el caracter del jugador en su posicion
void moverjugador(JUGADOR *player, MAP mapa, int tecla);//Mueve al jugador segun la tecla que se presione

int GameLoop(JUGADOR player, PUNTO start, PUNTO end, MAP mapa, step ** L);		//Juego completo

void moverpincel(JUGADOR *player, MAP mapa, int tecla, bool prize);	//Usado en el dibujo del mapa, para mover el pincel y dibujar los espacios en blanco, paredes y premios en el mapa
MAP draw_map(int dimx, int dimy);									//Usado para dibujar el mapa e iniciar la etapa de dibujo

int check_for_maps();		//Abre el archivo con el numero de mapas y devuelve el numero

void list_maps(unsigned int n, char ** map_temp);	//Recibe un el numero de mapas y un puntero a una cadena de caracteres, lista los mapas y devuelve el nombre del archivo del mapa elegido (en la cadena)


PUNTO new_point(int x, int y)
{
	PUNTO p;
	p.x = x;
	p.y = y;
	return p;
}

bool equal_points(PUNTO a, PUNTO b)
{
	return a.x == b.x && a.y == b.y;
}


void Oculta_cursor()
{
	CONSOLE_CURSOR_INFO cci = {100, FALSE};

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}


PILA PilaVacia(){
	return NULL;
}

bool EsPilaVacia(PILA P){
	if (P != NULL)
	{
		return false;
	}else{
		return true;
	}
}

PILA PUSH(PILA P, ITEM item){
	PILA nuevo;
	nuevo = new nodo;
	nuevo->dato = item;
	nuevo->next = P;
	P = nuevo;
	return P;
}

ITEM TOP(PILA P){
	if (EsPilaVacia(P))
	{
		return error;
	}else{
		return P->dato;
	}
}

PILA POP(PILA P){
	if (EsPilaVacia(P))
	{
		return P;
	}else{
		return P->next;
	}
}


void * ReservarMemoria(int cant)
{
	void * pAux;

	if((pAux = malloc(cant)) == NULL)
	{
		cprintf("No pudo reservar memoria dinamica");
		getch(); exit(1);
	}
	return pAux;
}


bool unvisited_cells(MAP mapa)
{
	for (int i = 0; i < mapa.dimx; i++)
	{
		for (int j = 0; j < mapa.dimy; j++)
		{
			//Si una celda no pared no fue visitada
			if (!mapa.cell[i][j].wall && !mapa.cell[i][j].visited)
			{
				//Digo hay al menos una celda no visitada
				return true;
			}
		}
	}
	//Todas las celdas fueron visitadas
	return false;
}

PUNTO rand_choose_cell(MAP mapa, PUNTO current)
{
	int arr[4] = {0, 1, 2, 3};
	int a = 4;
	int n = random(a);//random entre 0 y 3  0: arriba, 1: derecha, 2: abajo, 3: izquierda

	while(true)
	{
		if (arr[n] == 0)//arriba
		{
			//Pruebo que no se pase de los limites y que no haya sido visitada
			if (current.y - 2 > 0 && current.y - 2 < (mapa.dimy - 1) && mapa.cell[current.x][current.y - 2].visited == false)
			{
				//Muevo el punto
				return new_point(current.x, current.y - 2);
			}
		}else{
			if (arr[n] == 1)//derecha
			{
				if (current.x + 2 < (mapa.dimx - 1) && current.x + 2 > 0 && mapa.cell[current.x + 2][current.y].visited == false)
				{
					return new_point(current.x + 2, current.y);
				}
			}else{
				if (arr[n] == 2)//abajo
				{
					if (current.y + 2 < (mapa.dimy - 1) && current.y + 2 > 0 && mapa.cell[current.x][current.y + 2].visited == false)
					{
						return new_point(current.x, current.y + 2);
					}
				}else{//izquierda
					//n == 3
					if (current.x - 2 < (mapa.dimx - 1) && current.x - 2 > 0 && mapa.cell[current.x - 2][current.y].visited == false)
					{
						return new_point(current.x - 2, current.y);
					}
				}
			}
		}

		//Si se pasa del numero o estaba visitada, elimino el numero elegido del arreglo
		for(int i = 0 ; i < a ; i++)
		{
			if(arr[i] == arr[n])
			{
				for(int j = i; j < a ; j++){
					arr[j] = arr[j+1];
				}
				a--;
			}
		}

		//Y genero otro numero
		n = random(a);
	}
}

bool exist_unvisited_neighbors(MAP mapa, PUNTO p)
{
	//Reviso en todas las celdas a una distancia 2 de la "current" (porque a distancia 1 esta la pared)

	if (p.y - 2 > 0 && mapa.cell[p.x][p.y - 2].visited == false)//arriba no fue visitado
	{
		return true;
	}else{
		if (p.x + 2 < mapa.dimx && mapa.cell[p.x + 2][p.y].visited == false)//derecha no fue visitado
		{
			return true;
		}else{
			if ((p.y + 2 < mapa.dimy && mapa.cell[p.x][p.y + 2].visited == false))//abajo no fue visitado
			{
				return true;
			}else{
				if (p.x - 2 > 0 && mapa.cell[p.x - 2][p.y].visited == false)//izquierda no fue visitado
				{
					return true;
				}else{
					return false;
				}
			}
		}
	}
}

void remove_walls(PUNTO c, PUNTO p, MAP mapa)
{
	//Uso aritmetica para sacar el punto intermedio
	int n = (p.x + c.x)/ 2, m = (p.y + c.y)/2;
	mapa.cell[n][m].wall = false;
}


MAP new_map(int x, int y)
{
	MAP mapa;

	mapa.dimx = x;
	mapa.dimy = y;
	//Reservo las columnas del mapa
	mapa.cell = (CELL **)ReservarMemoria(sizeof(CELL *) * mapa.dimx);

	for (int i = 0; i < mapa.dimx; i++)
	{
		//Reservo las filas del mapa
		mapa.cell[i] = (CELL *)ReservarMemoria(sizeof(CELL) * mapa.dimy);

		for (int j = 0; j < mapa.dimy; j++)
		{
			//Les doy su posicion
			mapa.cell[i][j].pos.x = i;
			mapa.cell[i][j].pos.y = j;

			//Empiezo con todas las celdas pares como paredes
			//Reviso si deben ser paredes
			if (i % 2 == 0 || j % 2 == 0)
			{
				mapa.cell[i][j].wall = true;
				mapa.cell[i][j].visited = true;
			}else{
				mapa.cell[i][j].wall = false;
				mapa.cell[i][j].visited = false;
			}
		}
	}

	return mapa;
}

void print_unfinished_map(MAP mapa)
{
	clrscr();
	for (int i = 0; i < mapa.dimx; i++)
	{
		for (int j = 0; j < mapa.dimy; j++)
		{
			// Voy a la posicion de la celda, gotoxy no puede ser 0, por lo tanto le sumo 1, entonces en vez de ir de 0 a dim - 1, va de 1 a dim
			gotoxy(mapa.cell[i][j].pos.x + 1, mapa.cell[i][j].pos.y + 1);

			// Si es pared
			if (mapa.cell[i][j].wall == true)
			{
				// Dibujo el caracter de pared en gris
				textcolor(DARKGRAY);
				cprintf("%c", CAR_PARED);
			}else{
				// Sino dibujo el caracter vacio
				printf("%c", CAR_VACIO);
			}
		}
	}
}

void print_map(MAP mapa, PUNTO start, PUNTO end)
{
	clrscr();
	for (int i = 0; i < mapa.dimx; i++)
	{
		for (int j = 0; j < mapa.dimy; j++)
		{
			// Voy a la posicion de la celda, gotoxy no puede ser 0, por lo tanto le sumo 1, entonces en vez de ir de 0 a dim - 1, va de 1 a dim
			gotoxy(mapa.cell[i][j].pos.x + 1, mapa.cell[i][j].pos.y + 1);

			// Si es pared
			if (mapa.cell[i][j].wall == true)
			{
				// Dibujo el caracter de pared en gris
				textcolor(DARKGRAY);
				cprintf("%c", CAR_PARED);
			}else{
				// Sino, si es premio
				if (mapa.cell[i][j].prize)
				{
					//Dibujo el caracter de premio en amarillo
					textcolor(YELLOW);
					cprintf("%c", CAR_PREMIO);
				}else{
					// Sino dibujo el caracter vacio
					printf("%c", CAR_VACIO);
				}
			}
		}
	}

	// En start dibujo el caracter en rojo
	gotoxy(start.x + 1, start.y + 1);
	textcolor(RED);
	cprintf("%c", CAR_PUERTA);

	// En end dibujo el caracter en verde
	gotoxy(end.x + 1, end.y + 1);
	textcolor(LIGHTGREEN);
	cprintf("%c", CAR_PUERTA);
}

void generate_maze(MAP * mapa, PUNTO start, PUNTO end)
{
	int x1, y1;
	PUNTO current, chosen;
	PILA movidas =  PilaVacia();
	//Designo dos variables con la direccion de la celda central
	x1 = mapa->dimx / 2;
	if (x1 % 2 == 0)
	{
		x1++;
	}

	y1 = mapa->dimy / 2;
	if (y1 % 2 == 0)
	{
		y1++;
	}
	

	//Empiezo por la celda del centro (la celda en la posicion "current" es la celda que esta siendo analizada)
	current = new_point(x1, y1);

	//Digo que la celda central fue visitada
	mapa->cell[x1][y1].visited = true;

	//Digo que la celda (1, 0) no sea pared, para que haya inicio
	mapa->cell[start.x][start.y].wall = false;
	mapa->cell[start.x][start.y].visited = true;

	//Digo que la celda (dimx-2, dimy-1) no sea pared, para que haya final
	mapa->cell[end.x][end.y].wall = false;
	mapa->cell[end.x][end.y].visited = true;

	//Mientras haya celdas no visitadas
	while(unvisited_cells(*mapa))
	{	
		//Si la celda "current" tiene vecinos no visitados
		if (exist_unvisited_neighbors(*mapa, current))
		{
			//Elijo un vecino al azar
			chosen = rand_choose_cell(*mapa, current);
			
			//Pongo la celda "current" en la pila, para poder volver hacia atras en caso de quedar en un rincon
			movidas = PUSH(movidas, current);
			
			//Destruyo la pared entre "current" y la elegida
			remove_walls(chosen, current, *mapa);

			//Digo que "current" fue visitada
			current = chosen;
			mapa->cell[current.x][current.y].visited = true;

			if (random(mapa->dimx/2) == 0)
			{
				mapa->cell[current.x][current.y].prize = true;
			}else{
				mapa->cell[current.x][current.y].prize = false;
			}
		
		}else{
			//Si "current" no tiene vecinos no visitados, significa que estoy en un rincon
			//Asi que debo volver en retroceso

			//Hago que "current" sea el tope de la pila (la anterior "current")
			current = TOP(movidas);
			//Elimino el tope de la pila
			movidas = POP(movidas);
		}
	}
}

void pregen_maze(char * source, MAP *maze)
{
	int k;

	for (int i = 0; i < maze->dimx; i++)
	{
		for (int j = 0; j < maze->dimy; ++j)
		{
			// k va avanzando --
			k = j + (maze->dimy)*i;

			// Guardo el punto con la posicion en el mapa
			maze->cell[i][j].pos = new_point(i, j);

			// Usando k decido si es pared, premio o vacio
			if (source[k] == '0')
			{
				maze->cell[i][j].wall = true;
			}else{
				maze->cell[i][j].wall = false;
				if (source[k] == '2')
				{
					maze->cell[i][j].prize = true;
				}else
				{
					maze->cell[i][j].prize = false;
				}
			}
		}
	}
}

bool check_prize(CELL celda)
{
	return celda.prize;
}


header save_header(MAP mapa, char name[20], PUNTO start, PUNTO end)
{
	int i, j, k;
	header aux;

	// Copio el nombre al auxiliar
	strcpy(aux.name, name);

	//Copio las variables al auxiliar
	aux.start = start;
	aux.end = end;
	aux.dim_x = mapa.dimx;
	aux.dim_y = mapa.dimy;
	return aux;
}

char * save_source(MAP mapa)
{
	int i, j, k;

	//Guardo memoria en una cadena de caracteres
	char * source = (char *)ReservarMemoria((mapa.dimx * mapa.dimy + 1) * sizeof(char));

	for (i = 0; i < mapa.dimx; i++)
	{
		for (j = 0; j < mapa.dimy; j++)
		{
			k = j + (mapa.dimy)*i;

			// Si es pared pongo un 0 en la cadena, si es premio un 2 y sino (es vacio) un 1
			if (mapa.cell[i][j].wall)
			{
				source[k] = '0';
			}else{
				if (mapa.cell[i][j].prize)
				{
					source[k] = '2';
				}else{
					source[k] = '1';
				}
			}
		}
	}
	//Termino la cadena con el catacter de fin de cadena
	source[mapa.dimx * mapa.dimy + 1] = '\0';

	return source;
}



JUGADOR nuevo_jugador(PUNTO start)
{
	JUGADOR player;

	//Inicio al jugador en start
	player.pos = start;
	//Elegi el caracter 0 para representar al jugador
	player.caracter = CAR_JUG_CENTRO;
	return player;
}

void dibujarjugador(JUGADOR player)
{
	//voy a la posicion del jugador y dibujo el caracter, gotoxy no puede ser 0, por lo tanto le sumo 1, entonces en vez de ir de 0 a dim - 1, va de 1 a dim
	gotoxy(player.pos.x + 1, player.pos.y + 1);
	printf("%c", player.caracter);
}

void moverjugador(JUGADOR *player, MAP mapa, int tecla)
{
	//Borro el anterior jugador
	gotoxy(player->pos.x + 1, player->pos.y + 1);

	//Si su posicion en Y es 0 significa que esta saliendo de la salida
	if (player->pos.y == 0)
	{
		textcolor(RED);
		cprintf("%c", CAR_PUERTA);
	}else
		printf("%c", CAR_VACIO);

	//Analizo que tecla fue presionada
	switch (tecla)
	{
		case FLECHA_ARR: //arriba
		
			//Analizo que no se pase del mapa o que no entre a una pared
			if(player->pos.y > 0 && !mapa.cell[player->pos.x][player->pos.y - 1].wall)

				//Cambio la posicion del jugador
				player->pos.y --;
				player->caracter = CAR_JUG_ARR;
			break;
			
		case FLECHA_AB://abajo
			if(player->pos.y < mapa.dimy - 1 && !mapa.cell[player->pos.x][player->pos.y + 1].wall)
				player->pos.y ++;
				player->caracter = CAR_JUG_AB;
			break;

		case FLECHA_DER: //derecha
			if(player->pos.x < mapa.dimx - 1 && !mapa.cell[player->pos.x + 1][player->pos.y].wall)
				player->pos.x ++;
				player->caracter = CAR_JUG_DER;
			break;

		case FLECHA_IZQ: //izquierda
			if(player->pos.x > 0 && !mapa.cell[player->pos.x - 1][player->pos.y].wall)
				player->pos.x --;
				player->caracter = CAR_JUG_IZQ;
			break;
	}
}

void moverpincel(JUGADOR *player, MAP mapa, int tecla, bool prize)
{
	//Borro el anterior jugador
	gotoxy(player->pos.x + 1, player->pos.y + 1);
	cprintf("%c", CAR_VACIO);
	mapa.cell[player->pos.x][player->pos.y].wall = false;
	mapa.cell[player->pos.x][player->pos.y].prize = false;


	//Analizo que tecla fue presionada
	switch (tecla)
	{
		case FLECHA_ARR: //arriba
		
			//Analizo que no se pase del mapa o que no entre a una pared
			if(player->pos.y > 0)
				//Cambio la posicion del jugador
				player->pos.y --;
				player->caracter = CAR_JUG_ARR;
			break;
			
		case FLECHA_AB://abajo
			if(player->pos.y < mapa.dimy - 1)
				player->pos.y ++;
				player->caracter = CAR_JUG_AB;
			break;

		case FLECHA_DER: //derecha
			if(player->pos.x < mapa.dimx - 1)
				player->pos.x ++;
				player->caracter = CAR_JUG_DER;
			break;	

		case FLECHA_IZQ: //izquierda
			if(player->pos.x > 0)
				player->pos.x --;
				player->caracter = CAR_JUG_IZQ;
			break;

		case 'w': //w

			player->caracter = CAR_JUG_ARR;
			if(player->pos.y > 0){
				if (prize)
				{
					mapa.cell[player->pos.x][player->pos.y - 1].prize = true;
					mapa.cell[player->pos.x][player->pos.y - 1].wall = false;
					gotoxy(player->pos.x + 1, player->pos.y);
					textcolor(YELLOW);
					cprintf("*");
				}else{
					mapa.cell[player->pos.x][player->pos.y - 1].wall = true;
					mapa.cell[player->pos.x][player->pos.y - 1].prize = false;
					gotoxy(player->pos.x + 1, player->pos.y);
					textcolor(DARKGRAY);
					cprintf("%c", CAR_PARED);
				}
			}
			break;
			
		case 's'://s

			player->caracter = CAR_JUG_AB;
			if(player->pos.y < mapa.dimy - 1){
				if (prize)
				{
					mapa.cell[player->pos.x][player->pos.y + 1].prize = true;
					mapa.cell[player->pos.x][player->pos.y + 1].wall = false;
					gotoxy(player->pos.x + 1, player->pos.y + 2);
					textcolor(YELLOW);
					cprintf("*");
				}else{
					mapa.cell[player->pos.x][player->pos.y + 1].wall = true;
					mapa.cell[player->pos.x][player->pos.y + 1].prize = false;
					gotoxy(player->pos.x + 1, player->pos.y + 2);
					textcolor(DARKGRAY);
					cprintf("%c", CAR_PARED);
				}
			}
			break;

		case 'd': //d
			player->caracter = CAR_JUG_DER;
			if(player->pos.x < mapa.dimx - 1){
				if (prize)
				{
					mapa.cell[player->pos.x + 1][player->pos.y].prize = true;
					mapa.cell[player->pos.x + 1][player->pos.y].wall = false;
					gotoxy(player->pos.x + 2, player->pos.y + 1);
					textcolor(YELLOW);
					cprintf("*");
				}else{
					mapa.cell[player->pos.x + 1][player->pos.y].wall = true;
					mapa.cell[player->pos.x + 1][player->pos.y].prize = false;
					gotoxy(player->pos.x + 2, player->pos.y + 1);
					textcolor(DARKGRAY);
					cprintf("%c", CAR_PARED);
				}
			}
			break;	

		case 'a': //a
			player->caracter = CAR_JUG_IZQ;
			if(player->pos.x > 0){
				if (prize)
				{
					mapa.cell[player->pos.x - 1][player->pos.y].prize = true;
					mapa.cell[player->pos.x - 1][player->pos.y].wall = false;
					gotoxy(player->pos.x, player->pos.y + 1);
					textcolor(YELLOW);
					cprintf("*");
				}else{
					mapa.cell[player->pos.x - 1][player->pos.y].wall = true;
					mapa.cell[player->pos.x - 1][player->pos.y].prize = false;
					gotoxy(player->pos.x, player->pos.y + 1);
					textcolor(DARKGRAY);
					cprintf("%c", CAR_PARED);
				}
			}
			break;

	}
}

int GameLoop(JUGADOR player, PUNTO start, PUNTO end, MAP mapa, step ** L)
{
	int score = 0;
	bool begin = true; //Bandera para ver si es el inicio del ciclo
	step * aux; // Auxiliar para recorrer la lista enlazada

	print_map(mapa, start, end);

	while(!equal_points(player.pos, end)){
		//Dibujo al jugador
		dibujarjugador(player);
		//Detecto la tecla
		//Uso 2 getch porque las flechas de direccion devuelve 2 valores
		getch();

		//Muevo al juegador
		moverjugador(&player, mapa, getch());
		gotoxy(1, mapa.dimy + 4);

		// Cargo la lista enlazada
		if (begin)
		{
			// Si es el inicio cargo en la lista
			*L = aux = (step *)ReservarMemoria(sizeof(step));
			aux->p = player;
			aux->next = NULL;
		}else{
			// Sino cargo en el auxiliar
			aux->next = (step *)ReservarMemoria(sizeof(step));
			aux = aux->next;
			aux->p = player;
			aux->next = NULL;
		}

		//Chequeo si piso un premio
		if (check_prize(mapa.cell[player.pos.x][player.pos.y]))
		{
			score -= ((mapa.dimx+mapa.dimy)/2)*.4;
		}

		score++;	//El puntaje lo calculo como la cantidad de movimientos
		begin = false;	//Pongo la bandera en falso para decir que ya paso un ciclo
	}
	return score;
}

MAP draw_map(int dimx, int dimy)
{

	JUGADOR player = nuevo_jugador(new_point(dimx/2, dimy/2));
	MAP mapa;
	int tecla;
	bool prize = true;

	mapa.dimx = dimx;
	mapa.dimy = dimy;

	mapa.cell = (CELL **)ReservarMemoria(sizeof(CELL *) * mapa.dimx);

	for (int i = 0; i < mapa.dimx; i++)
	{
		//Reservo las filas del mapa
		mapa.cell[i] = (CELL *)ReservarMemoria(sizeof(CELL) * mapa.dimy);

		for (int j = 0; j < mapa.dimy; j++)
		{
			//Les doy su posicion
			mapa.cell[i][j].pos.x = i;
			mapa.cell[i][j].pos.y = j;

			mapa.cell[i][j].wall = true;
			mapa.cell[i][j].visited = true;
			mapa.cell[i][j].prize = false;
			// gotoxy(mapa.cell[i][j].pos.x, mapa.cell[i][j].pos.y);
			// printf("%c", CAR_PARED);
		}
	}

	mapa.cell[dimx/2][dimy/2].wall = false;

	print_unfinished_map(mapa);
	gotoxy(1, dimy + 1);
	printf("Presione la barra espaciadora para cambiar entre premio y pared\nPresione enter cuando este listo");
	Oculta_cursor();
	do
	{
		dibujarjugador(player);
		tecla = getch();
		if (tecla == CAR_VACIO)
		{
			prize = !prize;
		}
		moverpincel(&player, mapa, tecla, prize);
		fflush(stdin);
	}while(tecla != ENTER);
	return mapa;
}


void Replay(MAP mapa, JUGADOR player, step * L, PUNTO start, PUNTO end)
{
	step * aux = L;
	print_map(mapa, start, end);

	while(aux != NULL)
	{
		gotoxy(player.pos.x + 1, player.pos.y + 1);
		if (player.pos.y == start.y)
		{
			textcolor(RED);
			cprintf("%c", CAR_PUERTA);
		}else
			printf("%c", CAR_VACIO);
		player = aux->p;
		dibujarjugador(player);
		aux = aux->next;
		Sleep(150);
	}
	gotoxy(1, mapa.dimy + 2);
	printf("Repetir? (s/n)");
	fflush(stdin);
	if (getch() == 's')
	{
		Replay(mapa, player, L, start, end);
	}
}

int check_for_maps()
{
	FILE * manager;
	int n;

	if ((manager = fopen("Game Manager.dat", "rb")) == NULL)
	{
		n = 0;
		manager = fopen("Game Manager.dat", "wb");
		fprintf(manager, "0\0");
	}else{
		fscanf(manager, "%d", &n);
	}

	fclose(manager);
	return n;

}

void list_maps(unsigned int n, char ** map_temp)
{
	char map_access[] = "mapa_";
	char map_ext[] = "1.dat\0";

	char name[20]; //Digo que los nombres seran de 20 caracteres
	FILE * mapa;
	int x;

	*map_temp = (char *)ReservarMemoria(sizeof(char) * (strlen(map_ext) + strlen(map_access)));


	//Listo los mapas, ya que se como se llaman los archivos
	printf("Lista de mapas:\r\n");
	for (unsigned int i = 1; i <= n; i++)
	{
		strcpy(*map_temp, map_access);	//Copio la base del nombre de los archivos
		map_ext[0] = i + '0';			//Agrego el numero que lo identifica
		strcat(*map_temp, map_ext);		//Agrego la extension

		mapa = fopen(*map_temp, "rb");	//Abro el archivo
		fgets(name, 20, mapa);			//Tomo los primeros 20 bits, que son el nombre
		printf("%d %s\r\n", i, name);	//Escribo el nombre con el numero
		fclose(mapa);
	}

	memset(*map_temp, 0, sizeof(*map_temp));

	printf("%d Volver al menu principal\n", n + 1);
	printf("\r\nSeleccione un mapa: ");
	scanf("%d", &x);

	if (x == n + 1)
	{
		*map_temp[0] = 1;
		printf("%d\n", *map_temp[0]);
	}else
		if (x <= n)
		{
			//Abro el mapa elegido
			strcpy(*map_temp, map_access);
			map_ext[0] = x + '0';
			strcat(*map_temp, map_ext);
		}else{
			clrscr();
			
			//Si elige un numero invalido aparecera esto arriba
			printf("Por favor, seleccione un numero de las opciones\n");
		}
}