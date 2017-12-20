//////////////////////////////////////
//                                   //
//          MATH 2nd (M2nd)          //
//                                   //
//     (c) Nicolas DUBIEN - 2006     //
//                                   //
///////////////////////////////////////

#include <iostream>

using namespace std;


#ifndef UTILISATEUR_H
#define UTILISATEUR_H


double getdouble() {
	for(;;) {
		double valeur;
		cin >> valeur;
		if(cin.fail()){
			cin.clear();
			string inutile;
			getline(cin, inutile);
			cout <<"\nCe n'etait pas un nombre entier, reessayer : \n";
		}
		else {
			return valeur;
		}
	}
}

int getint() {
	for(;;) {
		int valeur;
		cin >> valeur;
		if(cin.fail()){
			cin.clear();
			string inutile;
			getline(cin, inutile);
			cout <<"\nCe n'etait pas un nombre entier, reessayer : \n";
		}
		else {
			return valeur;
		}
	}
}

#endif


