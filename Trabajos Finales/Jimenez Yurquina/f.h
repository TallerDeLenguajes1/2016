const DIM1=30; const DIM2=90; const IZQ=75; const DER=77; const ABJ=80; const ARR=72; const ESC=27; const R=82; const r=114;
const S=83;    const s=115;   const M=77;   const m=109;  const E=69;   const e=101;  const ti=105; const tI=73; const b=98; 
const B=66;    const Ent=13;  const g=103;  const G=71;   const f=102;  const F=70;   const SI=1;   const NO=-1;

void gotoxy(int x,int y){
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon, dwPos);
}

bool contorno(int m, int n, int i, int j){

	if( i==0 && j==0 || i==0 && j==m-1 || j==0 && i==n-1 || j==m && i==n-1 )         //Todo esto es para
		return false;																   //que no se pueda poner
	else if(i==0 || i==n-1)															   //el inicio ni el final
		return true;																   //en cualquier
	else if(j==0 || j==m-1)														 	   //parte. Sólo en el contorno
		return true;																   //(quitando las esquinas)
	else
		return false;
}

int mover(int m, int n, int *i, int *j, int contorno){
	int x, y;
		x=getch();
		if(x==0){
			y=getch();
			
			if(y==IZQ){
				gotoxy(*i, *j); //si escribo antes (*i)--; no me toma bien la restricción del contorno
				(*i)--;
			}else if(y==DER){
				gotoxy(*i, *j);
				(*i)++;
			}else if(y==ABJ){
				gotoxy(*i, *j);
				(*j)++;
			}else if(y==ARR){
				gotoxy(*i, *j);
				(*j)--;
			}
		}

		if(contorno==0){
			if (*i < 1)     (*i)++;    //		Todos estos casos
			if (*j < 1)     (*j)++;    //		son para cuando
			if (*i >= n-1)  (*i)--;    //		el cursor llega 
			if (*j >= m-1)  (*j)--;    //		a los límites de la pantalla
		}
		else{
			if (*i < 0)  (*i)++;       //		Todos estos casos
			if (*j < 0)  (*j)++;       //		son para cuando
			if (*i >= n) (*i)--;       //		el cursor llega 
			if (*j >= m) (*j)--;       //		a los límites de la pantalla
		}

	gotoxy(*i, *j);
	return x;
}

int senderos(int m, int n, int *i, int *j, int **Mat){
	int x;
	do{
		gotoxy(0, m+3);
		textcolor(LIGHTGREEN);
		cprintf("                                                                                                \n");
		cprintf("\r Usted esta dibujando senderos                                                                  ");
		gotoxy(*i, *j);
		x=mover(m, n, i, j, 0);
		Mat[*j][*i] = 0; // Guarda en la matriz donde hay camino.
		cprintf(" "); // Va dibujando los senderos
 	}while(x!=R && x!=r && x!=ESC && x!= e && x!=E && x!=b && x!=B && x!=ti && x!=tI && x!=f && x!=F && x!=g && x!=G ); // Si se presiona alguna de las teclas indicadas (ya sea con Bloq. Mayús. o sin él) se termina el bucle
 	return x;
}

int noEscribir(int m, int n, int *i, int *j){
	int x;
	do{
		gotoxy(0, m+3);
		textcolor(LIGHTGREEN);
		cprintf("                                                                                                \n");//para que borre el texto largo anterior
		cprintf("\r Usted esta moviendo el cursor                                                                  ");
		gotoxy(*i, *j);
		x=mover(m, n, i, j, 0);		
 	}while(x!=S && x!=s && x!=ESC && x!= r && x!=R && x!=b && x!=B && x!=ti && x!=tI && x!=f && x!=F && x!=g && x!=G ); // Si se presiona alguna de las teclas indicadas (ya sea con Bloq. Mayús. o sin él) se termina el bucle
 	return x;
}

int reescribir(int m, int n, int *i, int *j, int **Mat){
	int x;
	do{
		gotoxy(0, m+3);
		textcolor(LIGHTGREEN);
		cprintf("                                                                                                \n");
		cprintf("\r Usted esta reescribiendo                                                                       ");
		gotoxy(*i, *j);
		x=mover(m, n, i, j, 0);
		Mat[*j][*i] = 1; // Guarda en la matriz donde hay camino.
		cprintf("%c", 1); //Va reescribiendo con el caracter indicado
 	}while(x!=S && x!=s && x!=ESC && x!= e && x!=E && x!=b && x!=B  && x!=ti && x!=tI && x!=f && x!=F && x!=g && x!=G ); // Si se presiona alguna de las teclas indicadas (ya sea con Bloq. Mayús. o sin él) se termina el bucle
 	return x;
}

