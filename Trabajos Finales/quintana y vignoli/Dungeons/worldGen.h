
//DUNGEONS SOURCE CODE 
//DEVELOPED BY QUINTANA, EDUARDO NICOLAS & VIGNOLI, LUCAS 
//VERSION 0.2a
//2016
#include	<conio.h> 
#include	<stdio.h> 
#include	<stdlib.h> 
#include	<dos.h> 
#include 	<cstdio.h>
#include	<iostream>
#include	<windows.h>
#include	<math.h>

#define WALL 219				//caracter de pared
#define DRAGON 245				//caracter de enemigo
#define	RELIC 197				//caracter de item
#define DELIVERYZONE 254		//caracter de meta
#define BRUSH 184				//caracter del pincel
#define TRAP 178				//caracter de las trampas
#define PLAYEREMPTY	1			//carater del jugador sin reliquia
#define PLAYERFULL	2			//carater del jugador con reliquia
#define FILESTRING "Nivel.dat"	//ruta en donde se guarda el mapa

struct Header 					//Estructura que contiene la cabecera a guardarse en el archivo binario.
{
	int amountScenes;			//Variable que contiene la cantidad de escenas (habitaciones) de todo el nivel.
	int dimx;					//Varibale que almacena la dimension en el eje x, de todas las escenas, es decir, la cantidad de columnas.
	int dimy;					//Varibale que almacena la dimension en el eje y, de todas las escenas, es decir, la cantidad de filas.
	int items;					//Variable que contiene la cantidad de reliquias presentes en el nivel completo.
};

struct Pixel					//estructura que representa un pixel del mapa.
{
	int coordX;					//Coordenada en x, minimo valor : 1
	int coordY;					//Coordenada en y, minimo valor : 1
	int character;				//carater dibujado en esta celda o "pixel"
};


struct Rows				
{
	
	Pixel * pixels; 			//puntero a reserva de memoria que contiene todas las columns de una sola fila.

};

struct Map 						//Estructura que contiene un mapa.
{
	int dimx;					//amountidad de columns
	int dimy;					//amountidad de rows
	Rows * rows;				//puntero a reserva de memoria que contiene todas las rows para un solo mapa.
};

struct Scene					//Estructura que representa una escena, es decir, una habitacion.
{
	int id;						//Numero de identificacion usado para cargar la escena.
	
	Map * map;					//Puntero al mapa de esta escena.
	int door1id;				//identificacion de cada puerta, siendo 0 null.
	int door2id;
	int door3id;
	int door4id;

	Scene* next;				//Puntero a la siguiente escena de la lista enlazada.

};

struct Brush 					//Estructura que representa el pincel, usado para dibujar el mapa.
{
	int coordX;					//coordenadas en x, minimo valor : 1
	int coordY;					//coordenadas en y, minimo valor : 1
	int character;				//caracter que se dibuja para representar el pincel
	int brushhead;				//Caracter a pintar.
};

struct Jugador 					//Estructura que representa al jugador.
{
	int coordX;					//coordenadas en x, minimo valor : 1
	int coordY;					//coordenadas en y, minimo valor : 1
	int character;				//caracter que se dibuja para representar el jugador
	
};

struct Enemy 					//Estructura que representa al fantasma enemigo.
{
	int coordX;					//coordenadas en x, minimo valor : 1
	int coordY;					//coordenadas en y, minimo valor : 1
	int character;				//caracter que se dibuja para representar el enemigo.

};

//**********	PROTOTYPES	*********

Scene * Create_Level();			//Funcion que crea una lista enlazada de escenas.

Scene * New_Scene(Header * header, int id);			//Funcion que crea una nueva escena vacia.

void Create_Empty_Map(Map * map, int amount_rows, int amount_columns);			//Funcion que crea un mapa vacio

void Draw_Map(Map * map);		//Funcion que dibuja un mapa.

void Draw_Map(Map * map, Enemy* enemies[20], int * countEnemy);	//Funcion que dibuja el mapa. Especificamente usada durante el juego y no la creacion de mapas.

void Draw_Palette();			//Funcion que dibuja la paleta que indica cuales son las posibles brushheads.

void Draw_Brush(Brush * brush);	//Funcion que dibuja el pincel en las coordenadas correspondientes.

void Input_Check_Brush( Map * map, Brush * brush, int * key, int*items);	//Funcion que realiza el checkeo de keys presionadas DURANTE LA CREACION DE UN MAPA

bool Brush_Movement(Map * map, Brush * brush, int * key);	//Funcion que mueve el pincel, devuelve verdadero si las keys presionadas son para mover el pincel.

bool Brush_Head_Selection(Brush * brush, int * key);	//Funcion que selecciona el tipo de brushhead a pintar, devuelve verdadero si las keys presionadas corresponden a la seleccion de brushhead.

bool Draw_Brushhead(Map * map, Brush * brush , int * key, int* items);	//Funcion que pinta la brushhead, devuelve verdadero si las keys presionadas son para pintar la brushhead.

void Generate_Way(Map * map, Brush * brush, int * items);	 //Funcion que genera el camino tras el pincel.

Scene* Search_Scene_By_Id(Scene* mainScene, int id);	//Funcion que devuelve una escena dentro de una lista enlazada, cuyo id es el especificado.

void Save_Level (Scene* Aux, Header * header);	//Funcion que guarda el nivel en un archivo binario.

Scene* Load_All_Scenes(int* items);	//Funcion que carga todas las escenas, armando una lista enlazada y devolviendo la primera escena cargada.

Scene* Load_Scene(FILE* file, int dimy, int dimx);	//Funcion que carga una escena de un archivo binario y devuelve un puntero a ella.

int Get_Amount_Scenes(Scene * scene);	//Funcion que dada un escena incial de una lista enlazada, devuelve la cantidad de escenas en dicha lista.

void Modify();							//Funcion que permite la modificacion de escenas concretas.

void Modify_Scene(Scene * mainscene, Scene * scene, int * items, int amount);	//Funcion que hace uso de funciones anteriores para modificar una escena en particular.

void Menu();							//Funcion que contiene toda la logica de interaccion del menu.

void HowToPlay(int *);					//Funcion que muestra la informacion sobre como jugar el juego.

void HowToCreate(int *);				//Funcion que muetra la informacion sobre como crear un nivel completo.

bool GameLoop(Scene * mainScene, int *items);	//Funcion que contiene el juego propiamente dicho.

bool Enemy_Movement(Enemy * enemy, Jugador * jugador, Map * map);	// Funcion que se encarga de manejar la inteligencia artifical de los enemigos.

void * Save_Memory(int amount);			//Funcion para reservar memoria


//************	DEFINITIONS	************

