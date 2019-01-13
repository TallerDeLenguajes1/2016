#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream.h>
#include <windows.h>
#include <conio.h>


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



void abrir(header cabecera);
void gotoxy(int x,int y);
void jugar(int x,int y,elemento lab[TAM][TAM],int t,int z);

int main() {


FILE *ABin;


elemento lab[TAM][TAM];
header cabecera;
abrir(cabecera);


}



void abrir(header cabecera){

	    FILE *ABin;
	    elemento lab[TAM][TAM];

		ABin = fopen("archivo.dat","rb+");
		fread(&cabecera,sizeof(header),1, ABin);
		for (int i = 0; i < TAM; i++)
			{
				for (int j = 0; j < TAM; j++)
				{

					fread(&lab[i][j].mostrar,sizeof(int),1, ABin);
					

					if (lab[i][j].mostrar == 0)
					{
						printf("%c",lab[i][j].mostrar = 177);
					}

					if (lab[i][j].mostrar == 1)
					{
						printf("%c",lab[i][j].mostrar = ' ');
					}

					if (lab[i][j].mostrar == 2)
					{
						printf("%c",lab[i][j].mostrar = ' ');
					}

					if (lab[i][j].mostrar == 3)
					{
						printf("%c",lab[i][j].mostrar = 175);
					}

					if (lab[i][j].mostrar == 4)
					{
						printf("%c",lab[i][j].mostrar = ' ');
					}
					

				}
					
					printf("\n");	
			}
			

			gotoxy(cabecera.posx, cabecera.posy);
			printf("*");  
     		jugar(cabecera.posx,cabecera.posy,lab,cabecera.endx, cabecera.endy); 		

      

			fclose(ABin);
}
void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }

 void jugar(int x,int y, elemento lab[TAM][TAM],int t, int z){

 	bool fin=false;
      while(!fin){
      		

      		if(kbhit()){
      			char tecla = getch();
      			gotoxy(x,y);
      			printf(" ");
      			if(tecla == 'K' && lab[y][x-1].mostrar == ' '){			//doble igual porque es una condicion logica//
      					x--;
      				}
      			if(tecla == 'M' && lab[y][x+1].mostrar == ' ' || tecla == 'M' && lab[y][x+1].mostrar == 175 ){			//doble igual porque es una condicion logica//
      					x++;
      				}
      			if(tecla == 'H' && lab[y-1][x].mostrar == ' '){			//doble igual porque es una condicion logica//
      					y--;
      				}
      			if(tecla == 'P' && lab[y+1][x].mostrar == ' '){			//doble igual porque es una condicion logica//
      					y++;
      				}


      			if(x<0){
					x=0;
					
      			      				
      			}

      			if(y<0){
                              y=0;
                              
                                                      
                        }

                        gotoxy(x,y);
                        printf("*");
      			
      			
      		}
      		if(x==t && y==z )
      		{
      			fin = true;
      		}
      		
 }
 clrscr();
 printf("Felicitaciones!!!! Ud. Gano");

}