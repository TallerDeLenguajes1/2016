#include <iostream>
#include <conio2.h>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "cabecera.h"

using namespace std;

#define ANCHO 80
#define ALTO 25


void imprdib(char map[][ANCHO],int alto,int ancho); //Prototipo
void imprayuda(void); //Prototipo


int main() {
	
	char map[ALTO][ANCHO]; //mapa del grafico
	textcolor(WHITE);
	header cabecera; //Para llenar el struct del archivo
	cout.precision(2);
	cout << fixed;
	char t; //para leer el teclado
	
	char nombre[30]; //nombre de archivo
	char cad[ANCHO+3]; //cadena auxiliar para ayudar a guardar o leer de los archivos
	
	bool salir=true; //salir=false para salir
	
	int px,py; //coordenadas del pincel
	
	int alto=ALTO; //alto del mapa grafico
	int ancho=ANCHO; //ancho del mapa grafico
	
	int m,n,s=0; //auxiliares para for
	
	//iniciamos el mapa del grafico con ceros
	
	for(n=0;n<ALTO;++n)
		for(int m=0;m<ANCHO;++m) map[n][m]='0';
	
	px=py=0; // coordenadas del pincel para dibujar (0,0)
	
	imprdib(map,alto,ancho); //imprimimos la zona de dibujo llena de 0s
	
	imprayuda(); //Mostramos los comandos
	
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
			
			//Las teclas modifican py,px y muestran las coordenadas actuales
			
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
			
			if(t=='1') //pintamos camino al presionar 1
			{
				if (map[px][py]=='1') map[px][py]='0';
				else map[px][py]='1';
				putchar(map[px][py]); 
				
			}
			
			if(t=='2') //pintamos bloque. Solo en "1".
			{
				s++;
				if((s>4))s=1;
				
				if (map[px][py]!='0'){ //Siempre y cuando distinto de 0
					switch (s){
						case 1:
							if (map[px][py]=='1') map[px][py]='2'; //Puerta Roja
							else map[px][py]='2';
							putchar(map[px][py]);
							break;
							
						case 2:
							if (map[px][py]=='1') map[px][py]='3'; //Llave roja
							else map[px][py]='3';
							putchar(map[px][py]);
							break;						
							
						
						case 3: 	
							if (map[px][py]=='1') map[px][py]='4'; //Puerta amarilla
							else map[px][py]='4';
							putchar(map[px][py]);
							break;						
							
						case 4: 	
							if (map[px][py]=='1') map[px][py]='5'; //Lave amarilla
							else map[px][py]='5';
							putchar(map[px][py]);
							break;								
						default:
						s=0;
							
					}
					
				}
			}
			
			if ((t=='3')) //Asigna la pos px py al struct, coordenadas de inicio
			{
			
				cabecera.inX = py;
				cabecera.inY = px;
				gotoxy(1,30);
				cout << "Coordenadas de ENTRADA  Y: " << cabecera.inX << " " << "X: " << cabecera.inY << "\b";
				
			}
			
			if ((t=='4')) //Asigna pos px py al struct como coordenada de salida
			{
			
				cabecera.outX = py;
				cabecera.outY = px;
				gotoxy(1,30);
				cout << "Coordenadas de SALIDA   Y: " << cabecera.outX << " " << "X: " << cabecera.outY << "\b";
					
			}
			
						
			if(t==61)//F2 para guardar
			{

				ofstream sal; //manejador de archivo de salida
				gotoxy(1,29); //espacio para el pedido de nombre
				cout<<"Introduce el nombre del archivo a guardar:";
				cin.getline(nombre,30); //Escribo nombre y lo guardo
				strcpy(cabecera.nombre,nombre); //Copio el nombre a mi struct
				strcpy(cabecera.recordnombre,"PLAYER");
				cabecera.record = 9999; //Record es igual a 9999.
				cabecera.tamX = ancho; //Ancho y alto fijos, los copio al struct
				cabecera.tamY = alto; 
				
				sal.open(nombre); //abrimos el archivo "nombre" para escritura 
				
				//El guardado del struct se hace a partir del primer byte del archivo (PUT en 0)
				sal.seekp(0); //Puntero PUT en byte 0
				
				sal.write((char *)&cabecera, sizeof(header)); //Escribo mi struct en el archivo
			
				//A partir del byte 4000 finaliza la cabecera y comienza el mapa
				
				sal.seekp(4000); //Puntero PUT en 4000
				
				for(int n=0;n<alto;++n) //leemos linea por linea el archivo
				{
					cad[0]='\"';
					strncpy(cad+1,map[n],ancho); //copiamos la linea a una cadena
					cad[ancho+1]='\"';
					cad[ancho+2]=0; //por un bug en el compilador hay que agregar '\0'
					sal<<cad<<endl; //enviamos la linea al archivo con un enter al final
				}
				
				sal.close(); //cerramos el archivo
				gotoxy(1,29); //borramos el pedido de nombre
				cout << "                                                                          " ;
				gotoxy(1,29);
				cout << "Guardado exitosamente";
				
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
				
				ent.seekg(4000); //Puntero GET en 4000

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
					
				
					clrscr();                                            //borramos la pantalla e imprimimos todo de nuevo
					imprdib(map,alto,ancho);                             //imprimimos la zona de dibujo
				
				
				gotoxy(1,28); //Una vez cargado, muestra la cabecera del mapa.
			 	cout << "||Mapa: " << cabecera.nombre << "         ||" << "Record: " << cabecera.record << " secs de " << cabecera.recordnombre << endl;
			 	cout << "||Inicio en X:" << cabecera.inX << "  Y:" << cabecera.inY;
				cout << "    ||Fin en  X:" << cabecera.outX << "  Y:" << cabecera.outY << endl;
				
				imprayuda();                                           //imprimimos las ayudas
				}   
				
				

				
			
			gotoxy(py+2,px+2); //fijamos el cursor en su lugar
		}
		
		
		if(t==67){ //Con F9 se muestra la ayuda avanzada
			clrscr();
			gotoxy(1,1);
			cout << "Crea caminos con la tecla 1 " <<endl;	
			cout << "Con la tecla 2 puedes poner items en los senderos " <<endl;
			cout << "             2= Puerta Roja" <<endl;
			cout << "             3= Llave Roja" <<endl;
			cout << "             4= Puerta Verde" <<endl;
			cout << "             5= Llave Verde" <<endl;
			cout << "Con la tecla 3 posicionas el lugar donde el jugador incia" <<endl;
			cout << "Con la tecla 4 posicionas el area donde se gana el mapa" <<endl;
			cout << "PRESIONE CUALQUIER TECLA PARA CONTINUAR" <<endl;
			
			getch(); //Presianar cualquier tecla para volver a mostrar mapa
			clrscr();
			imprdib(map,alto,ancho);
			imprayuda();
				}
		}
	
	return 0;
}