//*******	GENERATION ********
Scene * Create_Level()
{
	Header header;							//Se crea una instancia de la estructura Header para poder almacenar luego el nivel completo.
	header.items = 0;						//Inicializa en 0 la cantidad de items o reliquias que presentara el nivel.
	
	Scene * Aux ;							//Puntero a una escena que sera utilizado para crear una lista enlazada de escenas.
	Scene * Start;							//Puntero a una escena que representara la escena principal y el inicio de la lista.
	
	do{										//Se piden los valores de cantidad, filas y columnas, controlando que estos sean valores validos, y se los asigna a la cabecera.
		printf("Ingrese la cantidad de escenas: ");
		scanf("%d", &header.amountScenes);
		clrscr();
	}while(header.amountScenes <= 0);
	do{
		printf("Ingrese la cantidad de filas de los mapas: ");
		scanf("%d", &header.dimy);
		clrscr();
	}while(header.dimy <= 0);
	do{
		printf("Ingrese la cantidad de columnas de los mapas: ");
		scanf("%d", &header.dimx);
		clrscr();
	}while(header.dimx <= 0);

	printf("ESCENA 1\n\n");		

	Aux = New_Scene(&header, 1);			//Se llama a la funcion New_Scene que devuelve una escena completa ya dibujada por el usuario.
	Aux->next = NULL;						//Se asigna a la escena siguiente como nula pues en este punto la lista tiene una solo escena.
	Start = Aux;							//Esta unica escena es designada como la escena principal y en inicio de la lista.

	for(int i = 1; i < header.amountScenes; i++)	//Se crean escenas deacuerdo al valor ingresado en la cabecera, formando asi una lista enlazada de escenas dibujadas por el usuario.
	{
		clrscr();
		printf("ESCENA %d\n\n", i+1);

		Aux->next = New_Scene(&header,  i+1 );
		Aux = Aux->next;
		Aux->next = NULL;
	}

	Save_Level(Start, &header);				//Una vez creada la lista, se procede a guardarlas con la funcion Save_Level que guarda todo el nivel en un archivo binario.

	return Start;							//Retorna el inicio de la lista.
}

Scene * New_Scene(Header * header, int id)
{
	int key; 						//variable que almacenara la key presionada
	Scene * New_Scene = (Scene *)Save_Memory(sizeof(Scene));// Se crea un puntero a una reserva de memoria de tamanio Scene y se guarda en un puntero auxiliar llamade New_Scene.
	New_Scene->map = (Map *) Save_Memory (sizeof(Map));// Se crea un puntero a una reserva de memoria de tamanio Map y se la asigna al puntero map de la estructura scene a la que apunta el puntero New_Scene.

	Brush brush; 					//variable del tipo Brush que representa el pincel.
	Create_Empty_Map(New_Scene->map, header->dimy, header->dimx); //  crea el mapa "vacio" de dimensiones rowsXcolumns.
	brush.coordX = New_Scene->map->dimx / 2;	// Ubica el pincel en el medio del mapa.
	brush.coordY = New_Scene->map->dimy / 2;	// Ubica el pincel en el medio del mapa.
	brush.character = BRUSH;	//Se establece el caracter que representa el pincel.
		
	New_Scene->id = id;			//Se le asigna a la escena el id correspondiente.

	printf("\nCUIDADO!: El id de las puertas deben ser 0 si se desea que esten cerradas o no lleven a ningun lado.\n\n ");

	do 							//Se pide el id de la escena contigua a la escena actual por cada una de las puertas, siendo la puerta 1 la puerta de arriba y seguidas las demas en sentido horario.
	{							//Se hace la comprobacion necesaria, impidiendo que el id ingresado sea positivo, distinto de la escena actual y no mayor que la cantidad total de escenas.
		printf("\nIngrese el id de la puerta 1: ");
	
		scanf("%d", &New_Scene->door1id);

	}while(New_Scene->door1id < 0 || New_Scene->door1id > header->amountScenes || New_Scene->door1id == id);

	do
	{
		printf("\nIngrese el id de la puerta 2: ");
	
		scanf("%d", &New_Scene->door2id);

	}while(New_Scene->door2id < 0 || New_Scene->door2id > header->amountScenes || New_Scene->door2id == id);

	do
	{
		printf("\nIngrese el id de la puerta 3: ");
	
		scanf("%d", &New_Scene->door3id);

	}while(New_Scene->door3id < 0 || New_Scene->door3id > header->amountScenes || New_Scene->door3id == id);

	do
	{
		printf("\nIngrese el id de la puerta 4: ");
	
		scanf("%d", &New_Scene->door4id);

	}while(New_Scene->door4id < 0 || New_Scene->door4id > header->amountScenes || New_Scene->door4id == id);
	
	clrscr();

	Draw_Map(New_Scene->map);					//Dibuja el mapa vacio.

	printf("\n\nEscena %d", New_Scene->id);		//Se muestra el id de la escena actual.
	printf("\n");

	Draw_Palette();								//Luego de dibujar el mapa, se dibuja la Paleta.

	brush.brushhead = WALL;						//Se asigna la cabeza del pincel como pared como predeterminado.

	do{		
		Generate_Way(New_Scene->map, &brush, &header->items);	//Se guarda en la matriz del mapa, un espacio vacio en las coordenadas del pincel.
			
		Draw_Brush(&brush);										//Se dibuja el pincel en sus coordenadas
		
		key = getch(); 											//Se guarda la tecla presionada en una variable que se pasara de funcion en funcion para determinar que accion ejecutar.
		
		Input_Check_Brush(New_Scene->map, &brush, &key, &header->items);// De ser necesario, mueve el pincel o pinta una pared.	
	}
	while(key != 27); 							//se repite hasta que se presione ESC, lo cual termina el proceso de creado de una escena.
	clrscr();

	return New_Scene; 							//Una vez terminada la habitacion o escena, se la retorna para su inclusion en la lista.
}

void Create_Empty_Map(Map * map, int amount_rows, int amount_columns)
{
	if(map != NULL)						//Si el mapa no es nulo.
	{
		map->dimx = amount_columns;		//Se asigna la cantidad de columnas a crear.
		map->dimy = amount_rows;		//se asigna la cantidad de filas a crear.
		
		map->rows = (Rows *)Save_Memory(sizeof(Rows) * map->dimy);	//Rserva memoria de la cantidad de filas.
	
		for (int i = 0; i < map->dimy; i++) 	//Para cada fila, se hace reserva de memoria de las columnas. 
		{	
			map->rows[i].pixels = (Pixel *)Save_Memory(sizeof(Pixel) * map->dimx);
	
			for (int j = 0; j < map->dimx; j++)		//Para cada Pixel, se especifican sus coordenadas en pantalla y su caracter.
			{
				map->rows[i].pixels[j].coordX = j + 1;	//Se suma + 1 porque el minimo valor para las coordenadas es 1.
				map->rows[i].pixels[j].coordY = i + 1;
				map->rows[i].pixels[j].character = WALL;
				
			}
		}
	}	
}

