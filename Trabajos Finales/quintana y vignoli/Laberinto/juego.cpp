#include "maze_v2.h"

void main(){
	header destino, origen;
	MAP maze;
	unsigned int num_mapas, x;
	JUGADOR p1;
	PUNTO end, start;// Se usara para comprobar si el jugador llego al final
	char * map_temp, score_string[6];
	char * source;

	step * camino;

	int old_score, score;
	FILE * mapa;
	bool new_higscore = true;

	bool sigue = true; //Se usa para comprobar si el usuario quiere volver al menu o salir

	do
	{
		do
		{
			clrscr();
			Sleep(50);
			printf("Bienvenido al Laberinto:\n");
			printf("1- Elegir un mapa\n");
			printf("2- Instrucciones\n");
			printf("3- Salir\n");
			scanf("%d", &x);
		} while (x != 1 && x != 2 && x != 3);
		if (x == 1)
		{
			//Abro el archivo con la cantidad de mapas
			num_mapas = check_for_maps();

			fflush(stdin);
			clrscr();

			if (num_mapas > 0)
			{	
				do{
					list_maps(num_mapas, &map_temp);
				}
				while ((mapa = fopen(map_temp, "rb")) == NULL && map_temp[0] != 1); //Uso el caracter '!' como control de si desea salir

				if (map_temp[0] != 1)
				{
					//Si elige un numero valido
					clrscr();
					fread(&origen, sizeof(header), 1, mapa);//Toma la cabecera

					source = (char *)ReservarMemoria((origen.dim_x * origen.dim_y + 1) * sizeof(char));//Reservo memoria para la "fuente" (el arreglo donde esta guardado el mapa en si)
					fseek(mapa, TAM_CABECERA, SEEK_SET);//Salto la cabecera
					fgets(source, origen.dim_x * origen.dim_y + 1, mapa);//Leo la fuente

					maze = new_map(origen.dim_x, origen.dim_y);//Inicializo el mapa

					pregen_maze(source, &maze);//Lo genero desde la fuente
				}
			}else{
				printf("No hay mapas\n");
				getch();
				exit(1);
			}

			if (map_temp[0] != 1)
			{
				p1 = nuevo_jugador(origen.start);//Inicializo el jugador en el inicio

				Oculta_cursor();


				//Comienzo el juego
				score = GameLoop(p1, origen.start, origen.end, maze, &camino);


				//Analizo si el puntaje que esta guardado en el archivo es mejor q el actual
				fseek(mapa, TAM_CABECERA, SEEK_SET);//Salto cabecera
				fseek(mapa, origen.dim_x * origen.dim_y, SEEK_CUR);//Salto la fuente
				fgets(score_string, sizeof(int)*5, mapa);//Tomo el puntaje
				old_score = atoi(score_string);//Lo traduzco a un entero

				if (score < old_score)
				{
					//Cierro el archivo y lo abro en escritura para borrar todo
					fclose(mapa);
					mapa = fopen(map_temp, "w+b");//Uso el nombre del archivo que tengo en la variable map_temp

					//Reescribo todo con el puntaje nuevo
					fwrite(&origen, sizeof(header), 1, mapa);//Escribo la cabecera que tengo en el archivo

					//Salto cabecera y guardo la fuente
					fseek(mapa, TAM_CABECERA, SEEK_SET);
					fputs(source, mapa);
					sprintf(score_string, "%4d", score);//Coloco el nuevo puntaje en un string
					fputs(score_string, mapa);			//Guardo el string en el archivo
				}else{
					new_higscore = false;//Si el nuevo puntaje es peor que el que esta en el archivo pongo esta bandera en falso
				}
				//Cierro el archivo
				fclose(mapa);

				//Hago el replay
				printf("Desea ver la replay? (s/n)\n");
				if (getch() == 's')
				{
					clrscr();
					Replay(maze, p1, camino, origen.start, origen.end);
				}


				//Imprimo el mensaje de final del juego
				do{
					clrscr();
					printf("FELICIDADES, GANASTE!!!!\r\n");
					printf("Tu puntaje es: %d\r\n", score);
					if (new_higscore)
						printf("Nuevo mejor puntaje!\r\n");
					else
						printf("El mejor puntaje en este mapa es: %d\r\n", old_score);
					printf("Presiona \"Esc\" para salir\r\n");
					fflush(stdin);
				}while(getch()!= 27);
			}else
				clrscr();
		}else
			if (x == 2)
			{
				do{
					clrscr();
					printf("Instrucciones:\n\n");
					printf("Despues de elegir una de las opciones del selector de niveles, el mapa se abrira\ny podra empezar el juego.\n");
					printf("Su personaje es representado por el caracter \"%c\", puede atravesar los bloques \"%c\",\nlos bloques \"%c\" son paredes y no pueden ser atravesados.\n", CAR_JUG_CENTRO, CAR_VACIO, CAR_PARED);
					printf("El objetivo del juego es llegar de la entrada, maracada por el caracter \"");
					textcolor(RED);
					cprintf("%c", CAR_PUERTA);
					printf("\"\na la salida, marcada por el caracter \"");
					textcolor(LIGHTGREEN);
					cprintf("%c", CAR_PUERTA);
					printf("\", mientras recolecta la mayor cantidad de\npremios que pueda, marcados por el caracter \"");
					textcolor(YELLOW);
					cprintf("%c", CAR_PREMIO);
					printf("\".\n\n\n");
					printf("Presione ENTER para continuar\n");
				}while(getch() != ENTER);
			}else{
				sigue = false;
			}
	} while (sigue);
}