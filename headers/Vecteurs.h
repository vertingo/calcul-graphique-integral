///////////////////////////////////////
//                                   //
//          MATH 2nd (M2nd)          //
//                                   //
//     (c) Nicolas DUBIEN - 2006     //
//                                   //
///////////////////////////////////////

#include "utilisateur.h"
#include "utilitaires.h"

using namespace std;


#ifndef VECTEURS_H
#define VECTEURS_H


void vec_milieu() {
	cout <<"\n\nSoit le segment [AB]";
	cout <<"\n\nA(xA;yA)";
	cout <<"\nB(xB;yB)";
	cout <<"\n\nxA=";
	double xa(getdouble());
	cout <<"yA=";
	double ya(getdouble());
	cout <<"\nxB=";
	double xb(getdouble());
	cout <<"yB=";
	double yb(getdouble());
	cout <<"\n\nSoit I le milieu de [AB]";
	cout <<"\n\nI(("<<xa<<"+"<<xb<<")/2;("<<ya<<"+"<<yb<<")/2)";
	cout <<"\nI("<<xa+xb<<"/2;"<<ya+yb<<"/2)";
	cout <<"\nI("<<(xa+xb)/2<<";"<<(ya+yb)/2<<")";
}

void vec_align3_1() {
	cout <<"\n\nSoit trois points: A(xA;yA), B(xB;yB) et C(xC;yC)";
	cout <<"\n\nxA=";
	double xa(getdouble());
	cout <<"yA=";
	double ya(getdouble());
	cout <<"\nxB=";
	double xb(getdouble());
	cout <<"yB=";
	double yb(getdouble());
	cout <<"\nxC=";
	double xc(getdouble());
	cout <<"yC=";
	double yc(getdouble());
	cout <<"\n\n->";
	cout <<"\nAB("<<xb-xa<<";"<<yb-ya<<")";
	cout <<"\n->";
	cout <<"\nAC("<<xc-xa<<";"<<yc-ya<<")";
	cout <<"\n\n"<<xc-xa<<"="<<xb-xa<<"*"<<(xc-xa)/(xb-xa);
	cout <<'\n'<<yc-ya<<"="<<yb-ya<<"*"<<(yc-ya)/(yb-ya);
	if((xc-xa)/(xb-xa)==(yc-ya)/(yb-ya)) {
		cout <<"\n\nVecteur AB = Vecteur AC * "<<(yc-ya)/(yb-ya)<<".";
		cout <<"\n\nAinsi les vecteurs AB et AC sont colineaires\net les points A, B et C sont alignes.";
		}
	else cout <<"\n\nLes points A, B et C ne sont pas alignes.";
}

void vec_align3_2() {
	cout <<"\n\nSoit trois points: A(xA;yA), B(xB;yB) et C(xC;yC)";
	cout <<"\n\nxA=";
	double xa(getdouble());
	cout <<"yA=";
	double ya(getdouble());
	cout <<"\nxB=";
	double xb(getdouble());
	cout <<"yB=";
	double yb(getdouble());
	cout <<"\nxC=";
	double xc(getdouble());
	cout <<"yC=";
	double yc(getdouble());
	cout <<"\n\n->";
	cout <<"\nAB(x;y)=("<<xb-xa<<";"<<yb-ya<<")";
	cout <<"\n->";
	cout <<"\nAC(x\';y\')=("<<xc-xa<<";"<<yc-ya<<")";

	cout <<"\n\n"<<xb-xa<<"*"<<yc-ya<<"-"<<yb-ya<<"*"<<xc-xa;
	cout <<'\n'<<(xb-xa)*(yc-ya)<<"-"<<(yb-ya)*(xc-xa)<<"="<<(xb-xa)*(yc-ya)-(yb-ya)*(xc-xa);
	if((xb-xa)*(yc-ya)-(yb-ya)*(xc-xa)==0) {
		cout <<"\n\nx*y\'-y*x\'=0";
		cout <<"\nDonc les vecteurs AB et AC sont colineaires\net les points A, B et C sont alignes.";
	} else {
		cout <<"\n\nx*y\'-y*x\' \"different de\" 0";
		cout <<"\nDonc les vecteurs AB et AC ne sont pas colineaires\net les points A, B et C ne sont pas alignes.";
	}
}

void vec_norme() {
	cout <<"\n\n               -->";
	cout <<"\nSoit le vecteur A(x;y)";
	cout <<"\n\nx=";
	double x(getdouble());
	cout <<"y=";
	double y(getdouble());
	cout <<"\n\n  -->";
	cout <<"\n|| A || =V("<<(x*x+y*y)<<")";
	double reduction(div_racine(x*x+y*y));
	cout <<"\n\n  -->";
	cout <<"\n|| A || =V("<<(x*x+y*y)<<")";
	if(reduction!=0) {
		cout <<"\n  -->";
		cout <<"\n|| A || =V("<<((x*x+y*y))/reduction<<"*"<<reduction<<")";
		cout <<"\n  -->";
		if(reduction==(x*x+y*y)) cout <<"\n|| A || ="<<sqrt((x*x+y*y));
		else cout <<"\n|| A || ="<<sqrt(reduction)<<"V("<<((x*x+y*y))/reduction<<")";
	}
}