void Draw_Map(Map * map)
{
	if(map != NULL)
	{
		for (int i = 0; i < map->dimy; i++) //para cada fila obtengo la columna
		{		
			for (int j = 0; j < map->dimx; j++) //para cada Pixel de una fila, muevo el cursor a la coordenada del Pixel, e imprimo su caracter.
			{
				
				gotoxy(map->rows[i].pixels[j].coordX, map->rows[i].pixels[j].coordY);
				
				printf("%c", map->rows[i].pixels[j].character);			
				
			}
		}
	}
}

void Draw_Map(Map * map, Enemy* enemies[50] , int * countEnemy)
{	//Esta funcion es llamada una unica vez cada vez que el jugador entra en una escena.
	
	*countEnemy = 0;	//Puntero al contador de enemigos de una escena, usado para luego mover los enemigos.

	if(map != NULL)
	{
		for (int i = 0; i < map->dimy; i++)	//Para cada fila obtengo la columna
		{		
			for (int j = 0; j < map->dimx; j++)	
			{
				if(map->rows[i].pixels[j].character == DRAGON)	//Para cada Pixel analiza si es un Enemigo, y crea una instancia de Enemy, asignando los valores correspondiente y aumentando el contador.
				{
					enemies[*countEnemy] = (Enemy*) Save_Memory(sizeof(Enemy));
					enemies[*countEnemy]->coordX = map->rows[i].pixels[j].coordX;
					enemies[*countEnemy]->coordY = map->rows[i].pixels[j].coordY;
					enemies[*countEnemy]->character = DRAGON;
					(*countEnemy)++;							
				}			
				
				gotoxy(map->rows[i].pixels[j].coordX, map->rows[i].pixels[j].coordY); //Para cada Pixel de una fila, muevo el cursor a la coordenada del Pixel, e imprimo su caracter.
				
				printf("%c", map->rows[i].pixels[j].character);				
				
			}
		}
	}
}

void Draw_Palette()
{
	printf("\n------------------------------------- PALETA -----------------------------------\n\n 1: %c -> Paredes\n 2: %c -> Dragones\n 3: %c -> Reliquias\n 4: %c -> Zona de Entrega\n 5: %c -> Trampas\n ESC: Guardar", WALL, DRAGON, RELIC,DELIVERYZONE, TRAP);
}

void Draw_Brush(Brush * brush)
{
	//Posiciona el cursor en las coordenadas del pincel e imprime su caracter.
	gotoxy(brush->coordX, brush->coordY);
	printf("%c", brush->character);
}

void Input_Check_Brush( Map * map, Brush * brush, int * key, int*items)
{
	if(map != NULL)
	{
		gotoxy(brush->coordX, brush->coordY); //Antes de mover el pincel, pinta en su posicion un caracter vacio, en caso de que deba moverse.
		printf("%c", 0);		

		if(!Brush_Movement(map, brush, key))	//Si la funcion devuelve verdadero significa que s epresiono una tecla de movimiento.
		{
			if(!Brush_Head_Selection(brush, key))	//Si la funcion devuelve verdadero significa que se presiono una tecla de seleccion de cabeza de pincel.
			{	
				if(Draw_Brushhead(map, brush, key, items) && brush->brushhead == RELIC){	//si la funcion devuelve verdadero significa que se presiono una tecla de dibujo.
					
					
					(*items)++;		//En caso de haber pintado una reliquia se aumenta este contador.
					
				}
			}
		}

		//Las tres funciones antes vistas no solo checkean las teclas presionadas sino tambien ejecutan la accion adecuada a la tecla.
	}
}

bool Brush_Movement(Map * map, Brush * brush, int * key)
{
	if(map != NULL)
	{
		switch (*key) //Analiza la key presionada.
		{	//las coordenadas en x aumentan hacia la derecha. Las coordenadas en y aumentan hacia abajo.
			//Se controla que el pincel no este fuera de los limites ni vaya a moverse fuera del mapa, luego, se modifica sus coordenadas deacuerdo a la tecla presionada.
			case 72: //arriba
				if(brush->coordY > 1) //solo decremento la coordenada en y si es mayor a 1, en caso contrario saldria del mapa hacia arriba.
					brush->coordY --;
				return true;


			case 75://izquierda
				if(brush->coordX > 1)
					brush->coordX --;
				return true;
			
				
			case 80://abajo
				if(brush->coordY < map->dimy)
					brush->coordY ++;
				return true;
			

			case 77://derecha

				if(brush->coordX < map->dimx)
					brush->coordX ++;
				return true;						

		}
	}
	//Si no se retorno nada antes de esta linea significa que la tecla presionada no es de movimiento, por lo que retorna false.
	return false;
}

bool Brush_Head_Selection(Brush * brush, int * key)
{	//Funcionamiento simialr al anterior, se analiza la tecla, se selecciona la cabeza del pincel deacuerdo a la tecla presionada.Si no se presiona una tecla valida, retorna false.
	switch(*key)
	{	
		case 49:
			brush->brushhead = WALL;
			return true;
		case 50:
			brush->brushhead = DRAGON;
			return true;
		case 51:
			brush->brushhead = RELIC;
			return true;
		
		case 52:
			brush->brushhead = DELIVERYZONE;
			return true;
		case 53:
			brush->brushhead = TRAP;
			return true;	

	}
	return false;
}

bool Draw_Brushhead(Map * map, Brush * brush , int * key, int* items)
{
	if(map != NULL)
	{
		switch(*key) //Analiza si se presiono alguna tecla de pintado de paredes.
			{
				case 119: //	w, se pinta en la celda arriba del pincel, una pared, y tambien se guarda dicha pared en la matriz.
					if(brush->coordY != 1 ){	//Se checkea que no se escriba si el pincel esta en el limite superior
						if(map->rows[brush->coordY - 2].pixels[brush->coordX-1].character == RELIC)
						{
							items -= 1;
						}
						gotoxy(brush->coordX, brush->coordY-1); 
						printf("%c", brush->brushhead);	
						map->rows[brush->coordY - 2].pixels[brush->coordX-1].character = brush->brushhead;
					}
					return true;
					
				case 97: //a, se pinta en la celda izquierda del pincel, una pared, y tambien se guarda dicha pared en la matriz.
					if(brush->coordX != 1){	
						if(map->rows[brush->coordY - 1 ].pixels[brush->coordX - 2].character == RELIC)
						{
							items -= 1;
						}
						gotoxy(brush->coordX-1, brush->coordY);
						printf("%c", brush->brushhead);
						map->rows[brush->coordY - 1 ].pixels[brush->coordX - 2].character = brush->brushhead;
					}
					return true;
					
				case 115://s, se pinta en la celda abajo del pincel, una pared, y tambien se guarda dicha pared en la matriz.
					if( brush->coordY != map->dimy){
						if(map->rows[brush->coordY].pixels[brush->coordX - 1].character == RELIC)
						{
							items -= 1;
						}	
						gotoxy(brush->coordX, brush->coordY+1);
						printf("%c", brush->brushhead);
						map->rows[brush->coordY].pixels[brush->coordX - 1].character = brush->brushhead;
					}
					return true;
					
				case 100://d, se pinta en la celda derecha del pincel, una pared, y tambien se guarda dicha pared en la matriz.
					if(brush->coordX != map->dimx){
						if(map->rows[brush->coordY-1].pixels[brush->coordX].character == RELIC)
						{
							items -= 1;
						}
						gotoxy(brush->coordX+1, brush->coordY);					
						printf("%c", brush->brushhead);
						map->rows[brush->coordY-1].pixels[brush->coordX].character = brush->brushhead;
					}	
					return true;
					
				default://si no se presiono ninguna de las keys anteriores, se sale.
					return false;					
				
			}
	}
}

