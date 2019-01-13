#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct
{   
    char tag[3];
    char nombre[30];
    char artista[30];
    char album[30];
    char anio[4];
    char comentario[28];
    unsigned char nulo[1];
    unsigned char track[1];
    unsigned char genero[1];

}TTAG;
// -------------------------------------------------------------------------------------------------------------------
void main()
{
	 FILE *Fuente;
	 char  NombFuente [128]  = "Travesura2.mp3"; 
	 char  BuffFuente [128];
	 int   Leidos;
	 int   i;
     char car;
     TTAG  DTAG;
    if((Fuente=fopen(NombFuente,"rb"))==NULL) {
    	  cprintf("ARCHIVO FUENTE NO ENCONTRADO\r\n");
    	  getch(); return;
    }


    fseek(Fuente,-128,SEEK_END);
    Leidos=fread(&DTAG,sizeof(TTAG),1,Fuente);

    cprintf("TAG: tema:%s artista:%s album:%s\r\n",DTAG.nombre,DTAG.artista,DTAG.album);

    cprintf("TAG: anio:%c%c%c%c comentario:%s\r\n",DTAG.anio[0],DTAG.anio[1],DTAG.anio[2],DTAG.anio[3],DTAG.comentario);
    //car=DTAG.track[0];
   cprintf("TAG:nro track:%c genero tema1:%c \r\n",DTAG.track,DTAG.genero);

   getch();
   fseek(Fuente,-128,SEEK_END);     
    Leidos=fread(BuffFuente,1,sizeof(BuffFuente),Fuente);
    for(i=0;i<Leidos-3;i++){
        cprintf("caracter %d: %d\r\n",i,BuffFuente[i]);
    getch();
    }
    fclose(Fuente); 
}
