#include <conio.h>
#include <stdio.h>

int FileSize   ( FILE * );
long TamanioArchivo( FILE* );
// ----------------------------------------------------------------------------------------------------------------
void main( )
{
    char   NombArchi[128] = "listado de propiedades.bin";
    FILE *pArchivo;
    clrscr();
    if((pArchivo=fopen(NombArchi,"rb"))==NULL) {
           cprintf("NO PUDO ABRIR EL ARCHIVO.");
           getch();
     }
    cprintf("Tamanio de %s : %d\r\n",NombArchi,FileSize(pArchivo));
    cprintf("Tamanio de %s : %d\r\n",NombArchi,TamanioArchivo(pArchivo));

    getch();

}

// --------------------------------------------------------------------------------------------------------------
int FileSize(FILE *NombArchi)
{
	 char   Buff[1024];
     int    Cuenta = 0;
     int    Leidos;
     //while((Leidos=fread(Buff,sizeof(Buff),1,NombArchi))!=0) 
       while((Leidos=fread(Buff,1,sizeof(Buff),NombArchi))!=0) 
        Cuenta+=(Leidos);
     return(Cuenta);
}

// --------------------------------------------------------------------------------------------------------------
long TamanioArchivo(FILE *P_File)
{
long Pos, TamArch;
Pos = ftell(P_File); // Guardar el posicion actual del puntero
fseek(P_File,0, SEEK_END); // Ir al final del Archivo
TamArch = ftell(P_File); // Almacenar el Tamaño del Archivo
fseek(P_File,Pos, SEEK_SET); // Restablecer puntero
return(TamArch);
}