void Generate_Way(Map * map, Brush * brush, int* items)
{
	if(map != NULL)
	{
		//Selecciona, en la matriz del mapa, el caracter en la posicion en la que se encuentra el jugador y le doy el caracter 0.
		//debido a que en la matriz, las posiciones en rows van de 0 a dimy-1 y en columns de 0 a dimx, pero las coordenadas en x van de 1 a dimx y en y de 1 a dimy
		//para seleccionar la celda en la posicion del jugador es necesario restar - 1 a las coordenadas.
		if(map->rows[brush->coordY-1].pixels[brush->coordX-1].character == RELIC) //En caso en que pasemos por encima de una reliquia, decrementamos el contador.
		{
			(*items)--;
		}
		map->rows[brush->coordY - 1 ].pixels[brush->coordX - 1].character = 0; 

	}
}

Scene* Search_Scene_By_Id(Scene* mainScene, int id)
{	//Recorre la lista hasta encontrar la escena cuyo id concuerda con el parametro dado y la retorna.
	Scene* Aux = mainScene;
	while(Aux) 
	{
		if(Aux->id == id)
		{
			return Aux;
		}
		else
		{
			Aux = Aux->next;
		}
	}
	return NULL;
}

void Save_Level (Scene* Aux, Header * header)
{
	FILE * file;

	file = fopen(FILESTRING, "w+b");

	//Guardo en Cabecera: cantidad de Escenas, y Dimesiones Generales.

	fwrite(header, sizeof(Header),1,file);	//Escribe la cabecera en el archivo binario.
	while(Aux){				//Se guarda en el archivo todas las escenas de la lista enlazada.

		fwrite(Aux, sizeof(Scene), 1, file);	//Guarda la estructura completa en el archivo.

		for(int i = 0; i<Aux->map->dimy;i++)
	 	{

			for(int j = 0; j< Aux->map->dimx; j++)
			{
					
				fwrite(&Aux->map->rows[i].pixels[j], sizeof(Pixel), 1, file);	//Guarda cada Pixel del mapa de la escena actual.
			}
			
		}
		
		Aux = Aux->next;
	}
	rewind(file);	
 	fclose(file);
}

Scene* Load_All_Scenes(int* items)
{
	int amount, dimy, dimx;
	Header header;
	FILE* file;
	file = fopen(FILESTRING, "rb");	//Se abre el archivo como lectura.

	if(file == NULL)	//Si el archivo es nulo, es decir no existe, esta funcion retorna nulo.
		return NULL;
	
	fread(&header, sizeof(Header), 1, file);	//Se recupera la cabecera del archivo.
	
	*items = header.items;	//Se asigna la cantidad de reliquias.

	//Inicia el proceso de reconstruccion del nivel.

	Scene * Aux ; 			//Puntero a Scene que se emplea para recrear la lista nelazada de escenas.
	Scene * Start;			//Puntero a Scene que apuntara al inicio de la escena.
	
	Aux = Load_Scene(file,  header.dimy, header.dimx);	//Se carga la primera escena del archivo.	
	Aux->next = NULL;
	Start = Aux;			//Se asigna el inicio de la lista.

	for(int i = 1; i < header.amountScenes; i++)	// Para cada escena (especificada en la cabecera) se carga la escena desde el archivo.
	{	
		Aux->next = Load_Scene(file,  header.dimy, header.dimx);
		Aux = Aux->next;
		Aux->next = NULL;
	}
	rewind(file);
	fclose(file);

	return Start;		//Retorna el inicio de la lista recuperada.
}

Scene * Load_Scene(FILE *file, int dimy, int dimx)
{

	Scene* Aux = (Scene *) Save_Memory(sizeof(Scene));	//Crea un puntero a una reserva de  memoria de tamanio Scene que se usara para recuperar la escena.
	fread(Aux, sizeof(Scene), 1, file);					//Se lee del archivo la escena almacenada.
	
	Aux->map = (Map *) Save_Memory (sizeof(Map));		// Crea un puntero a una reserva de  memoria de tamanio Map y se la asigno al puntero map de la estructura scene a la que apunta el puntero New_Scene.
	Aux->map->dimy = dimy;								//Se asignan los valores de las dimensiones (que han sido guardados en la cabecera).
	Aux->map->dimx = dimx;
	Aux->map->rows = (Rows *)Save_Memory(sizeof(Rows) * Aux->map->dimy);//Reserva memoria del vector de filas.
	
	for(int i = 0; i< Aux->map->dimy;i++)				//Luego, para cada Pixel almacenado en el archivo, se lo recupera y asigna a cada Pixel del mapa de la escena recuperada.
 	{
 		Aux->map->rows[i].pixels = (Pixel *)Save_Memory(sizeof(Pixel) * Aux->map->dimx);

		for(int j = 0; j< Aux->map->dimx; j++)
		{
	
			fread(&Aux->map->rows[i].pixels[j], sizeof(Pixel), 1, file);
		
		}
	}
	
	return Aux;		//Se obtiene la escena recontruida, y se la retorna.
}

int Get_Amount_Scenes(Scene * scene)
{
	Scene * Aux;	//Puntero que se usara para recorrer la lista enlazada.
	Aux = scene;	//Se asigna este puntero al puntero de la escena a partir de la cual se desea contar.
	int count = 0;	//Contador.

	while(Aux)		//Hasta que el auxiliar sea nulo (la lista termine) se aumenta el contador y se modifica el puntero .
	{
		count++;
		Aux = Aux->next;
	}
	return count;
}