void imprdib(char map[][ANCHO],int alto,int ancho)
{
	int m,n;

	gotoxy(1,1); //Primer FOR para el recuadro del editor
	cout<<(char)201; //Esquina del recuadro
	for(n=0;n<ancho;++n) cout<<(char)205; //Limite superior recuadro
	cout<<(char)187<<" ";
	for(m=0;m<alto;++m)
	{
		gotoxy(1,m+2);
		cout<<(char)186; //Limite izquierdo
		
		for(int n=0;n<ancho;++n) {
			
			if(map[m][n]=='0'){  //Limite derecho
				cout <<(char)178 ;
			}else if (map[m][n]=='1') { //Lee los 1 y los escribe como vacio
				cout << ' ' ;
			}else{
				cout<< map[m][n]  ; //Escribe el resto tal y como esta en el archivo
			};
		}
		cout<<(char)186<<" "; //Limite derecho recuadro
	}
	gotoxy(1,m+2);
	cout<<(char)200; 
	for(n=0;n<ancho;++n) cout<<(char)205; //Limite inferior
	cout<<(char)188<<" ";
	gotoxy(1,m+3);
	//cout<<"                                                                                 ";
}

void imprayuda(void)
{
	//imprimimos las ayudas iniciales
	gotoxy(61,28);
	cout<<"||F2-Guardar  F5-Cargar";
	gotoxy(61,29);
	cout<<"||F9-Ver Ayuda";

}

