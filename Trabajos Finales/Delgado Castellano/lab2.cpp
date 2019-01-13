#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream.h>
#include <windows.h>
#include <conio.h>
#include <stack>
#include <string.h>


#define TAM 25





struct elemento
{
	bool visitado;
	bool arriba;
	bool abajo;
	bool izquierda;
	bool derecha;
	int mostrar;
};



struct header
{
	char nombre[20];
	int posx;
	int posy;
	int endx;
	int endy;
	int tamanio;

	
};




void Inicializar(elemento lab[TAM][TAM]);
void dibujar(elemento lab[TAM][TAM]);
//void ClearScreen();
getch();
void caminos(elemento lab[TAM][TAM], int finX, int finY);
void guardar(elemento lab[TAM][TAM], header cabecera);




int main() {


char Cant='m';

while ( Cant>'b')
	printf(“%2c”, --Cant);




return 0;


}



void Inicializar(elemento lab[TAM][TAM]){

	for (int i = 0; i < TAM; i++)
	{
		for (int j = 0; j < TAM; j++)
		{ 
			lab[i][j].mostrar = 0;
			lab[i][j].arriba = true;
			lab[i][j].abajo = true;
			lab[i][j].izquierda = true;
			lab[i][j].derecha = true;
			lab[i][j].visitado = false;
			/*lab[0][j].visitado = true;
			lab[TAM-1][j].visitado = true;
			lab[i][0].visitado = true;
			lab[i][TAM-1].visitado = true;*/

		}
	}

	for(int i=1; i<TAM-1; i++) {
		for(int j=1; j<TAM-1; j++) {
			lab[1][j].arriba = false;
			lab[1][j].abajo = false;
			
			lab[TAM-2][j].abajo = false;
			lab[i][1].izquierda = false;
			lab[i][TAM-2].derecha = false;
		}
	}





}

void ClearScreen()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void dibujar(elemento lab[TAM][TAM]) {
	for(int i=0; i<TAM; i++) {
		printf("\n");

		for(int j=0; j< TAM; j++)
			if (lab[i][j].mostrar==0) printf("%c", 219);
			else
				if (lab[i][j].mostrar==1) printf(" ");
				else printf("%d", lab[i][j].mostrar);
	}

	

}