void Modify()
{
	
	int sceneId;	//varibale que almacena el id de la escena que se desea modificar.

	Header header;	//Instancia de cabecera, se emplea para guardar nuevamente el archivo.
	
	Scene * mainScene = Load_All_Scenes(&header.items);		//Carga todo el nivel
	if(mainScene == NULL){
		printf("\nERROR! No existe ningun juego creado, por favor cree un nuevo juego.");
			
		return;
	}
	header.amountScenes = Get_Amount_Scenes(mainScene);		//Asigna los valores correspondientes al header
	header.dimx = mainScene->map->dimx;
	header.dimy = mainScene->map->dimy;

	do{														//Se pide al usuario cual escena desea modificar.
		clrscr();
		printf("Su Juego posee %d habitaciones o escenas, escriba el numero de la escena que desea modificar: ", header.amountScenes);
		scanf("%d", &sceneId);
	}while(sceneId>header.amountScenes || sceneId <= 0);

	Scene* scene1 = Search_Scene_By_Id(mainScene, sceneId);		//Se busca, dentro de la lista recuperada, el nivel que se desea modificar.

	Modify_Scene(mainScene, scene1, &header.items, header.amountScenes);				//Se redibuja el mapa y se modifica usando las funciones como ya se uso antes para dibujar el nivel por primera vez.

	
	Save_Level(mainScene, &header);								//Se guarda todo el nivel nuevamente.
	
	clrscr();
}

void Modify_Scene(Scene * mainscene, Scene * scene, int * items, int amount)
{
	Brush  brush;								//Se instancia un pincel.
	brush.coordX = scene->map->dimx/2;			//Se inicializa las coordenadas del pincel en aproximadamente el centro.
	brush.coordY = scene->map->dimy/2;			
	brush.character = BRUSH;					//Se inicializa el caracter del pincel.
	brush.brushhead = WALL;						//Se inicializa la cabeza del pincel.

	char c;										//Variable que se empleara en algunos casos para seleccion de opciones.
	int key;									//tecla que se presiona.

	
	do{											//Se le pregunta al jugador si desea volver a configurar las puertas de esta escena.
		clrscr();
		printf("Desea modificar la configuracion de puertas? (y/n)" );
		c = getch();
	}while(c != 'y' && c != 'n');
	if(c == 'y'){								//En caso de que se elija y, se vuelve a pedir la configuracion de las puertas como se hizo antes.

		do
		{
			printf("\nIngrese el id de la puerta 1: ");
		
			scanf("%d", &scene->door1id);

		}while(scene->door1id < 0 || scene->door1id > amount || scene->door1id == scene->id);

		do
		{
			printf("\nIngrese el id de la puerta 2: ");
		
			scanf("%d", &scene->door2id);

		}while(scene->door2id < 0 || scene->door2id > amount || scene->door2id == scene->id);

		do
		{
			printf("\nIngrese el id de la puerta 3: ");
		
			scanf("%d", &scene->door3id);

		}while(scene->door3id < 0 || scene->door3id > amount || scene->door3id == scene->id);

		do
		{
			printf("\nIngrese el id de la puerta 4: ");
		
			scanf("%d", &scene->door4id);

		}while(scene->door4id < 0 || scene->door4id > amount || scene->door4id == scene->id);
		
		

		
	}
	
	do{											//Se le pregunta al jugador si desea modificar el mapa.
		clrscr();
		printf("Desea modificar el mapa? (y/n)" );
		c = getch();
	}while(c != 'y' && c != 'n');

	if(c == 'y'){								//En caso de decir que si, se dibuja nuevamente el mapa, y se le permite modificar.
		Draw_Map(scene->map);					//Se dibuja el mapa recuperado.
		
		printf("\n\nESCENA %d" ,scene->id);
		printf("\n");

		Draw_Palette();							//Se dibuja la paleta
		

		do{		
			Generate_Way(scene->map, &brush, items);//Guarda en la matriz del mapa, un espacio vacio en las coordenadas del pincel.
				
			Draw_Brush(&brush);					//Dibuja el pincel en sus coordenadas
			
			key = getch(); 						//Guarda la tecla presionada.
			
			Input_Check_Brush(scene->map, &brush, &key, items);// De ser necesario, mueve el pincel o pinta una pared.	
		}
		while(key != 27); 						//Se repite hasta que se presione ESC, lo cual termina el proceso de creado de una escena.
		
	}
	clrscr();	
}

