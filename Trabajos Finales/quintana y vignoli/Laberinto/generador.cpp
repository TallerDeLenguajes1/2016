#include "maze_v2.h"

void main(){
	MAP maze;
	unsigned int seed, x, num_mapas, dimx, dimy, tecla;
	PUNTO end, start;// Se usara para comprobar si el jugador llego al final
	char map_ext[6] = "1.dat\0";
	char name[20]; //Digo que los nombres seran de 20 caracteres
	char map_access[13] = "mapa_";
	char aux[13], aux2[3], score_string[5];
	char * source;
	header destino;

	JUGADOR p1;
	FILE * manager, * mapa;

	bool sigue = true; //Se usa para comprobar si el usuario quiere volver al menu o salir

	do
	{
		do
		{
			clrscr();
			printf("Bienvenido al generador de laberintos Retro-rastreador\n\n");
			printf("1- Comenzar a crear un mapa\n");
			printf("2- Instrucciones\n");
			printf("3- Salir\n");
			printf("Presione el numero correspondiente a la opcion deseada: ");
			scanf("%d", &x);
		} while (x != 1 && x != 2 && x != 3);

		if (x == 1)
		{
			//Abro o genero el archivo con la cantidad de mapas (lo abro en lectura para que me de NULL si no existe)
			num_mapas = check_for_maps();

			fflush(stdin);

			//Cargo el nombre del mapa
			printf("Como se llamara el mapa? \n");
			gets(name);


			//Cargo las dimensiones del mapa
			printf("Cuantas columnas tendra el laberinto (Contando paredes y pared externa)? ");
			scanf("%d", &dimx);
			if (dimx % 2 == 0)
			{
				dimx++;
			}

			printf("Cuantas filas tendra el laberinto (Contando paredes y pared externa)? ");
			scanf("%d", &dimy);
			if (dimy % 2 == 0)
			{
				dimy++;
			}

			clrscr();
			do
			{
				printf("Que desea hacer?\n1 Generar un mapa aleatoriamente\n2 Dibujar un mapa\n\n");
				scanf("%d", &x);
				clrscr();
				printf("Por favor elija una de las opciones\n");
			}while(x != 2 && x != 1);

			if (x == 2)
			{
				maze = draw_map(dimx, dimy);
				print_unfinished_map(maze);

				gotoxy(1, dimy + 2);
				printf("Coloquese sobre donde quiere que sea el inicio y presione enter");
				dibujarjugador(p1 = nuevo_jugador(new_point(maze.dimx/2, maze.dimy/2)));
				p1.caracter = CAR_JUG_CENTRO;
				do
				{
					dibujarjugador(p1);
					tecla = getch();
					moverjugador(&p1, maze, tecla);
					fflush(stdin);
				}while(tecla != ENTER);

				start = p1.pos;

				print_unfinished_map(maze);
				gotoxy(1, dimy + 2);

				printf("Coloquese sobre donde quiere que sea el final y presione enter");
				p1.pos = new_point(dimx/2, dimy/2);
				p1.caracter = CAR_JUG_CENTRO;
				do
				{
					dibujarjugador(p1);
					tecla = getch();
					moverjugador(&p1, maze, tecla);
					fflush(stdin);
				}while(tecla != ENTER);

				end = p1.pos;
			}else{
				//Cargo la semilla
				printf("Cargue una semilla (si desea generar una aleatoria escriba -1) ");
				scanf("%d", &seed);
				if (seed == -1)
				{
					seed = (unsigned int) time(NULL);
				}
				srand(seed);

				//Para asegurarme que la entrada y salida esten solo en las casillas impares
				//hago que random vaya hasta dim / 2, luego la multiplico por 2
				//y finalmente le sumo uno, para que sea impar

				//Para simplificar empiezo siempre arriba
				start = new_point((random((dimx - 1)/2)*2) + 1, 0);

				//Y termino abajo
				end = new_point((random((dimx - 1)/2)*2) + 1, dimy - 1);

				maze = new_map(dimx, dimy);
				
				//Genero el mapa
				generate_maze(&maze, start, end);
				
			}

			//Una vez generado dibujo el mapa
			print_map(maze, start, end);

			//Al final escribo 
			gotoxy(1, maze.dimy + 2);
			printf("Asi resulta el mapa\n");
			printf("Desea Guardar? (s/n)\n");

			if (getch() == 's')
			{
				//Modifico el numero de mapas
				num_mapas++;

				if ((manager = fopen("Game Manager.dat", "w+b")) == NULL)
				{
					printf("No se pudo abrir manager de nuevo\n");
					getch();
					exit(1);
				}
				sprintf(aux2, "%d", num_mapas);
				fprintf(manager, "%s", aux2);

				fclose(manager);

				//Genero el nombre del archivo del mapa
				map_ext[0] = num_mapas + '0';

				strcat(map_access, map_ext);

				//Creo el archivo
				if ((mapa = fopen(map_access, "w+b")) == NULL)
				{
					printf("No se pudo crear mapa\n");
					getch();
					exit(1);
				}

				//Guardo el mapa con su nombre
				destino = save_header(maze, name, start, end);	//Guardo la cabecera
				source = save_source(maze);						//Guardo la fuente
				fwrite(&destino, sizeof(header), 1, mapa);		//Escribo la cabecera
				fseek(mapa, TAM_CABECERA, SEEK_SET);			//Salto la cabecera
				fputs(source, mapa);							//Escribo la fuente
				sprintf(score_string, "%4d", 9999);				//Escribo el valor default de puntaje (9999) a un string auxiliar
				fputs(score_string, mapa);						//Escribo el string auxiliar con el puntaje default al archivo
				fclose(mapa);//Cierro el mapa
				printf("Guardado con exito\nPresione cualquier tecla para salir");
				getch();
				printf("\n");
			}else{
				printf("No guardado\n");
			}
			printf("Volver al menu? (s/n)\n");
			sigue = getch() == 's';
		}else{
			if (x == 2)
			{
				do
				{
					clrscr();
					printf("				Instrucciones:\n\n");
					printf("Al empezar necesitara ponerle nombre al mapa\nEl nombre no puede tener mas de 20 caracteres.\n");
					printf("Luego le pedira la cantidad de columnas y filas.\nEs recomendable no hacerlo mas grande que 80 x 25, para evitar problemas con el sistema\n");
					printf("Luego le pedira elegir entre generacion aleatoria y dibujar el mapa manualmente.\n");
					printf("Al final de todo le mostrara como resulta con los caracteres de principio \"");
					textcolor(RED);
					cprintf("%c", CAR_PUERTA);
					printf("\" y el de final \"");
					textcolor(LIGHTGREEN);
					cprintf("%c", CAR_PUERTA);
					printf("\"\n\n");
					printf("				Generacion aleatoria:\n\n");
					printf("El programa le pedira que coloque una semilla, esta sera el origen\ndel generador de numeros aleatorios, si desea puede colocar -1 para obtener una semilla aleatoria\n\n\n");
					printf("				Dibujo:\n\n");
					printf("El programa le dibujara un mapa completo de \"%c\" que representan la pared.\nEn el centro del mapa, aparecera el caracter \"%c\" que representa el pincel.\nPuede mover el pincel con las flechas, cuando lo mueva el pincel dejara \"%c\"\nque representa el espacio vacio.\nPuede usar las teclas W A S D para colocar \"", CAR_PARED, CAR_JUG_CENTRO, CAR_VACIO);
					textcolor(YELLOW);
					cprintf("%c", CAR_PREMIO);
					printf("\", que representa el premio\nque en el juego ayuda a mejorar el puntaje.\nSi presiona la barra espaciadora, las teclas W A S D colocaran paredes en lugar de premios.\n");
					printf("Una vez que termine de pintar paredes, premios y espacios podra mover el pincel hacia el lugar donde sera el principio del mapa.\nLuego tendra que hacer lo mismo con el final.\n");

					printf("\n\n\nPresione la tecla Enter para continuar");
				} while (getch() != ENTER);
			}else{
				exit(1);
			}
		}
	} while (sigue);
}