#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <conio2.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "cabecera.h"
#include <time.h>
#include <ctime>
#include <iomanip>

#define ANCHO 80
#define ALTO 25
using namespace std;

 //Prototipado de funciones
void imprdib(char** mapa,int alto,int ancho);
void mover(char** mapa,int* x, int* y, int movX, int movY);
bool win(int x,int y, header cabecera);

//Variables globales de llaves
bool llaveR = false;
bool llaveV = false;

int main() {
	

	int gOver = 0;
	char nombre[30];
	header cabecera;	
												//Inicializar stuct
	cout.precision(2);
	cout << fixed;
	char** mapa;														//Incializo mapa
	mapa = new char*[ALTO];
	
	
	//Menu y show

	textcolor(LIGHTGREEN);
	gotoxy(30,10);
	cout << "    {__         {__       {__                             " <<endl;
	gotoxy(30,11);
	cout << " {__   {__      {_ {__   {___                             " <<endl;
	gotoxy(30,12);
	cout << "{__             {__ {__ { {__   {__    {____ {__   {__    " <<endl;
	gotoxy(30,13);
	cout << "{__       {_____{__  {__  {__ {__  {__      {__  {_   {__ " <<endl;
	gotoxy(30,14);
	cout << "{__             {__   {_  {__{__   {__    {__   {_____ {__" <<endl;
	gotoxy(30,15);
	cout << " {__   {__      {__       {__{__   {__   {__    {_        " <<endl;
	gotoxy(30,16);
	cout << "   {____        {__       {__  {__ {___{________  {____   " <<endl;

	textcolor(WHITE);
	gotoxy(33,18);
	cout << "Programado por";
	textcolor(LIGHTGREEN);
	cout << " Facundo Lopez Sales";
	textcolor(WHITE);
	cout << " y";
	textcolor(LIGHTGREEN);
	cout << " Franco Arganaraz";
	gotoxy(47,20);
	textcolor(WHITE);
	cout<<"Mapa a cargar: ";
	textcolor(YELLOW);
	cin.getline(nombre,30);
	
	
	for (int i = 0; i < ALTO; i++)										//Inicializar
	{
		mapa[i] = new char[ANCHO];
	}
	
																		//CARGANDO MAPA
	int m;
	int alto=ALTO; 														//alto del mapa grafico
	int ancho=ANCHO; 													//ancho del mapa grafico
	char cad[ANCHO+3]; 													//cadena auxiliar para ayudar a guardar o leer de los archivos
	 																	
		ifstream ent(nombre); 											//creamos el objeto para manejar entrada
		if (ent.fail())
					{
						cout<<"Error de Archivo";
					}
				
				ent.seekg(0); //Puntero GET en 0
				
				ent.read((char *)&cabecera,sizeof(header));
				
				
		//show//		
				
					gotoxy(20,24);
					cout << "Cargando... ";
					Sleep(500);
					cout << cabecera.nombre <<endl;
					gotoxy(20,25);
					Sleep(1000);
					cout << "Record: " << cabecera.record << " segundos realizado por " << cabecera.recordnombre <<endl;
					Sleep(3000);
					gotoxy(20,26);
					cout << "Comenzando en 3...";
					Sleep(1300);
					cout << "2...";
					Sleep(1300);
					cout << "1...";
					Sleep(1000);
				
				
				ent.seekg(4000); //Puntero GET en 4000

					m=0;                                                //para contar la cantidad de lineas
					do{
						ent.getline(cad,ANCHO+3);                       //leemos una linea del archivo ent y la colocamos en cad
						ancho=strlen(cad)-2;                            //obtenemos longitud de cad con strlen (devuelve tamaño)
						memcpy(mapa[m],cad+1,ancho);                     //copiamos ancho caracteres (memcpy es parecida a strncpy solo que no coloca el '\0' )
						++m;
						if(m>ALTO-1) break;                             //si superamos la cantidad de lineas que podemos almacenar terminamos la carga
					}while(!ent.eof());                                 //leemos hasta que el achivo se acabe
					alto=m;
					if(alto<1) alto=1;                                  //si el archivo tiene lineas vacias acomodamos
					if(ancho<1) ancho=1;                                //alto y ancho
					ent.close();
					clrscr();                                           //borramos la pantalla e imprimimos todo de nuevo

	int tecla;
	char newrecord[10];													//Por si jugador rompe record
	//////////////////////////////////////////////////////////////////////inicializo jugador
	int* jx;															//Inicializo variables
	int* jy;
	jx = new int();
	jy = new int();
	char jug = char(254);
	//Valores de posicion donde inicia el jugador leidas del archivo
	*jx= cabecera.inX;
	*jy= cabecera.inY;
	mapa[*jy][*jx] = jug;												//colocamos en matriz al jugador  
	

	imprdib(mapa,alto,ancho);											//imprimir mapa
	
	clock_t begin = clock(); 											//Inicia reloj
	
	//inicio de juego
	while (gOver == 0) {
		
			//captura de teclado
			if (kbhit()) {
				tecla = getch();
				
				switch (tecla){
					
				case 75:   //izquierda
					mover(mapa,jx,jy,-1,0);
				break;			
					
				case 77:   //derecha
					mover(mapa,jx,jy,1,0);
					break;
					
				case 80:   //abajo
					mover(mapa,jx,jy,0,1);
					break;
			 
				
				case 72:   //arriba
					mover(mapa,jx,jy,0,-1);
				break;
				} 
			
			if (win(*jx,*jy,cabecera)) gOver =1; 						//Despues de cada movimiento revisa si se ganó o no
		}
	}

	//Game Over se ejecuta cuando se sale del bucle anterior 
	
	clock_t end = clock();												//Revisa cuantos segundos demoró en ganar
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	
	clrscr();
	gotoxy(20,10);
	textcolor(LIGHTGREEN);
	cout << "  @@@@@@@   @@@@@@  @@@@@@@@@@  @@@@@@@@       @@@@@@  @@@  @@@ @@@@@@@@ @@@@@@@ " <<endl;
	gotoxy(20,11);
	cout << " !@@       @@!  @@@ @@! @@! @@! @@!           @@!  @@@ @@!  @@@ @@!      @@!  @@@"<<endl;
	gotoxy(20,12);
	cout << " !@! @!@!@ @!@!@!@! @!! !!@ @!@ @!!!:!        @!@  !@! @!@  !@! @!!!:!   @!@!!@! "<<endl;
	gotoxy(20,13);
	cout << " :!!   !!: !!:  !!! !!:     !!: !!:           !!:  !!!  !: .:!  !!:      !!: :!! "<<endl;
	gotoxy(20,14);
	cout << "  :: :: :   :   : :  :      :   : :: :::       : :. :     ::    : :: :::  :   : :"<<endl;
	gotoxy(20,15);

	
	//cout << "GANASTE  EN " << elapsed_secs << " segundos";
	if (cabecera.record > elapsed_secs){
		gotoxy(40,16);
		cout << "NUEVO RECORD DE MAPA!"<<endl;
		gotoxy(40,17);
		cout << "Ingrese su nombre: ";
		textcolor(YELLOW);
		cin.getline(newrecord,30);
		
		strcpy(cabecera.recordnombre,newrecord);
		cabecera.record = elapsed_secs;
		fstream sal;													//Declaro el objeto
		sal.open(nombre);												//abrimos el archivo "nombre" para escritura 
		sal.seekp(0); 													//Puntero PUT en 0
		sal.write((char *)&cabecera, sizeof(header)); 					//Escribo mi struct en el archivo
		sal.close();
		
		textcolor(LIGHTGREEN);													//Cierro el archivo
		gotoxy(40,18);
		cout << "Su record se ha guardado exitosamente ";
		textcolor(YELLOW);
		cout << newrecord << "!";
		textcolor(LIGHTGREEN);
	}
	
	gotoxy(40,19);
	Sleep(2500);
	return 0;

}