void Menu()
{
	
	Scene * mainScene;					//Puntero que se empleara para cargar un nivel, o crear uno desde cero.
	int items;							//Cantidad de items
	int option;							//Opcion de menu
	option = 0;							//Opcion por defecto lleva al menu principal.

	do{
		switch(option)					//Analiza la variable opcion y deacuerdo a ella, se mueve a travez del menu.
		{	case 0:						//Menu Principal.
				clrscr();
				printf("		 ___________________________________________\n");
				Sleep(100);
				printf("		|                                           |\n");
				Sleep(100);
				printf("		|                   DUNGEONS                |\n");
				Sleep(100);
				printf("		|___________________________________________|\n\n");
				Sleep(100);
				printf("------------------------------------ MENU -------------------------------------\n\n");
				Sleep(100);		
				printf("	1 -  Jugar\n");
				Sleep(100);
				printf("	2 -  Crear un nuevo Juego (Sobreescribe el Juego actual)\n");
				Sleep(100);
				printf("	3 -  Modificar Mapa\n" );
				Sleep(100);
				printf("	4 -  Ayuda\n" );
				Sleep(100);
				printf("	5 -  Salir\n\n\n");
				Sleep(100);
				printf("Presione el numero correspondiente a la opcion deseada: ");
				scanf("%d", &option);
				break;
			case 1:
				mainScene = Load_All_Scenes(&items);
				if(mainScene == NULL){
					printf("ERROR! No existe ningun juego creado, por favor cree un nuevo juego.\nPulse cualquier tecla para continuar...");
					getch();
					option = 0;
					break;
				}
				
				clrscr();
				char c;
				if(GameLoop(mainScene, &items))
				{
					do{
						clrscr();
							printf("		 ___________________________________________\n");
							Sleep(100);
							printf("		|                                           |\n");
							Sleep(100);
							printf("		|                  HAS GANADO!              |\n");
							Sleep(100);
							printf("		|___________________________________________|\n\n");
							Sleep(100);
						printf("\n\nDeseas volver a jugar? (y/n) : ");

						c = getch();
						if(c == 'y')
							option = 1;
						else if (c == 'n')
							option = 0;
						
					}while(c != 'y' && c != 'n');
				}
				else
				{
					
					do{
						clrscr();
							printf("		 ___________________________________________\n");
							Sleep(100);
							printf("		|                                           |\n");
							Sleep(100);
							printf("		|                 HAS PERDIDO!              |\n");
							Sleep(100);
							printf("		|___________________________________________|\n\n");
							Sleep(100);
						printf("\n\nDeseas volver a jugar? (y/n) : ");

						c = getch();
						if(c == 'y')
							option = 1;
						else if (c == 'n')
							option = 0;
						
					}while(c != 'y' && c != 'n');
				}
			break;
			case 2:
				clrscr();
				mainScene = Create_Level();
				option = 0;
			break;
			case 3:

				Modify();
				printf("\n\nPresione cualquier tecla para volver al Menu Principal.");
				getch();
				option = 0;

			break;
			case 4:
				clrscr();
				printf("		 ___________________________________________\n");
				Sleep(100);
				printf("		|                                           |\n");
				Sleep(100);
				printf("		|                   DUNGEONS                |\n");
				Sleep(100);
				printf("		|___________________________________________|\n\n");
				Sleep(100);
				printf("------------------------------------ AYUDA ------------------------------------\n\n");
				Sleep(100);
				printf("	1 -  Como Jugar?\n");
				Sleep(100);
				printf("	2 -  Como Crear un Nivel?\n");
				Sleep(100);
				printf("	3 -  Atras\n\n\n");
				Sleep(100);
				printf("Presione el numero correspondiente a la opcion deseada: ");
				scanf("%d", &option);
				clrscr();
				
				switch(option)
				{
					case 1:
						HowToPlay(&option);
					break;
					case 2:
						HowToCreate(&option);
					break;
					case 3:
						option = 0;
					break;
					default:
						option = 4;
					break;	
				}
			break;
			case 5:
				option = -1;
			break;
			default:
				option = 0;
			break;
		}
	}while(option != -1);
	char c;
	do{
		clrscr();
		printf("Esta seguro que desea salir? (y/n) : ");

		c = getch();
		if(c == 'y')
			break;
		else if (c == 'n')
			Menu();
	}while(c != 'y' && c != 'n');
	clrscr();
}
void HowToPlay(int * option)
{
	Sleep(100);
	printf("------------------------------------ COMO JUGAR --------------------------------\n\n");
	Sleep(100);
	printf("Dungeons es un juego de estrategia y exploracion, que consiste en moverse a traves de diversas habitaciones, y en donde deberemos lograr esquivar o atrapar a los temibles dragones que intentaran detenernos en nuestro deber por recuperar las sagradas reliquias.\n\nEl objetivo del juego es recuperar todas las reliquias (%c), una por vez, y devolverlas a la zona de entrega (%c). Para ello nos moveremos con las flechas de keydo.\n\nEn cada habitacion es posible encontrar dragones (%c) quienes seguiran nuestros Brush_Movements hasta encontrarnos, los dragones pueden volar por encima de las paredes por lo que no tendran problemas en encontrarnos.\n\nLa unica manera para deterlos es atraerlos a las zonas magicas (%c) en donde no podran moverse.\n\nCUIDADO!, un dragon atrapado sigue vivo, por lo que si lo tocamos nos matara!.\n\nEl juego terminara cuando hayamos devuelto todas las reliquias a las zonas de entrega (%c)\n\nREFERENCIAS:\n\n   %c  -  Jugador sin Reliquia\n\n   %c  -  Jugador con Reliquia\n\n   %c  -  Reliquias\n\n   %c  -  Zona de Entrega\n\n   %c  -  Dragones\n\n   %c  -  Zonas Magicas\n\n", RELIC, DELIVERYZONE, DRAGON, TRAP, DELIVERYZONE, PLAYEREMPTY, PLAYERFULL, RELIC, DELIVERYZONE, DRAGON, TRAP);
	Sleep(100);
	printf("\nPresione cualquier key para volver...");
	getch();
	*option = 4;
}
void HowToCreate(int *option)
{
	printf("------------------------------------ COMO CREAR --------------------------------\n\n");
	Sleep(100);
	printf("La creacion de mapas es una herramienta que le permitira crear un nivel completo, con todas sus habitaciones o escenas, enemigos, trampas y metas.\n Es recomendable que antes de crear un nivel, tenga en claro cuantas habitaciones tendra y como estas se conectaran entre ellas.\n Al iniciar se le pedira el numero de escenas o habitaciones de su nivel, este numero debe ser un numero entero y positivo.\n Luego debera ingresar la cantidad de filas y columnas que determinaran las dimensiones de todas las habitaciones.\n Hecha la inicializacion principal, la herramienta comenzara a pedirle informacion sobre cada escena en particular. El editor mostrara el numero de identificacion de la escena en la leyenda 'ESCENA X' donde X sera el numero que identifica a la escena actual.\n Este numero es de vital importancia para pasos siguientes y debera tener en cuenta que la ESCENA 1 sera siempre la escena principal en donde aparecera el jugador por primera vez.\n Se le pedira que ingrese un nombre para la escena actual, y luego se le pedira la configuracion de puertas la cual se vera a continuacion:\n\n Supongamos las siguientes escenas .\n\n");
	Sleep(100);
	printf(" ____________        ____________\n");
	Sleep(100);
	printf("|            |      |            |\n");
	Sleep(100);
	printf("|            |      |            |\n");
	Sleep(100);
	printf("|  ESCENA 1  |      |  ESCENA 4  |\n");
	Sleep(100);
	printf("|            |      |            |\n");
	Sleep(100);
	printf("|            |      |            |\n");
	Sleep(100);
	printf("|____________|      |____________|\n");
	Sleep(100);
	printf("\n Podemos ver que tenemos 2 escenas, la escena con id 1 y otra con id 4... Supongamos que deseamos que cuando el jugador pase por una puerta que se escuentra a la derecha en la escena 1, pase a la escena 4. Esto significaria que la escena 1 y la cuatro estan conectadas por una puerta que esta a la derecha de escena 1 y a la izquierda de escena 4.\n Para poder comprender como configurar esto en la herramienta de creacion debemos tener en mente el siguiente esquema de configuracion, valido para todas las habitaciones:\n\n");
	Sleep(100);
	printf("               Puerta 1  \n");
	Sleep(100);
	printf("                  ^  \n");
	Sleep(100);
	printf("                  |  \n");
	Sleep(100);
	printf("             ____________ \n");
	Sleep(100);
	printf("            |            |\n");
	Sleep(100);
	printf("            |            |\n");
	Sleep(100);
	printf("Puerta 4 <--|  ESCENA X  |--> Puerta 2\n");
	Sleep(100);
	printf("            |            |\n");
	Sleep(100);
	printf("            |            |\n");
	Sleep(100);
	printf("            |____________|\n");
	Sleep(100);
	printf("                  |  \n");
	Sleep(100);
	printf("                  v  \n");
	Sleep(100);
	printf("               Puerta 3  \n");
	Sleep(100);
	printf("\n De esta manera, la herramienta preguntara, para la escena 1, 2, ... y asi sucesivamente, que habitacion se encuentra en la puerta 1, 2, 3 y 4; a lo cual deberemos responder ocn el numero de id de la habitacion contigua. Es importante recalcar que si una habitacion no tiene coneccion en una de sus puertas se ha de ingresaar el id 0. De esta forma, para el ejemplo, la configuracion a ingresar para la escena 1 sera: \n\n Puerta 1: 0\n Puerta 2: 4  (id de la escena 4)\n Puerta 3: 0\n Puerta 4: 0\n\n Y para la escena 4:\n\n Puerta 1: 0\n Puerta 2: 0\n Puerta 3: 0\n Puerta 4: 1\n\n De esta forma quedaran vinculadas ambas habitaciones por una puerta en comun.\n\n Reiteramos, es conveniente tener disenada la configuracion de antemano para hacer este proceso lo mas facil posible.\n\n");
	Sleep(100);
	printf("\n Con esto hemos acabado como configurar una escena, a continuacion se explicara como dibujar una escena:\n\n Se le presentara un rectangulo de las dimensiones especificadas, pintado de blanco, especificamente del caracter %c (Paredes) que representa paredes, y en el medio, el caracter  %c (pincel) que representara su pincel. Por defecto el pincel pinta caminos, es decir zonas negras que pueden ser caminadas por el jugador. Para pintar un camino debera mover el pincel con las FLECHAS del teclado. No podra salirse de los limites antes preestablecidos.\n Podra notar en la parte inferior una leyenda con el nombre elegido de la escena y su identificador, seguido de una paleta. Esta paleta le permitira dibujar elementos diferentes a los caminos.\n\n Para elegir un elemento a pintar debera presionar el numero correspondiente a ese elemento siguiendo la paleta o la siguiente referencia:\n\n 1 => %c => Paredes\n 2 => %c => Dragones\n 3 => %c => Reliquias\n 4 => %c => Zona de Entrega\n 5 => %c => Trampas\n", WALL, BRUSH, WALL, DRAGON, RELIC, DELIVERYZONE, TRAP);
	Sleep(100);
	printf("\n Finalmente para pintar cualquier elemento diferente de un camino, debera presionar las teclas W, A, S o D dependiendo de la direccion en donde desea pintar, siendo estas arriba, izquierda, abajo, o derecha correspondientemente. \n Recuerde tener en cuenta las puertas configuradas ya que si se configura una puerta, pero no se dibuja un camino que permita al jugador llegar al borde correspondiente, este ninca podra llegar a la habitacion contigua.\n Una vez dibujada la primera escena, presiones la tecla ESC, esta s eguardara, y se repetira todo el proceso hasta hacer todas las habitaciones. \n\n Algo muy importante es que debera OBLIGATORIAMENTE colocar al menos una reliquia Y una zona de entrega para que su nivel se pueda jugar adecuadamente y ganar, de lo contrario su nivel jamas podra ser ganado.\n\n Recuerde que cualquier error podra ser corregido luego con la opcion Modificar Nivel, que se encuentra en el menu principal, la cual usa el mismo procedimiento descripto en esta seccion, excepto que se le pedira la escena especifica a modificar por lo que debera entrar a esta herrmaienta cada vez que desee modificar una escena distinta.\n\n ");
	Sleep(100);
	printf("\nPresione cualquier key para volver...");
	getch();
	*option = 4;
}


