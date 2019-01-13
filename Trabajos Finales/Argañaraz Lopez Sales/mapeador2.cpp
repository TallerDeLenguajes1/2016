#include <iostream>
#include <conio2.h>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "cabecera.h"

using namespace std;

#define ANCHO 80
#define ALTO 25


void imprdib(char map[][ANCHO],int alto,int ancho);
void imprayuda(void);

int main() {
	
	char map[ALTO][ANCHO]; //mapa del grafico
	textcolor(WHITE);
	header cabecera;
	
	char t; //para leer el teclado
	
	char nombre[30]; //nombre de archivo
	char cad[ANCHO+3]; //cadena auxiliar para ayudar a guardar o leer de los archivos
	
	bool salir=true; //salir=false para salir
	
	int px,py; //coordenadas del pincel
	
	int alto=ALTO; //alto del mapa gr?fico
	int ancho=ANCHO; //ancho del mapa gr?fico
	
	int m,n,s=0; //auxiliares para for
	
	//iniciamos el mapa del grafico con espacios
	for(n=0;n<ALTO;++n)
		for(int m=0;m<ANCHO;++m) map[n][m]='0';
	
	px=py=0; // coordenadas del pincel para dibujar
	imprdib(map,alto,ancho); //imprimimos la zona de dibujo
	
	imprayuda();
	
	gotoxy(py+2,px+2); //fijamos el cursor en su lugar
	
	while(salir)
	{
		if(kbhit())
		{
			t=getch();
			if(t==27) //tecla Esc salimos del programa
			{
				exit(0);
			}
			if(t==75) //nos movemos a la izquierda
			{
				if(py>0) --py;
				gotoxy(51,29);
				cout << "X: " << px << " " << "Y: " << py;
			}
			if(t==77) //nos movemos a la derecha
			{
				if(py<ancho-1) ++py;
				gotoxy(51,29);
				cout << "X: " << px << " " << "Y: " << py;
			}
			
			if(t==72) //nos movemos hacia arriba
			{
				if(px>0) --px;
				gotoxy(51,29);
				cout << "X: " << px << " " << "Y: " << py;
			}
			if(t==80) //nos movemos hacia abajo
			{
				if(px<alto-1) ++px;
				gotoxy(51,29);
				cout << "X: " << px << " " << "Y: " << py;
			}
			
			if(t=='2') //pintamos bloque
			{
				s++;
				if((s>3))s=1;
				
				if (map[px][py]!='0'){
					switch (s){
						case 1:
							if (map[px][py]=='1') map[px][py]='2';
							else map[px][py]='2';
							putchar(map[px][py]);
							break;
							
						case 2:
							if (map[px][py]=='1') map[px][py]='3';
							else map[px][py]='3';
							putchar(map[px][py]);
							break;						
							break;
						
						case 3: 	
							if (map[px][py]=='1') map[px][py]='4';
							else map[px][py]='4';
							putchar(map[px][py]);
							break;						
							break;
							
						default:
						s=0;
							
					}
					
				}
			}
			
			if ((t=='3'))
			{
			
				cabecera.inX = px;
				cabecera.inY = py;
				gotoxy(1,30);
				//cout<<"    ";
				cout << "Coordenadas de ENTRADA   X: " << cabecera.inX << " " << "Y: " << cabecera.inY << "\b";
				
					
			}
			
			if ((t=='4'))
			{
			
				cabecera.outX = px;
				cabecera.outY = py;
				gotoxy(1,30);
				//cout<<"    ";
				cout << "Coordenadas de SALIDA    X: " << cabecera.outX << " " << "Y: " << cabecera.outY << "\b";
					
			}
			
						
			if(t==61)//F2 para guardar
			{

				ofstream sal; //manejador de archivo de salida
				gotoxy(1,29); //espacio para el pedido de nombre
				
				gotoxy(1,29);
				cout<<"Introduce el nombre del archivo a guardar:";
				cin.getline(nombre,30);
				strcpy(cabecera.nombre,nombre); //Copio el nombre a mi struct
				cabecera.record = 0; //Record es igual a 0.
				sal.open(nombre); //abrimos el archivo "nombre" para escritura 
				
				sal.seekp(0); //Puntero PUT en 0
				
		
				sal.write((char *)&cabecera, sizeof(header)); //Escribo mi struct en el archivo
			
				sal.seekp(1024); //Puntero PUT en 1024
				
				for(int n=0;n<alto;++n) //leemos linea por linea el archivo
				{
					cad[0]='\"';
					strncpy(cad+1,map[n],ancho); //copiamos la linea a una cadena
					cad[ancho+1]='\"';
					cad[ancho+2]=0; //por un bug en el compilador hay que agregar '\0'
					sal<<cad<<endl; //enviamos la linea al archivo con un enter al final
				}
				
				sal.close(); //cerramos el archivo y se puede reutilizar sal la proxima vez
				gotoxy(1,24); //borramos el pedido de nombre
				imprayuda();
			}
		
			
			
			if(t==63)//F5 para cargar
			{
				gotoxy(1,29); //espacio para el pedido de nombre
				gotoxy(1,29);
				cout<<"Introduce el nombre del archivo a cargar:";
				cin.getline(nombre,30);
				
				ifstream ent(nombre); //creamos el objeto para manejar entrada
				
					if (ent.fail())
					{
						cout<<"Error de Archivo";
						continue;
					}
				
				ent.seekg(0); //Puntero GET en 0
				
				ent.read((char *)&cabecera, sizeof(header));
				
				ent.seekg(1024); //Puntero GET en 0

					m=0;                                                //para contar la cantidad de lineas
					do{
						ent.getline(cad,ANCHO+3);                       //leemos una linea del archivo ent y la colocamos en cad
						ancho=strlen(cad)-2;                            //obtenemos longitud de cad con strlen (devuelve tamaño)
						memcpy(map[m],cad+1,ancho);                     //copiamos ancho caracteres (memcpy es parecida a strncpy solo que no coloca el '\0' )
						++m;
						if(m>ALTO-1) break;                             //si superamos la cantidad de lineas que podemos almacenar terminamos la carga
					}while(!ent.eof());                                 //leemos hasta que el achivo se acabe
					alto=m;
					if(alto<1) alto=1;                                  //si el archivo tiene lineas vacias acomodamos
					if(ancho<1) ancho=1;                                //alto y ancho
					px=py=0;                                            //el cursor va a arriba a la izquierda
					ent.close();
					
				
					clrscr();                                               //borramos la pantalla e imprimimos todo de nuevo
					imprdib(map,alto,ancho);                                //imprimimos la zona de dibujo
				//imprayuda();                                            //imprimimos las ayudas
				
				gotoxy(1,28);
			 	cout << "Nombre mapa: " << cabecera.nombre << endl;
			 	cout << "Se inicia   en X: " << cabecera.inX << "  Y: " << cabecera.inY <<endl;
				cout << "Se finaliza en X: " << cabecera.outX << "  Y: " << cabecera.outY << endl;
				}   
				
				

				
			
			gotoxy(py+2,px+2); //fijamos el cursor en su lugar
		}
		
	}
	
	return 0;
}


void imprdib(char map[][ANCHO],int alto,int ancho)
{
	int m,n;
	
	//dibujamos el area de dibujo
	
	gotoxy(1,1);
	cout<<(char)201;
	for(n=0;n<ancho;++n) cout<<(char)205;
	cout<<(char)187<<" ";
	for(m=0;m<alto;++m)
	{
		gotoxy(1,m+2);
		cout<<(char)186;
		for(int n=0;n<ancho;++n) {
			
			
			if(map[m][n]=='0'){
				cout <<(char)178 ;
			}else if (map[m][n]=='1') {
				cout << ' ' ;
			}else{
				cout<< map[m][n]  ;
			}
				
			
			 ;
		}
		cout<<(char)186<<" ";
	}
	gotoxy(1,m+2);
	cout<<(char)200;
	for(n=0;n<ancho;++n) cout<<(char)205;
	cout<<(char)188<<" ";
	gotoxy(1,m+3);
	cout<<"                                                                                 ";
}



void imprayuda(void)
{
	//imprimimos las ayudas
	gotoxy(1,28);
	cout<<"F2 Guardar Archivo  F5 Cargar Archivo";
}