void vec_distances() {
	cout <<"\n\nSoit deux points: A(xA;yA) et B(xB;yB)";
	cout <<"\n\nxA=";
	double xa(getdouble());
	cout <<"yA=";
	double ya(getdouble());
	cout <<"\nxB=";
	double xb(getdouble());
	cout <<"yB=";
	double yb(getdouble());
	cout <<"\n[AB]=V("<<(xa-xb)*(xa-xb)+(ya-yb)*(ya-yb)<<")";
	double reduction(div_racine((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb)));
	cout <<"\n\n[AB]=V("<<(xa-xb)*(xa-xb)+(ya-yb)*(ya-yb)<<")";
	if(reduction!=0) {
		cout <<"\n[AB]=V("<<((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb))/reduction<<"*"<<reduction<<")";
		if(reduction==(xa-xb)*(xa-xb)+(ya-yb)*(ya-yb)) cout <<"\n[AB]="<<sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
		else cout <<"\n[AB]="<<sqrt(reduction)<<"V("<<((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb))/reduction<<")";
	}
}

void vec_vecteur() {
    int choix;
	cout <<"\n\nSoit deux points: A(xA;yA) et B(xB;yB)";
	cout <<"\n\nxA=";
	double xa(getdouble());
	cout <<"yA=";
	double ya(getdouble());
	cout <<"\nxB=";
	double xb(getdouble());
	cout <<"yB=";
	double yb(getdouble());
	cout <<"\n\n->";
	cout <<"\nAB=("<<xb-xa<<";"<<yb-ya<<")";
    /*printf("\n(1) Afficher le vecteur dans un plan?\n");
    printf("\nQuel est votre choix?:");
    scanf("%d",&choix);

    switch(choix)
    {
        case 1:
        {
          Uint32 couleur2[100];
          SDL_Surface *screen2;

          SDL_Init(SDL_INIT_VIDEO);

          screen2=SDL_SetVideoMode(800,600,32, SDL_SWSURFACE|SDL_DOUBLEBUF);


          exemples de couleurs avec leurs trois composantes RGB
         couleur2[0]=SDL_MapRGB(screen2->format,0,0,0);
         SDL_FillRect(screen2,0,couleur2[0]); donne un fond blanc à la fenêtre
        }
    }*/

}

void vec_produit_scalaire() {
	cout <<"\n\nSoit deux points le vecteur AB: A(xA;yA) et B(xB;yB)";
	cout <<"\n\nxA=";
	double xa(getdouble());
	cout <<"yA=";
	double ya(getdouble());
	cout <<"\nxB=";
	double xb(getdouble());
	cout <<"yB=";
	double yb(getdouble());
	cout <<"\n\nSoit deux autres points le vecteur CD: C(xC;yC) et D(xD;yD)";
	cout <<"\n\nxC=";
	double xc(getdouble());
	cout <<"yC=";
	double yc(getdouble());
	cout <<"\nxD=";
	double xd(getdouble());
	cout <<"yD=";
	double yd(getdouble());

    cout <<"\nAB=("<<xb-xa<<";"<<yb-ya<<")";
    cout <<"\nCD=("<<xd-xc<<";"<<yd-yc<<")";

	cout <<"\n[AB]*[CD]=V("<<(xb-xa)*(xd-xc)+(yb-ya)*(yd-yc)<<")";
	double scalaire((xb-xa)*(xd-xc)+(yb-ya)*(yd-yc));

	if(scalaire==0)
    {
         cout <<"\nLe produit scalaire des vecteurs [AB]*[CD]=0 les vecteurs sont donc orthogonaux! Il se coupent en formant un angle de 90°";
    }
    else
    {
         cout <<"\nLe produit scalaire des vecteurs [AB]*[CD]="<<scalaire<<" les vecteurs ne sont donc pas orthogonaux!";
    }

}

void menuvecteurs() {
	cout <<"\n\nCalcul Vectoriel!";
	cout <<"\n\n(1) Calculer la distance entre deux points";
	cout <<"\n(2) Donner les coordonnees du milieu d'un segment";
	cout <<"\n(3) Donner les coordonnees d'un vecteur";
	cout <<"\n(4) Calculer la norme d'un vecteur";
	cout <<"\n(5) Demontrer l'alignement de trois points (technique n1)";
	cout <<"\n(6) Demontrer l'alignement de trois points (technique n2)";
	cout <<"\n(7) Calcul du produit scalaire de deux vecteurs";
	cout <<"\n---------------";
	cout <<"\nAutre - Retour menu principal";
	cout <<"\n\nVotre choix: ";
	int choix(getint());
	if(choix==1) vec_distances();
	if(choix==2) vec_milieu();
	if(choix==3) vec_vecteur();
	if(choix==4) vec_norme();
	if(choix==5) vec_align3_1();
	if(choix==6) vec_align3_2();
	if(choix==7) vec_produit_scalaire();
}

#endif