//*******	GAME	********




bool GameLoop(Scene * mainScene, int *items)
{
	int key;										//Variable que contendra la tecla presionada.
	int totalItems = *items;						//Variable que retiene la cantidad de reliquias a recoger.
	Jugador jugador;								//Instancia del Jugador.
	Scene* currentScene = mainScene;				//Puntero que apunta a la escena actual de la lista. Inicializada en la escena principal.
	Scene* Aux;										//Puntero que se usara para

	jugador.character = PLAYEREMPTY;				//Inicializacion del jugador.
	jugador.coordX = mainScene->map->dimx/2;
	jugador.coordY = mainScene->map->dimy/2;
	Enemy* enemies[50];								//Se crea un vector de puntero a enemigos con un tamano maximo de 50
	int countEnemy;									//Contador de enemigos.
	bool finish = false;							//Variable que indica si el juego termino, de ser verdadera significa que el jugador perdio.
	bool win = false;								//Variable que indica si el jugador consiguio el objetivo.
	
	clrscr();
	Draw_Map(mainScene->map, enemies, &countEnemy);	//Se dibuja el mapa recuperado. Se carga el vector enemies con los enemigos del mapa, y se carga el contador de enemigos.

	gotoxy(1, mainScene->map->dimy + 2);					//Se imprime en pantalla la cantidad de reliquias faltantes para ganar.
	printf(" Cantidad de Reliquias Entregadas: %d / %d", (totalItems - *items), totalItems);

	gotoxy(jugador.coordX, jugador.coordY); 		//Se dibuja al jugador.
	printf("%c", jugador.character);

	do
	{	

		key = getch();								//Se obtiene la tecla presionada
		if(key == 27)								//Si es ESC el juego termina.
		{
			clrscr();
			return false;
		}

		gotoxy(jugador.coordX, jugador.coordY); 	//Se ubica el cursor en las coordenadas del jugador

		if(currentScene->map->rows[jugador.coordY-1].pixels[jugador.coordX-1].character != WALL){	
			if(currentScene->map->rows[jugador.coordY-1].pixels[jugador.coordX-1].character == DRAGON)
				printf("%c", 0);
			else
				printf("%c", currentScene->map->rows[jugador.coordY-1].pixels[jugador.coordX-1].character);
		}
		else
			printf("%c", 0);


		if(key == 72||key==75||key==80||key==77)	//Se checkea si la tecla corresponde a las de movimiento (flechas)
		{

			switch (key) 							//Analizo la tecla presionada. 
			{	//las coordenadas en x aumentan hacia la derecha. Las coordenadas en y aumentan hacia abajo. 
				case 72: //arriba
					
					if(jugador.coordY > 1)			//Se verifica que no se este saliendo del mapa
					{
						if(currentScene->map->rows[jugador.coordY-2].pixels[jugador.coordX-1].character != WALL)//Se verifica que no este chocando con una pared.
						{
							jugador.coordY --;
						}
					}
					else 							//En caso de estar en un borde...
					{
						Aux = Search_Scene_By_Id(mainScene, currentScene->door1id);	// Se busca en la configuracion de la escena actual, el id de la puerta corresppondiente y se recupera la escena correspondiente.
						if(Aux != NULL)				//Si el id de la puerta era 0, la funcion anterior retorna null y por ende no se ejecuta este if.
						{
							currentScene = Aux;		//Se cambia la variable de escena actual.
							jugador.coordY = currentScene->map->dimy;	//Se espeja la posicion del jugador en el eje correspondiente.
							Draw_Map(currentScene->map, enemies, &countEnemy);//Se dibuja el nuevo mapa.

						}
					}
					break;


				case 75://izquierda
					if(jugador.coordX > 1)
					{
						if(currentScene->map->rows[jugador.coordY-1].pixels[jugador.coordX-2].character != WALL)
							jugador.coordX --;
						
					}
					else
					{
						Aux = Search_Scene_By_Id(mainScene, currentScene->door4id);
						if(Aux != NULL)
						{
							currentScene = Aux;
							jugador.coordX = currentScene->map->dimx;
							Draw_Map(currentScene->map, enemies, &countEnemy);

						}
					}
					break;
				
					
				case 80://abajo
					if(jugador.coordY < currentScene->map->dimy)
					{
						if(currentScene->map->rows[jugador.coordY].pixels[jugador.coordX-1].character != WALL)
							jugador.coordY ++;
					}
					else
					{
						Aux = Search_Scene_By_Id(mainScene, currentScene->door3id);
						if(Aux != NULL)
						{
							currentScene = Aux;
							jugador.coordY = 1;
							Draw_Map(currentScene->map, enemies, &countEnemy);

						}
					}
					break;
				

				case 77://derecha

					if(jugador.coordX < currentScene->map->dimx ){
						if(currentScene->map->rows[jugador.coordY-1].pixels[jugador.coordX].character != WALL)
							jugador.coordX ++;
					}
					else
					{
						Aux = Search_Scene_By_Id(mainScene, currentScene->door2id);
						if(Aux != NULL)
						{
							currentScene = Aux;
							jugador.coordX = 1;
							Draw_Map(currentScene->map, enemies, &countEnemy);

						}
					}
					break;						

			}

			if(currentScene->map->rows[jugador.coordY-1].pixels[jugador.coordX-1].character == RELIC)	//Si el jugador pasa sobre una reliquia...
			{
				if(jugador.character == PLAYEREMPTY)				//Y ademas, no posee antes otra reliquia.
				{
					currentScene->map->rows[jugador.coordY-1].pixels[jugador.coordX-1].character = 0;	//Se borra la reliquia del mapa.
					jugador.character = PLAYERFULL;					//Se le asigna al caracter del jugador el valor de lleno para indicar que posee una reliquia.
				}
			}


			if(currentScene->map->rows[jugador.coordY-1].pixels[jugador.coordX-1].character == DELIVERYZONE){	//Si el jugador se encuentra en la zona de entrega...
				if(jugador.character == PLAYERFULL)					//Y ademas, tiene una reliquia
				{
					jugador.character = PLAYEREMPTY;				//Se le asigna el caracter de vacio al jugador para indicar que ya no posee la reliquia.
					*items -= 1;									//Se disminuye la cantidad de reliquias y se vuelve mostrar la cantidad faltante.
					gotoxy(1, mainScene->map->dimy + 2);
					printf(" Cantidad de Reliquias Entregadas: %d / %d", (totalItems - *items), totalItems);
					if(*items == 0)									//Si la cantidad de reliquias es 0, el jugador ha ganado.
					{
						win = true;
					}
				}
				
			}
			

			for(int i = 0; i < countEnemy; i++)						//Para cada enemigo en el vector enemies
			{	
				if(Enemy_Movement(enemies[i], &jugador, currentScene->map))	//se llama a la funcion que maneja el movimiento de cada enemigo.
				{
					finish = true;									//la funcion anterior devuelve verdadero si un enemigo toca al jugador, por lo que el juego termina.

				}
			}
					

		}
		
		gotoxy(jugador.coordX, jugador.coordY); 					//Se dibuja al jugador.		
		printf("%c", jugador.character);


		if(win)														//Se verifica si el jugador ha ganado.
		{
			clrscr();
			printf("		 ___________________________________________\n");
			printf("		|                                           |\n");
			printf("		|                  HAS GANADO!              |\n");
			printf("		|___________________________________________|\n\n");
			return true;
		}


	}while(!finish);												//Se repite hasta que el jugador pierda.


	clrscr();
	printf("		 ___________________________________________\n");
	printf("		|                                           |\n");
	printf("		|                 HAS PERDIDO!              |\n");
	printf("		|___________________________________________|\n\n");
	return false;
}