void *ReservarMemoria(int TotBytes){
void *pAux;
  
  if((pAux=malloc(TotBytes))==NULL) {
    cprintf(" No pudo reservar memoria dinámica");
    getch( ); exit(1);
  }
  return(pAux);
}

bool obtenerInicio(int **Mat, int m, int n, int *x_p, int *y_p){
	for (int i = 0; i<m; i++){
		for (int j = 0; j<n; j++){
			if(Mat[i][j]==35){
				*x_p=i;
				*y_p=j;
				return true;
			}
		}
	}
	return false;
}

int **asignar_matriz(int m, int n){
	 clrscr();
	 gotoxy(0, 0);
     int i, j;
     int **Mat;
     Mat=(int **)ReservarMemoria(m*sizeof(int *)); // se reserva memoria  para la matriz de m filas 
     for (i=0; i<m; i++)
        Mat[i]=(int *)ReservarMemoria(n*sizeof(int)); // se reserva memoria para las n columnas
	return Mat; // retorno de un puntero doble
}

char **asignarChar(int m){
     int i;
     char **Mat;
     Mat=(char **)ReservarMemoria(m*sizeof(char *)); // se reserva memoria  para la matriz de m filas 
     for (i=0; i<m; i++)
        Mat[i]=(char *)ReservarMemoria(17*sizeof(char)); // se reserva memoria para las n columnas	
	return Mat; // retorno de un puntero doble
}

void genMat(int **Mat, int m, int n){
	int i, j;
	gotoxy(0, 0);
	textcolor(LIGHTRED);
     for (i=0; i<m; i++)
	     for ( i = 0; i < m; i++){
     		for (j = 0; j < n; j++){
     			Mat[i][j]=1;// Sirve para despues guardar la matriz (El laberinto) en un archivo y poder abrirla.
     	}
     	printf("\n");
     }
}

void mostrarMatriz(int **Mat, int m, int n, bool jugando){
	int i,j;
	gotoxy(0, 0);
    for(i=0; i<m; i++){
        for (j=0; j<n; j++){
        	if(jugando==true){
        		textcolor(GREEN);

        		switch(Mat[i][j]){
        			case 0: cprintf("%c", 32); break;
        			case 1: 
		        			if(i==0 || j==0 || i==m-1 || j==n-1){//si es contorno pinta de rojo, sino pinta verde
		        				textcolor(LIGHTRED);
        						cprintf("%c", 177);
        					}else{
        						cprintf("%c", 1);
        					}
        					break;
        			case 35: textcolor(GREEN);cprintf("%c", tI); textcolor(LIGHTRED);break; 
        			case 64: textcolor(GREEN);cprintf("%c", F); textcolor(LIGHTRED);break;
        			default: cprintf("%c", 1); break;
        		}
        	}
      		else{
      				cprintf("%c", Mat[i][j]);
			}
        }
    	printf("\n");
    }
}

int moverMenu(int *i, int *j, int lim_sup, int lim_inf, bool uno ){
	int x, y;

	do{
		x=getch();
		if(x==0){
			y=getch();
			if(y==ABJ){
				gotoxy(*i, *j);
				if(uno==true)
					(*j)++;
				else
					*j=*j+2;
			}else if(y==ARR){
				gotoxy(*i, *j);
				if(uno==true)
					(*j)--;
				else
					*j=*j-2;
			}
		}

		if (uno==true){
			if(*j>lim_sup)	(*j)--;
			if(*j<lim_inf)	(*j)++;
		}else{
			if(*j>lim_sup)	*j=*j-2;
			if(*j<lim_inf)	*j=*j+2;
		}
			printf(" ");
			gotoxy(*i, *j);
			printf("*");
	}while(x!=Ent);
		
	return *j;
}

