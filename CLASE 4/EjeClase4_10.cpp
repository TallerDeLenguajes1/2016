#include <conio.h>
#include <alloc.h>
#include <stdlib.h>

const ESC = 27;

typedef unsigned int BYTE;
typedef struct  { BYTE R; BYTE G; BYTE B; }TColor;

void *ResMem       ( int Total         );
void  MostrarTabla ( TColor **p, int C );

// ----------------------------------------------------------
void main()
{
  TColor    **Foto;
  int         F     = 5; // dimension horizontal de la foto.
  int         C     = 10; // dimension vertical de la foto.
  int         i,j;

  clrscr(); highvideo(); randomize();

  Foto=(TColor **)ResMem(F*sizeof(TColor *));

  // --- asigna la tabla de colores -----------------

  for(i=0;i<F;i++){
      Foto[i]=(TColor *)ResMem(C*sizeof(TColor));
      for(j=0;j<C;j++){
    	  Foto[i][j].R=random(256);
    	  Foto[i][j].G=random(256);
    	  Foto[i][j].B=random(256);
      }
  }

  for(i=0;i<F;i++) 
    MostrarTabla(&Foto[i],C);

  getch();

}

// -----------------------------------------------------------
void *ResMem(int Total)
{
  void *p;
  if((p = malloc(Total))==NULL) {
      cprintf("NO PUDO RESERVAR MEMORIA");
      getch(); exit(1);
  }
  return(p);
}

// -----------------------------------------------------------
void MostrarTabla(TColor **p, int C)
{
	   int i;
	   int Col  = 2;
 static int Fila = 1;
 static int fila_mostrar = 1;
 textcolor(LIGHTRED);
 gotoxy(2,Fila); cprintf("FILA %d - %d",fila_mostrar,Fila);
 textcolor(WHITE);
 for(i=0;i<C;i++,Col+=4){
    gotoxy(Col,Fila+1); 
    cprintf("%d",(*p)[i].R);
    gotoxy(Col,Fila+2); 
    cprintf("%d",(*p)[i].G);
    gotoxy(Col,Fila+3); 
    cprintf("%d",(*p)[i].B);
 }
 Fila+=5;  
 fila_mostrar++; 
 if(getch()==ESC) 
    exit(1);
}
// ---------------------------------------------------------