bool Enemy_Movement(Enemy * enemy, Jugador * jugador, Map * map)
{
	int	diffX, diffY;					//Funcion que contiene las diferencias de posicion entre el jugador y el enemigo.
	if(map->rows[enemy->coordY-1].pixels[enemy->coordX-1].character != TRAP) //Si el enemigo no esta en una trampa.
	{														//Se calculan las diferencias como valores absolutos.
		diffX = abs(jugador->coordX - enemy->coordX);
		diffY = abs(jugador->coordY - enemy->coordY);

		gotoxy(enemy->coordX, enemy->coordY);				//Ubico el cursor en la posicion del enemigo.

		if(map->rows[enemy->coordY-1].pixels[enemy->coordX-1].character == DRAGON)	//Si en la posicion del enemigo, el mapa contiene el dibujo del enemigo, entonces dibujo vacio.
			printf("%c", 0);														//Esto es para que al moverse el enemigo, deje un rastro vacio.
		else
			printf("%c", map->rows[enemy->coordY-1].pixels[enemy->coordX-1].character);//Si en la posicion del enemigo, el mapa contiene cualquier otro caracter, entonces se dibuja ese caracter.

		if(diffX >= diffY)									//Se analiza cual de las diferencias es mayor, el enemigo intentara acortar la mayor distancia.
		{
			if(enemy->coordX > jugador->coordX)				//Analiza la coordenada correspondiente entre jugador y enemigo para comprobar hacia donde debe moverse.
			{
				enemy->coordX--;
			}
			else if(enemy->coordX < jugador->coordX)
			{
				enemy->coordX++;
			}
		}
		else
		{
			if(enemy->coordY < jugador->coordY)
			{
				enemy->coordY++;
			}
			else if(enemy->coordY > jugador->coordY)
			{
				enemy->coordY--;
			}
		}

		if(enemy->coordX == jugador->coordX && enemy->coordY == jugador->coordY)	//Si la posicion del enemigo y del jugador son iguales, el jugador pierde.
			return true;

		gotoxy(enemy->coordX, enemy->coordY);				//Ubico el cursor en la posicion del enemigo
		
		printf("%c", DRAGON);								//Dibujo al enemigo.

	}
	else
	{
		if(enemy->coordX == jugador->coordX && enemy->coordY == jugador->coordY)
			return true;
	}

	return false;
}

//*******	OTHERS	********


void * Save_Memory(int amount)
{
	void * pAux;
	

	if((pAux = malloc(amount)) == NULL)
	{
		printf("No pudo reservar memoria dinamica");
		getch(); 
		exit(1);
	}
	return pAux;
}


void HideCursor()
{
	CONSOLE_CURSOR_INFO cci = {100 , FALSE};

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}