void imprdib(char **mapa,int alto,int ancho){
	int m;
	for(m=0;m<alto;++m)
	{
		gotoxy(1,m+2);
		
		for(int n=0;n<ancho;++n) 
			if (mapa[m][n] == '1'){
				textcolor(WHITE);
				cout << ' ';
				
			 }else if (mapa[m][n] =='0'){ //Pared
				textcolor(WHITE);
				cout << (char)219;
				
			 }else if (mapa[m][n] =='2'){ //Puerta Roja
				textcolor(RED);
				cout << (char)219;
				textcolor(WHITE);
				
			 }else if (mapa[m][n] =='3'){ //Lave Roja
				textcolor(RED);
				cout << (char)197;
				textcolor(WHITE);
				
			 }else if (mapa[m][n] =='4'){ //Puerta Verde
				textcolor(GREEN);
				cout << (char)219;
				textcolor(WHITE);
				
			 }else if (mapa[m][n] =='5'){ //Llave Verde
				textcolor(GREEN);
				cout << (char)197;
				textcolor(WHITE);						
					
			 }else cout << mapa[m][n];
	}
	
}

bool win(int x,int y, header cabecera){
	
	if ( (x == (cabecera.outX))  && (y == (cabecera.outY)))
	{ 
		return true;
	}
	return false;
}




