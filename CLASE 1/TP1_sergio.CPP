#include<conio.h>
#include<stdlib.h>

const   DIM = 16;


int Es_Minuscula ( int );


// --------------------------------------------------------------
void main()
{
  char Buff[DIM*sizeof(int)];
  unsigned int Dir_May[DIM];
  unsigned int Dir_Min[DIM];
  int  Tecla;
  int  aux,i,j,k;
  clrscr(); highvideo(); randomize();

  // --- Carga Buff con caracteres alfabeticos -----------------
  for(i=0;i<DIM;i++) {
     do{
      	 Tecla=65+random(57);
       } while(Tecla>90 && Tecla<97);
     
     *(((int*)Buff)+i)=Tecla;  
}

  cprintf("\r\n\r\n");

  // --- Inicializa vectores de direcciones --------------------

  for(i=0;i<DIM;i++) 
  {
    Dir_May[i]=0;
    Dir_Min[i]=0;
  }

  // --- Salva direccs de las minusc y mayusculas --------------
  j=0;
  k=0;
  for(i=0;i<DIM;i++)
  {
      
      aux=*(((int*)Buff)+i);
      if(aux>=97 && aux<=122) 
        Dir_Min[j++]=(unsigned int)(((int*)Buff)+i);
      else
        Dir_May[k++]=(unsigned int)(((int*)Buff)+i);
  }

  // --- Muestra lo referenciado en cada vector.
cprintf("Minusculas: \r\n");
  for(i=0;i<j;i++)
       cprintf("%d ",*(int*)Dir_Min[i]);

  cprintf("Mayusculas: \r\n");

  for(i=0;i<k;i++)
      cprintf("%c ",*(int*)Dir_May[i]);


  
  // --- Muestra el vector desde un puntero auxiliar
  int * pAux;
  pAux=(int*) &Buff[0];

  
  cprintf("\r\nRecorriendo el buff con puntero auxiliar subindexada: \r\n");
  for(i=0;i<DIM;i++)
  cprintf("%c ",pAux[i]);//utlizando fomrma subindexada
  
  cprintf("\r\nRecorriendo el buff con puntero auxiliar indexada: \r\n");
  for(i=0;i<DIM;i++)
  cprintf("%c ",*(pAux+i));//utlizando fomrma indexada
  
  cprintf("\r\nEl tamaño del vector Buff es: %d",DIM*sizeof(int));

  getch();
}