void caminos(elemento lab[TAM][TAM],int finX, int finY){

	srand(time(NULL));		        		
	int posicion;
	int posicionX;
	int posicionY;
	int tama = TAM/2;

	if (tama%2 == 0)
	{
		 posicionX= 1;
		 posicionY= TAM-2;
	}
	else{
		 posicionX= (TAM/2);						// posicion de salida en X
		 posicionY= (TAM/2);							// posicion de salida en Y
	}

	int elementosvisitados = 1;
	int totalelemnentos = ((TAM-1)/2)*((TAM-1)/2);
	stack<int> caminoX, caminoY; 						
	lab[posicionY][posicionX].mostrar = 2;						
	lab[posicionY][posicionX].visitado = true;						

	while(elementosvisitados < totalelemnentos)
	{
		if(((lab[posicionY-2][posicionX].visitado == false) && (lab[posicionY][posicionX].arriba == true && lab[posicionY-2][posicionX].abajo == true)) ||
		   ((lab[posicionY+2][posicionX].visitado == false) && (lab[posicionY][posicionX].abajo == true && lab[posicionY+2][posicionX].arriba == true)) ||
		   ((lab[posicionY][posicionX-2].visitado == false) && (lab[posicionY][posicionX].izquierda == true && lab[posicionY][posicionX-2].derecha == true)) ||
		   ((lab[posicionY][posicionX+2].visitado == false) && (lab[posicionY][posicionX].derecha == true && lab[posicionY][posicionX+2].izquierda == true)))
		{
			int random = (rand() % 4) + 1;		

			 // arriba
			if((random == 1) && (posicionY > 1)) {
				if(lab[posicionY-2][posicionX].visitado == false) {	
					
					lab[posicionY-1][posicionX].mostrar = 1;	
					lab[posicionY-1][posicionX].visitado = true;	
					lab[posicionY][posicionX].arriba = false;

					caminoX.push(posicionX); 			
					caminoY.push(posicionY);			

					posicionY -= 2;	
					lab[posicionY][posicionX].visitado = true;		
					lab[posicionY][posicionX].mostrar = 1;	
					lab[posicionY][posicionX].abajo = false;	
					elementosvisitados++;					
				}
				else
					continue;
			}

			// abajo
			else if((random == 2) && (posicionY < TAM-2)) {
				if(lab[posicionY+2][posicionX].visitado == false) {	
					lab[posicionY+1][posicionX].mostrar = 1;	
					lab[posicionY+1][posicionX].visitado = true;	
					lab[posicionY][posicionX].abajo = false;	

					caminoX.push(posicionX); 			
					caminoY.push(posicionY);			

					posicionY += 2;					
					lab[posicionY][posicionX].visitado = true;		
					lab[posicionY][posicionX].mostrar = 1;		
					lab[posicionY][posicionX].arriba = false;	
					elementosvisitados++;					
				}
				else
					continue;
			}

			// izquierda
			else if((random == 3) && (posicionX > 1)) {
				if(lab[posicionY][posicionX-2].visitado == false) {
					lab[posicionY][posicionX-1].mostrar = 1;	
					lab[posicionY][posicionX-1].visitado = true;	
					lab[posicionY][posicionX].izquierda = false;	

					caminoX.push(posicionX); 		
					caminoY.push(posicionY);			

					posicionX -= 2;					
					lab[posicionY][posicionX].visitado = true;		
					lab[posicionY][posicionX].mostrar = 1;		
					lab[posicionY][posicionX].derecha = false;	
					elementosvisitados++;					
				}
				else
					continue;
			}

			// derecha
			else if((random == 4) && (posicionX < TAM-2)) {
				if(lab[posicionY][posicionX+2].visitado == false) {	
					lab[posicionY][posicionX+1].mostrar = 1;	
					lab[posicionY][posicionX+1].visitado = true;	
					lab[posicionY][posicionX].derecha = false;	

					caminoX.push(posicionX); 			
					caminoY.push(posicionY);			

					posicionX += 2;					
					lab[posicionY][posicionX].visitado = true;		
					lab[posicionY][posicionX].mostrar = 1;		
					lab[posicionY][posicionX].izquierda = false;	
					elementosvisitados++;					
				}
				else
					continue;
			}

		
		}
		else {
			posicionX = caminoX.top();
			caminoX.pop();

			posicionY = caminoY.top();
			caminoY.pop();
		}
		
		ClearScreen();
		
 		//clrscr();
		dibujar(lab);
		
	}


	do{

	finX = TAM-1;
	finY = rand()%TAM-2;
	lab[finY][finX].mostrar = 3;
	//lab[1 + rand()%(TAM-2)][0].mostrar = ' ';
	 //clrscr();
	ClearScreen();
	dibujar(lab);
	}while(lab[finY][finX-1].mostrar == 0);



	do{

	finX = 0;
	finY = rand()%TAM-2;
	lab[finY][finX].mostrar = 4;
	//lab[1 + rand()%(TAM-2)][0].mostrar = ' ';
	 //clrscr();
	ClearScreen();
	dibujar(lab);
	}while(lab[finY][finX+1].mostrar == 0);

	/*printf("%c", lab[finY][finX-1].mostrar);
	printf("%d",finX);
	printf("%d",finY);*/
	

} 

void guardar(elemento lab[TAM][TAM], header cabecera){

char c;
char n[20];

printf("\n \n Guardar el laberinto y jugar? S/N:");
scanf("%c",&c);

printf("\n \n");




if (c == 's' || c == 'S')
{	
       //char tipo[] = ".dat";
	   char n[20];
	   char archivo[]="archivo.dat";

	   for (int i = 0; i < TAM; i++)
			{
				for (int j = 0; j < TAM; j++)
				{

					if(lab[i][j].mostrar == 4)
					{
						cabecera.posx = j;
						cabecera.posy = i;				
					}
					if(lab[i][j].mostrar == 3)
					{
						cabecera.endx = j;
						cabecera.endy = i;				
					}
				}
			}


	   printf("\n Ingrese el nombre del Laberinto: " );
	   scanf("%s", n);

	   //strcpy(archivo,n);
	   //strcat(archivo,tipo);


	   FILE *ABin = fopen(archivo,"wb+");

	   fwrite(&cabecera,sizeof(header),1, ABin);
	  
	   clrscr();



		printf("\n");
		for (int i = 0; i < TAM; i++)
			{
				for (int j = 0; j < TAM; j++)
				{

					fwrite(&lab[i][j].mostrar,sizeof(int),1, ABin);
				}
			}

			fclose(ABin);
			printf("ARCHIVO GUARDADO!");

}
		

if (c == 'n' || c == 'N')
{
	clrscr();
	printf("\n Chau");
}

}

