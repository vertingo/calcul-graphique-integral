///////////////////////////////////////
//                                   //
//          MATH 2nd (M2nd)          //
//                                   //
//     (c) Nicolas DUBIEN - 2006     //
//                                   //
///////////////////////////////////////

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

#include "convertisseur.h"
#include "utilisateur.h"
#include "utilitaires.h"

using namespace std;


#ifndef OUTILS_H
#define OUTILS_H


void out_ppcm() {
	cout <<"\n\nSoit deux nombre x et y";
	cout <<"\n\nValeur x : ";
	int x(getint());
	cout <<"\nValeur y : ";
	int y(getint());
	int pgcd(0);
	int x2(x);
	int y2(y);
	y2=y2;
	cout <<"\n\nCalcul du PGCD : \n";
	for(;pgcd==0;) {
		vector <int> pgcdoupas(trouv_pgcd(x2,y2));
		if(pgcdoupas[1]==0)  pgcd=pgcdoupas[2];
		else {
			x2=pgcdoupas[2];
			y2=pgcdoupas[1];
		}
	}
	cout <<"\n\nPPCM ( "<<x<<" ; "<<y<<" ) = PGCD ( "<<x<<" ; "<<y<<" ) * "<<x/pgcd<<" * "<<y/pgcd;
	cout <<"\nPPCM ( "<<x<<" ; "<<y<<" ) = "<<pgcd<<" * "<<(x/pgcd)*(y/pgcd);
	cout <<"\nPPCM ( "<<x<<" ; "<<y<<" ) = "<<pgcd*(x/pgcd)*(y/pgcd);
	cout <<"\n\n"<<x<<" * "<<(pgcd*(x/pgcd)*(y/pgcd))/x<<" = "<<pgcd*(x/pgcd)*(y/pgcd);
	cout <<'\n'<<y<<" * "<<(pgcd*(x/pgcd)*(y/pgcd))/y<<" = "<<pgcd*(x/pgcd)*(y/pgcd);
}

void out_fraction2() {
	cout <<"\n\nSoit la fraction : x / y";
	cout <<"\n\nValeur x : ";
	int x(getint());
	cout <<"\nValeur y : ";
	int y(getint());
	int pgcd(0);
	int x2(x);
	int y2(y);
	y2=y2;
	cout <<"\n\nCalcul du PGCD : \n";
	for(;pgcd==0;) {
		vector <int> pgcdoupas(trouv_pgcd(x2,y2));
		if(pgcdoupas[1]==0)  pgcd=pgcdoupas[2];
		else {
			x2=pgcdoupas[2];
			y2=pgcdoupas[1];
		}
	}
	cout <<"\n\n  "<<x<<" / "<<y;
	cout <<"\n= ( "<<x/pgcd<<" * "<<pgcd<<" ) / ( "<<y/pgcd<<" * "<<pgcd<<" )";
	cout <<"\n= "<<x/pgcd<<" / "<<y/pgcd;
}

void out_fraction() {
	cout <<"\n\nSoit la fraction : x / y";
	cout <<"\n\nValeur x : ";
	int x(getint());
	cout <<"\nValeur y : ";
	int y(getint());
	vector <double> poss_x(trouv_div(x));
	vector <double> poss_y(trouv_div(y));
	int pgcd(1);
	for(int i(0);i!=poss_x.size();++i) {
		for(int j(0);j!=poss_y.size();++j) {
			if(poss_x[i]==poss_y[j]&&poss_x[i]>pgcd) pgcd=poss_x[i];
		}
	}
	cout <<"\n\n  "<<x<<" / "<<y;
	cout <<"\n= ( "<<x/pgcd<<" * "<<pgcd<<" ) / ( "<<y/pgcd<<" * "<<pgcd<<" )";
	cout <<"\n= "<<x/pgcd<<" / "<<y/pgcd;
}

int premier_ou_pas(double nombre) {
	cout <<"\n\nVerifie si le nombre "<<nombre<<" est un nombre premier";
	cout <<"\n...En cours...";
	if(nombre<0) nombre=-nombre;

	//Multiple de 2?

	int possa1(nombre/2);
	double possa2(nombre/2);
	if(possa1==possa2&&nombre!=2) {
		cout <<"\n --> Accomplie";
		return 2;
		}

	//Si pas divisible par 2
	//Verifie si divisible par nombre impair

	for(double i(1);i<(nombre/2);i+=2) {
		int possb1(nombre/i);
		double possb2(nombre/i);
		if(possb1==possb2&&i!=1) {
			cout <<"\n --> Accomplie";
			return i;
		}
	}

	cout <<"\n --> Accomplie";
	return 0;
}

void out_nb_premier_ou_pas() {
	cout <<"\n\nSavoir si le nombre entier \'x\' est un nombre premier";
	cout <<"\n\nValeur x : ";
	int x(getint());
	int diviseurs(premier_ou_pas(x));
	if(diviseurs==0) cout <<"\n\n"<<x<<" est un nombre premier.";
	else cout <<"\n\n"<<x<<" n\'est pas un nombre premier.";
}