void mover(char** mapa,int* x, int* y, int movX, int movY){				//Funcion recibe donde estoy parado y hacia donde voy en **map
	char jug = char(254);
	
	if (mapa[*y+movY][*x+movX] != '0'){									// Si es distinto de 0...
			switch (mapa[*y+movY][*x+movX]){
				
				case '1':												//Si map=1 avanzo
					mapa[*y][*x] = '1';
					gotoxy(*x+1,*y+2);
					cout << ' ';
					*y +=movY;
					*x +=movX;
					mapa[*y][*x] = jug;
					gotoxy(*x+1,*y+2);
					cout << jug;
					break;
					
				case '2':												//Si map=2 es puerta y solo se avanza si llaveR = true
					if (llaveR == true){
						mapa[*y][*x] = '1';
						gotoxy(*x+1,*y+2);
						cout << ' ';
						*y +=movY;
						*x +=movX;	
						mapa[*y][*x] = jug;
						gotoxy(*x+1,*y+2);
						cout << jug;
						llaveR = false;
						gotoxy(1,28);
						cout << " Llave Roja "; if (llaveR==false) cout<< "No";
						
					}
					break;
				case '3':												//Si map=3 llaveR = true
					
					llaveR = true;
					mapa[*y][*x] = '1';
					gotoxy(*x+1,*y+2);
					cout << ' ';
					*y +=movY;
					*x +=movX;	
					mapa[*y][*x] = jug;
					gotoxy(*x+1,*y+2);
					cout << jug;
					gotoxy(1,28);
					cout << " Llave Roja "; if (llaveR==true) cout<< "Si";
					break;
					
				case '4':												//Si map=4 es puerta y solo se avanza si llaveV = true
					if (llaveV == true){
						mapa[*y][*x] = '1';
						gotoxy(*x+1,*y+2);
						cout << ' ';
						*y +=movY;
						*x +=movX;	
						mapa[*y][*x] = jug;
						gotoxy(*x+1,*y+2);
						cout << jug;
						llaveV = false;
						gotoxy(1,29);
						cout << " Llave Verde "; if (llaveV==false) cout<< "No";
						
					}
					break;
					
				case '5':												//Si map=3 llaveV = true
					
					llaveV = true;
					mapa[*y][*x] = '1';
					gotoxy(*x+1,*y+2);
					cout << ' ';
					*y +=movY;
					*x +=movX;	
					mapa[*y][*x] = jug;
					gotoxy(*x+1,*y+2);
					cout << jug;
					gotoxy(1,29);
					cout << " Llave Verde "; if (llaveV==true) cout<< "Si";
					break;							
				}	
			
		}	
}
