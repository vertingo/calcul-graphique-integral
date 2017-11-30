#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <sdl/sdl.h>

#define XRES 800
#define YRES 600
#define MINX 0.0
#define MINY -6.0
#define MAXX 25.0
#define MAXY 630.0

#ifdef WIN32
#pragma comment(lib,"sdl.lib")
#pragma comment(lib,"sdlmain.lib")
#endif

double f(double x)
{
    // changez ici la fonction que vous voulez afficher. (pas forcément un polynome)
    return sqrt(x);
}

void waitkey()            // attend qu'on appuie sur ESC
{
    SDL_Event event;
    while(1)            // boucle
    {
        while(SDL_PollEvent(&event))        // aquisition d'evenement
        {
            if (event.type == SDL_KEYDOWN)  // on appuie sur une touche ?
            {
                if (event.key.keysym.sym == SDLK_ESCAPE) return;  // c'est "ESC" ?
            }
        }
        SDL_Delay(1);
    }
}

void SDL_PutPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *p;
    if (x<0 || y<0 || x>surface->w-1 || y>surface->h-1)
        return;
    p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32*)p = pixel;
}

void Line(SDL_Surface* surf,int x1,int y1, int x2,int y2,Uint32 couleur)  // Bresenham
{
    int x,y;
    int Dx,Dy;
    int xincr,yincr;
    int erreur;
    int i;

    Dx = abs(x2-x1);
    Dy = abs(y2-y1);
    if(x1<x2)
        xincr = 1;
    else
        xincr = -1;
    if(y1<y2)
        yincr = 1;
    else
        yincr = -1;

    x = x1;
    y = y1;
    if(Dx>Dy)
    {
        erreur = Dx/2;
        for(i=0;i<Dx;i++)
        {
            x += xincr;
            erreur += Dy;
            if(erreur>Dx)
            {
                erreur -= Dx;
                y += yincr;
            }
            SDL_PutPixel32(surf,x, y,couleur);
        }
    }
    else
    {
        erreur = Dy/2;
        for(i=0;i<Dy;i++)
        {
            y += yincr;
            erreur += Dx;
            if(erreur>Dy)
            {
                erreur -= Dy;
                x += xincr;
            }
            SDL_PutPixel32(surf,x, y,couleur);
        }
    }
    SDL_PutPixel32(surf,x1,y1,couleur);
    SDL_PutPixel32(surf,x2,y2,couleur);
}

int Re_to_EcrX(double r,double minX,double maxX)
{
    return (int)(XRES*(r-minX)/(maxX-minX));
}

int Re_to_EcrY(double r,double minY,double maxY)
{
    int y = (int)(YRES*(r-minY)/(maxY-minY));
    y = YRES - y - 1;
    return y;
}

double Ecr_to_ReX(int i,double minX,double maxX)
{
    return minX + i*(maxX-minX)/XRES;
}

double Ecr_to_ReY(int i,double minY,double maxY)
{
    return maxY - i*(maxY-minY)/YRES;
}


void ShowFoncion(SDL_Surface* screen,Uint32 couleur,double (*fonc)(double),int minX,int maxX,int minY,int maxY)
{
    int i;
    int lastx = 0;
    int lasty = 0;
    int x,y;
    double resfonc;

    for(i=0;i<XRES;i++)
    {
        x = i;
        resfonc = fonc(Ecr_to_ReX(i,minX,maxX));
        y = Re_to_EcrY(resfonc,minY,maxY);

        if (i!=0)
            Line(screen,x,y,lastx,lasty,couleur);
        lastx = x;
        lasty = y;

    }
}