void out_nb_premier() {
	ofstream filepremiers("M2nd Nb Premiers.txt");
	cout <<"\n\nAfficher tous les nombres premiers de \'x\' a \'y\'";
	cout <<"\n\nLes reponses trouvees sauront sauvegardees\ndans le fichier \"M2nd Nb Premiers.txt\"";
	cout <<"\n\nValeur x : ";
	int x(getint());
	cout <<"\nValeur y : ";
	int y(getint());
	if(x<0) x=-x;
	if(y<0) y=-y;
	int x2(0);
	int y2(0);
	if(x>y) {
		x2=y;
		y2=x;
	} else {
		x2=x;
		y2=y;
	}
	filepremiers <<"Nombres premiers de "<<x2<<" a "<<y2<<" : \n";
	vector <int> premiers;
	for(int i(x2);i!=(y2+1);++i) {
		int diviseurs(premier_ou_pas(i));
		if(diviseurs==0) {
			cout <<'\n'<<i<<" est un nombre premier.";
			premiers.push_back(i);
			filepremiers <<"\n	- "<<i;
		}
	}
	cout <<"\n\nNombres premiers de "<<x2<<" a "<<y2<<" : ";
	for(int j(0);j!=premiers.size();++j) {
		cout <<"\n	- "<<premiers[j];
	}
}

void out_aff_carres() {
	cout <<"\n\nAfficher tous les carres parfaits compris entre \'x\' et \'y\'";
	cout <<"\n\nValeur x : ";
	int x(getint());
	cout <<"\nValeur y : ";
	int y(getint());
	if(x<0) x=-x;
	if(y<0) y=-y;
	int x2(0);
	int y2(0);
	if(x>y) {
		x2=y;
		y2=x;
	} else {
		x2=x;
		y2=y;
	}
	cout <<"\n\nCarres parfaits de "<<x2<<" a "<<y2<<" : ";
	for(double i(x2);i!=(y2+1);++i) {
		int poss1(sqrt(i));
		double poss2(sqrt(i));
		if(poss1==poss2) cout <<"\n	- "<<i;
	}
}

void out_diviseurs() {
	ofstream filediviseurs("M2nd Diviseurs.txt");
	cout <<"\n\nLes reponses trouvees sauront sauvegardees\ndans le fichier \"M2nd Diviseurs.txt\"";
	cout <<"\n\nNombre dont vous souhaitez connaitre les diviseurs : ";
	int nombre(getint());
	filediviseurs <<"Diviseurs de "<<nombre<<" : \n";
	vector <double> possibilitees(trouv_div(nombre));
	for(int i(0);i!=possibilitees.size();++i) {
		cout <<'\n'<<nombre<<" / "<<possibilitees[i]<<" = "<<nombre/possibilitees[i];
		filediviseurs <<'\n'<<nombre<<" / "<<possibilitees[i]<<" = "<<nombre/possibilitees[i];
	}
}

void out_carres() {
	cout <<"\n\nExtraire du radical les carres parfaits";
	cout <<"\nExemple : V( 8 ) = 2V( 2 )";
	cout <<"\n\nx represente le 8 dans l'exemple precedent";
	cout <<"\n\nValeur de x : ";
	int nombre(getint());
	double reduction(div_racine(nombre));
	cout <<"\n\nV( "<<nombre<<" )";
	if(reduction!=0) {
		cout <<" = V( "<<nombre/reduction<<" * "<<reduction<<" ) = ";
		if(reduction==nombre) cout <<sqrt(reduction);
		else cout <<sqrt(reduction)<<"V( "<<nombre/reduction<<" )";
	} else cout <<"\n\nAucun carre parfait n'a ete trouve !";
}

void menuoutils() {
	cout <<"\n\nAutres fonctions utiles!";
	cout <<"\n\n(1) Extraire du radical les carres parfaits";
	cout <<"\n(2) Afficher les diviseurs d'un nombre (entier)";
	cout <<"\n(3) Reduire une fraction\n    (L'ordinateur n'affiche pas son raisonnement)";
	cout <<"\n(4) Reduire une fraction\n    (L'ordinateur affiche le calcul qui lui permet de trouver le PGCD)";
	cout <<"\n(5) Afficher tous les nombres premiers de ... a ...";
	cout <<"\n(6) Afficher tous les carres parfaits compris entre ... et ...";
	cout <<"\n(7) Savoir si un nombre est un nombre premier ou pas";
	cout <<"\n(8) Convertions";
	cout <<"\n(9) Trouver le PPCM de deux nombres";
	cout <<"\n---------------";
	cout <<"\nAutre - Retour menu principal";
	cout <<"\n\nVotre choix : ";
	int choix(getint());
	if(choix==1) out_carres();
	if(choix==2) out_diviseurs();
	if(choix==3) out_fraction();
	if(choix==4) out_fraction2();
	if(choix==5) out_nb_premier();
	if(choix==6) out_aff_carres();
	if(choix==7) out_nb_premier_ou_pas();
	if(choix==8) menuconvertisseur();
	if(choix==9) out_ppcm();
}

#endif

