///////////////////////////////////////
//                                   //
//          MATH 2nd (M2nd)          //
//                                   //
//     (c) Nicolas DUBIEN - 2006     //
//                                   //
///////////////////////////////////////

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;


#ifndef UTILITAIRES_H
#define UTILITAIRES_H


vector <double> trouv_div(double nombre) {
	cout <<"\n\nRecherche des diviseurs du nombre "<<nombre;
	cout <<"\n...En cours...";
	vector <double> div_poss;
	if(nombre<0) nombre=-nombre;

	int ajout(1);

	//L'ordinateur regarde s'il s'agit d'un nombre pair

	int possa(nombre/2);
	double possb(nombre/2);
	if(possa!=possb) ajout=2;

	//Si le nombre est impair l'ordinateur ne regardera pas
	//si le nombre se divise par un nombre pair (car s'est impossible),
	//ainsi il passe 2 fois moins de temps qu'avec un nombre pair,
	//car il ne recherche pas avec les nombres pairs

	for(double i(1);i<(nombre/2)+1;i+=ajout) {
		int poss1(nombre/i);
		double poss2(nombre/i);
		if(poss1==poss2) div_poss.push_back(i);
	}
	if(nombre!=0) div_poss.push_back(nombre);
	cout <<"\n --> Accomplie";
	return div_poss;
}

int div_racine(int nombre) {
	cout <<"\n\n--> Extraction des carres parfaits du radical <--";
	vector <double> possibilitees(trouv_div(nombre));
	cout <<"\n\nRecherche le diviseurs le plus important,\nqui est un carre parfait";
	cout <<"\n...En cours...";
	int max_div(0);
	for(int i(0);i!=possibilitees.size();++i) {
		int poss1(sqrt(possibilitees[i]));
		double poss2(sqrt(possibilitees[i]));
		if(poss1==poss2) max_div=possibilitees[i];
	}
	cout <<"\n --> Accomplie";
	return max_div;
}

vector <int> trouv_pgcd(int x,int y) {
	vector <int> pgcd;
	int x2(0);
	int y2(0);
	if(x<y) {
		x2=y;
		y2=x;
	} else {
		x2=x;
		y2=y;
	}
	int quotient(x2/y2);
	int reste(x2-quotient*y2);
	pgcd.push_back(quotient);
	pgcd.push_back(reste);
	pgcd.push_back(y2);
	cout <<"\n"<<x2<<" / "<<y2<<" -> Q : "<<quotient<<", R : "<<reste;
	return pgcd;
}

#endif