void ShowAxis(SDL_Surface* screen,int minX,int maxX,int minY,int maxY)
{
    int centreX = Re_to_EcrX(0.0,minX,maxX);
    int centreY = Re_to_EcrY(0.0,minY,maxY);
    Line(screen,centreX,0,centreX,YRES-1,0xFFFFFF);  // axe vertical
    Line(screen,0,centreY,XRES-1,centreY,0xFFFFFF);  // axe horizontal
    Uint32 rouge = SDL_MapRGB(screen->format, 255, 0, 0);
    Uint32 bleu = SDL_MapRGB(screen->format, 0, 0, 255);
    Line(screen,(XRES/(maxX+1))*maxX,0,(XRES/(maxX+1))*maxX,YRES-1,rouge);
    Line(screen,(XRES/(maxX+1)),0,(XRES/(maxX+1)),YRES-1,rouge);

    int xmax,xpas,y;
    double resfonc2;
    xmax=(XRES/(maxX+1))*maxX;
    xpas=(XRES/(maxX+1));

    for(int i=xpas;i<xmax;i++)
    {
        resfonc2 = f(Ecr_to_ReX(i,minX,maxX));
        y = Re_to_EcrY(resfonc2,minY,maxY);
        Line(screen,i,y,i,centreY,bleu);
    }

    while(0);
}

/*Function definition to perform integration by Trapezoidal Rule */
double trapezoidal(double a,double b,int n){
  double x,h=0,sum=0,integral;
  double i;
  h=fabs(b-a)/n;

  for(i=1;i<n;i++){
    x=a+i*h;
    sum=sum+f(x);
  }
  integral=(h/2)*(f(a)+f(b)+2*sum);

  return integral;
}

double simpson(int n, double a, double b)
{
  double X, h, Iapp0, Iapp1, Iapp2, Iapp;
  int NN, i;

  // Etape 1
  h = (b - a) / n;

  // Etape 2
  Iapp0 = f(a) + f(b);
  Iapp1 = 0.0;
  Iapp2 = 0.0;

  // Etape 3
  NN = n -1;
  for (i=1; i<=NN; i++)
    {
      // Etape 4
      X = a + i*h;
      // Etape 5
      if ((i%2) == 0)
        Iapp2 = Iapp2 + f(X);
      else
        Iapp1 = Iapp1 + f(X);
    }

  // Etape 6
  Iapp = (Iapp0 + 2.0 * Iapp2 + 4.0 * Iapp1) * h / 3.0;

  // Etape 7
  return (Iapp);

}

void Calcul_Integral()
{
  int i,n;
  float a,b,spmthd;
  double minX, maxX, minY, maxY;
  char fonction[10];
  int fonction2[15];
  int choix;
  SDL_Surface *screen;

  SDL_Init(SDL_INIT_VIDEO);
  freopen("CON", "w", stdout); // redirects stdout
  freopen("CON", "w", stderr); // redirects stderr

  printf("Entrez la valeur a de la borne inferieure de l'interval de l'integral!\na=");
  scanf("%f",&a);
  printf("Entrez la valeur b de la borne superieure de l'interval de l'integral!\nb=");
  scanf("%f",&b);
  printf("Entrez la valeur n correspondant au nombre de decoupage de l'interval en trapeze!\nn=");
  scanf("%i",&n);
  trapezoidal(a,b,n);
  spmthd=trapezoidal(a,b,n);
  printf("\nValeur de l'integral: %f \n",spmthd);

  printf("\nEntrez le numero de l\'operation desiree?:\n");
  printf("\n(1) Afficher une representation graphique de la courbe?\n",spmthd);
  printf("\nQuel est votre choix? :");

  scanf("%d",&choix);

  switch(choix)
  {
   case 1:
         {
           minX=a-1;
           maxX=b+1;
           minY=-50;
           maxY=f(b)+1;

           screen=SDL_SetVideoMode(XRES,YRES,32,SDL_SWSURFACE|SDL_DOUBLEBUF);

           if(SDL_MUSTLOCK(screen))
           SDL_LockSurface(screen);

           ShowAxis(screen,minX,maxX,minY,maxY);

           ShowFoncion(screen,0x00FF00,f,minX,maxX,minY,maxY);

           if(SDL_MUSTLOCK(screen))
           SDL_UnlockSurface(screen);
           SDL_Flip(screen);
           waitkey();

          };break;

  }
}


int main(int argc, char *argv[])
{

  Calcul_Integral();

}