void jugar(int m, int n, int x_p, int y_p, int **Mat, bool *win, bool jugar, int *pasos){
  int x, y;
  	clrscr();
  	mostrarMatriz(Mat, m, n, true);
  	gotoxy(0, m+1);
		textcolor(LIGHTGREEN);

	if(jugar==false){
		cprintf(" Vista previa del laberinto creado");
		cprintf("\r\n Presione [ESC] para seguir editando o llegue al Final del laberinto para Guardarlo");
	}

  gotoxy(y_p, x_p);
  do{
		x=getch();
	    if(x!=0){
	      y=0;
	    }else{
	      y=getch();
	    }

   		if(y==IZQ){
   			if(y_p>0){
	   			if(Mat[x_p][y_p-1]==0){
	   				gotoxy(y_p, x_p);
	   				printf(" ");
	    			y_p--;
	    			if (jugar==true)
	    				(*pasos)++;
	   			}else if(Mat[x_p][y_p-1]==64){
	   				clrscr();
	   				*win = true;
	   			}
   			}
		}else if(y==DER){
			if(y_p<n-1){
				if(Mat[x_p][y_p+1]==0){
					gotoxy(y_p, x_p);
	   				printf(" ");
					y_p++;
					if (jugar==true)
						(*pasos)++;
				}else if(Mat[x_p][y_p+1]==64){
					clrscr();
	   				*win = true;
				}
			}
		}else if(y==ABJ){
			if(x_p<m-1){
				if(Mat[x_p+1][y_p]==0){
					gotoxy(y_p, x_p);
	   				printf(" ");
					x_p++;
					if (jugar==true)
						(*pasos)++;
				}else if(Mat[x_p+1][y_p]==64){
					clrscr();
	   				*win = true;
				}
			}
		}else if(y==ARR){
			if(x_p>0){
				if(Mat[x_p-1][y_p]==0){
					gotoxy(y_p, x_p);
	   				printf(" ");
					x_p--;
					if (jugar==true)
						(*pasos)++;
				}else if(Mat[x_p-1][y_p]==64){
					clrscr();
	   				*win = true;
				}
				
			}
			
		}
	gotoxy(y_p, x_p);
    printf("%c", 1);

    if(jugar==true){
		gotoxy(0, m + 2);
		cprintf(" Presione [ESC] para volver al menu de Laberintos.");
		cprintf("\n\r Pasos: %d", *pasos);
	}

  }while(x!=ESC && *win == false);
  if(*win==false){
  	gotoxy(y_p, x_p); //cuando se cancela "Guardar" borra el personaje de la última posición
  	printf(" ");
  }

  if(jugar==true)
  	(*pasos)++;

}

/**********************************ARCHIVOS BINARIOS Y DE TEXTO**********************************************************/
void nombreLaberinto(int n, char name[]){//GENERA LOS NOMBRES DE LOS LABERINTOS con el parámetro entero que se desee (LaberintoXXX)
	char c[4]="0000";
	int i=2;
	while(n>0){
		c[i]='0'+n%10;
		n=n/10;
		i--;
	}
	c[3]='\0';
	strcat(name, c);
	strcat(name, ".dat");
}

int cantidadListas(){
	FILE *archivo;
	char name[17]="Laberinto";
	int m=1;
	nombreLaberinto(m, name);//EMPIEZA A BUSCAR DESDE "Laberinto001.dat"
	while((archivo=fopen(name,"rb"))!=NULL){
		fclose(archivo);
		m++;
		strcpy(name, "Laberinto");
		nombreLaberinto(m, name);
	}
	return m;
}

char **obtenerLista(int m){//DEVUELVE EL NOMBRE DE LAS LISTAS QUE EXISTAN (TIENEN QUE SER DE NOMBRES CONSECUTIVOS "LaberintoNNN.dat")
	FILE *archivo;
	char name[17]="Laberinto", **Lista;
	int i;

	Lista=asignarChar(m);

	for (i = 0; i < m; i++){
			nombreLaberinto(i+1, name);
			strcpy(Lista[i], name);
			strcpy(name, "Laberinto");
	}
	return Lista;
}

void guardarMatriz(int **Mat, int m, int n, int x_p, int y_p){
	FILE *archivo;
	int i, j, N;
	char name[17]="Laberinto";
	clrscr();
	N=cantidadListas();//OBTIENE LA CANTIDAD DE LABERINTOS CREADOS + 1 
	strcpy(name, "Laberinto");//VUELVE A ASIGNAR EL MISMO NOMBRE PORQUE ES MODIFICADO EN LA LLAMADA ANTERIOR
	nombreLaberinto(N, name);

	if((archivo=fopen(name,"wb+"))==NULL){
	    cprintf("No se pudo escribir el archivo");
	    getch(); return;
	}

	for(i=0; i < m; i++)
		for (j = 0; j < n; j++)
			putw(Mat[i][j], archivo);

	fwrite(name,sizeof(char)*17,1,archivo); /* Inicio Cabecera */
	putw(m,archivo);
	putw(n,archivo);
	putw(x_p,archivo);
	putw(y_p,archivo); /* Fin Cabecera */

	fclose(archivo);
	gotoxy(0, 3);
	printf("\n %s se creo correctamente, presione una tecla para continuar...", name);
	getch();
}

