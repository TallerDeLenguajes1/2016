#include <conio.h>
#include <stdlib.h>
#include <process.h>

typedef struct  {
		       float *Max;
		       float *Min;
		     }TExtr;
const int DIM1 = 5;
const int DIM2 = 5;

void   *ReservarMemoria        ( int Total              );
void    ProcesarDatos          ( float **p1, TExtr *p2  );
void    MostrarDatos           ( float **p              );
void    MostrarProcesamientos  ( float **p1, TExtr *p2  );

// ------------------------------------------------------------



void main()
{
  float    **p1;
  TExtr     *p2;
  int       i,j;

  clrscr(); highvideo(); randomize();

  // --- RESERVA PARA LAS ESTRUCTURAS DE PROCESAMIENTO -----
  p2=(TExtr *)ReservarMemoria(DIM1*sizeof(TExtr));

  // --- RESERVAS PARA LA MATRIZ DINAMICA ------------------
  p1=(float **)ReservarMemoria(DIM1*sizeof(float *));
  for(i=0;i<DIM1;i++) {
      p1[i]=(float *)ReservarMemoria(DIM2*sizeof(float));
      for(j=0;j<DIM2;j++) 
        p1[i][j]=(5000+random(5001))*0.01;
  }

  ProcesarDatos(p1,p2);
  MostrarDatos(p1);
  getch();
  MostrarProcesamientos(p1,p2);

  getch();
}
// -----------------------------------------------------------
void *ReservarMemoria(int Total)
{
  void *p;
  if((p=malloc(Total))==NULL) {
      cprintf("NO PUDO RESERVAR MEMORIA DINAMICA");
      getch(); exit(1);
  }
  return(p);
}
// -----------------------------------------------------------
void ProcesarDatos(float **p1, TExtr *p2)
{
  int      i,j;
  float    Max;
  float    Min;
  float   *DirMax;
  float   *DirMin;

  for(i=0;i<DIM1;i++) {
      Max=0.0;  Min=999.0;
      // --- INICIALIZA DIRECCIONES DE MIEMBROS ----
      p2[i].Max=&(p1[i][0]);
      p2[i].Min=&(p1[i][0]);

      for(j=0;j<DIM2;j++) {
      	  if(((p2[i].Max)[j]) > Max) {
      		 Max=(p2[i].Max)[j];
      		 DirMax=&((p2[i].Max)[j]);
      	  }
      	  if(((p2[i].Min)[j]) < Min) {
      		 Min=(p2[i].Min)[j];
      		 DirMin=&((p2[i].Min)[j]);
      	  }
      }

      p2[i].Max=DirMax;
      p2[i].Min=DirMin;
  }
}

// -----------------------------------------------------------
void MostrarDatos(float **p)
{
  int i,j;

  textcolor(WHITE);
  cprintf(" --- DATOS ALMACENADOS EN LA MATRIZ DINAMICA ---\r\n");
  cprintf("\r\n");

  textcolor(LIGHTRED);
  for(i=0;i<DIM1;i++) {
      for(j=0;j<DIM2;j++) cprintf("%6.2f",p[i][j]);
      cprintf("\r\n");
  }
  cprintf("\r\n");
}
// ------------------------------------------------------------
void MostrarProcesamientos(float **p1, TExtr *p2)
{
  int i,j;

  textcolor(WHITE); 
  cprintf(" --- POSICIONES DE MAXIMOS Y MINIMOS Y SUS VALORES ---\r\n\r\n");
  textcolor(LIGHTGREEN);

  for(i=0;i<DIM1;i++) {
      cprintf(" Direcc_Fila %d = %u\r\n" ,i,&p1[i][0]);
      cprintf(" Direcc_Max = %u, valor: %6.2f",p2[i].Max,*p2[i].Max);
      cprintf(" Direcc_Min = %u, valor: %6.2f",p2[i].Min,*p2[i].Min);
      cprintf("\r\n");
  }
}
// ----------------------------------------------------------