void LeerDeCabecera(int * m, int * n, int * x_p, int * y_p, char name[], char Lista[]){
	FILE * archivo;
	int leidos;

	if ((archivo = fopen(Lista,"rb"))==NULL){
		cprintf("No se pudo leer el archivo");
	}

	fseek(archivo, -(sizeof(char)*17 + sizeof(int)*4),SEEK_END);
	leidos = fread(name,sizeof(char)*17,1,archivo);
	leidos = fread(m,sizeof(int),1,archivo);
	leidos = fread(n,sizeof(int),1,archivo);
	leidos = fread(x_p,sizeof(int),1,archivo);
	leidos = fread(y_p,sizeof(int),1,archivo);

	fclose(archivo);
}

void leerMatriz(int **Mat, int m, int n, char name[]){
	FILE *archivo;
	int i, j;

	if((archivo=fopen(name,"rb"))==NULL) {
	    cprintf("\n\n\n No se pudo encontrar el archivo");
	    getch( ); return;
	 }
	 while(!feof(archivo) ){
	 	for (i = 0; i < m; i++){
	 		for (j = 0; j < n; j++){
	 	 		Mat[i][j]= getw(archivo);
	 	 	}
	 	}
	 	break;
	 }
	 fclose(archivo);
}

void guardarTopTen(char Mat[10][11], int pasos[], int nuevo, char player[10]){
	FILE *archivo;
	int i, j, aux;
	char nameaux[10];

	if((archivo=fopen("Top10.dat","wb"))==NULL){
	    cprintf("No se pudo escribir el archivo");
	    getch(); return;
	}

	for (i = 0; i < 10; i++){
		if (nuevo < pasos[i]){ // Pregunta si es menor que el puntaje pasos[i]
			j = i; // Si es menor, guarda la posicion donde debe ubicarse el nuevo
			i = 9; // Y le asigna 9 a la i, para que no entre mas al bucle.
		}
	}

	for (j; j < 10; j++){ // Desde el valor que quedo la j, hasta el final, cambia lo valores.
		aux = pasos[j];
		pasos[j] = nuevo;
		nuevo = aux;
		strcpy(nameaux, Mat[j]);
		strcpy(Mat[j], player);
		strcpy(player, nameaux); // En el ultimo ciclo, el que era el peor puntaje no se guarda en nigun lado.
	}

	for (i = 0; i < 10; i++){ // Una vez rearmado el vector de pasos y de nombres reescribe el archivo.
		fwrite(Mat[i], 1, 10, archivo);
		putw(pasos[i], archivo);
	}

	fclose(archivo);
}

void ordenarPasos(int vPasos[], char Mat[10][11]){ // Ordena atraves del Metodo de Inserción.
	int i, j, prox;
	char aux[11];

	for (i = 1; i < 10; i++)
	{
		prox = vPasos[i];
		strcpy(aux, Mat[i]);
		j = i;
		while(j > 0 && prox < vPasos[j - 1]){
			vPasos[j] = vPasos[j - 1];
			strcpy(Mat[j], Mat[j - 1]);
			j--;
		}
		vPasos[j] = prox;
		strcpy(Mat[j], aux);
	}
}

void leerTopTen(char Mat[10][11], int pasos[]){
	FILE *archivo;
	int i = 0, Leidos;
	char Leer[11];

	if((archivo=fopen("Top10.dat","ab+"))==NULL){ // Abre el archivo para lectura, si no existe lo crea
	    cprintf("No se pudo leer el archivo");
	    getch(); return;
	}
	rewind(archivo);
	while((Leidos = fread(Mat[i],sizeof(char)*10, 1, archivo)) > 0){ // Lee y guarda mientras haya nombres
		Mat[i][10] = '\0';
		pasos[i] = getw(archivo); // Guarda en el vector de Pasos, los pasos del nombre leido.
		i++;
	} 
    for (i; i < 10; i++){ // Completa el TopTen con valores predeterminados.
    	strcpy(Mat[i], "NO NAME---");
    	pasos[i] = 999;
    }

    ordenarPasos(pasos, Mat); // Ordena el vector de Pasos de menor a mayor
    fclose(archivo);
}


