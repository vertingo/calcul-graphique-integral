///////////////////////////////////////
//                                   //
//          MATH 2nd (M2nd)          //
//                                   //
//     (c) Nicolas DUBIEN - 2006     //
//                                   //
///////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>

#include "convertisseur_temperature.h"
#include "utilisateur.h"

using namespace std;


#ifndef CONVERTISSEUR_H
#define CONVERTISSEUR_H


void con_convert(vector <long double> conv01,vector <string> conv02) {
cout <<"\n\nUnites : \n";
for(int i(0);i!=conv02.size();++i) {
	if((i+1)<10) cout <<"\n "<<i+1<<" - "<<conv02[i];
	else cout <<'\n'<<i+1<<" - "<<conv02[i];
	if(conv02.size()==2) cout <<" -> "<<conv02[1-i];
}
cout <<"\n\nUnite du nombre de depart : ";
int unit1(getint());
int unit2(0);
if(conv02.size()==2) unit2=3-unit1;
else {
	cout <<"\nUnite du nombre final : ";
	unit2=getint();
}
cout <<"\n\nNombre a convertir : ";
double convert(getdouble());
if((unit1>0&&unit1<=conv01.size())&&(unit2>0&&unit2<=conv01.size())) {

	//Si la valeur initiale est superieure a 1
	//et que le mot necessite une orthographe speciale au pluriel

	if((conv02[unit1-1]=="annee lumiere"||conv02[unit1-1]=="unite astronomique")&&convert>1) {
		if(conv02[unit1-1]=="annee lumiere") cout <<"\n\n"<<convert<<" annees lumiere = ";
		else cout <<"\n\n"<<convert<<" unites astronomiques = ";
	}
	else {
		if(convert<=1) cout <<"\n\n"<<convert<<" "<<conv02[unit1-1]<<" = ";
		else cout <<"\n\n"<<convert<<" "<<conv02[unit1-1]<<"s = ";
	}

	//Si la valeur finale est superieure a 1
	//et que le mot necessite une orthographe speciale au pluriel

	if((conv02[unit2-1]=="annee lumiere"||conv02[unit2-1]=="unite astronomique")&&((convert*conv01[unit1-1])/conv01[unit2-1])>1) {
		if(conv02[unit2-1]=="annee lumiere") cout <<(convert*conv01[unit1-1])/conv01[unit2-1]<<" annees lumiere";
		else cout <<(convert*conv01[unit1-1])/conv01[unit2-1]<<" unites astronomiques";
	}
	else {
		if(((convert*conv01[unit1-1])/conv01[unit2-1])<=1) cout <<(convert*conv01[unit1-1])/conv01[unit2-1]<<" "<<conv02[unit2-1];
		else cout <<(convert*conv01[unit1-1])/conv01[unit2-1]<<" "<<conv02[unit2-1]<<"s";
	}

}
}

void con_temps() {
vector <long double> conv01;

//Temps mis en secondes

conv01.push_back(1);
conv01.push_back(60);
conv01.push_back(3600);
conv01.push_back(86400);
conv01.push_back(604800);
conv01.push_back(31556925.22);

vector <string> conv02;

conv02.push_back("seconde");
conv02.push_back("minute");
conv02.push_back("heure");
conv02.push_back("jour");
conv02.push_back("semaine");
conv02.push_back("annee");

/*Demande de l'avis de l'utilisateur
et affichage de la reponse
 |
 |
 +--> */ con_convert(conv01,conv02);
}

void con_longueur() {
vector <long double> conv01;

//Longueurs mises en gigametres

conv01.push_back(0.000000000000000000000001);
conv01.push_back(0.000000000000000000001);
conv01.push_back(0.000000000000000001);
conv01.push_back(0.000000000000001);
conv01.push_back(0.000000000001);
conv01.push_back(0.00000000001);
conv01.push_back(0.0000000000254);
conv01.push_back(0.0000000001);
conv01.push_back(0.0000000003048);
conv01.push_back(0.000000001);
conv01.push_back(0.000001);
conv01.push_back(0.000001609344);
conv01.push_back(0.000004828032);
conv01.push_back(0.001);
conv01.push_back(1);
conv01.push_back(150);
conv01.push_back(1000);
conv01.push_back(9460000);

vector <string> conv02;

conv02.push_back("femtometre");
conv02.push_back("picometre");
conv02.push_back("nanometre");
conv02.push_back("micrometre");
conv02.push_back("millimetre");
conv02.push_back("centimetre");
conv02.push_back("pouce");
conv02.push_back("decimetre");
conv02.push_back("pied");
conv02.push_back("metre");
conv02.push_back("kilometre");
conv02.push_back("mille");
conv02.push_back("lieue");
conv02.push_back("megametre");
conv02.push_back("gigametre");
conv02.push_back("unite astronomique");
conv02.push_back("terametre");
conv02.push_back("annee lumiere");

/*Demande de l'avis de l'utilisateur
et affichage de la reponse
 |
 |
 +--> */ con_convert(conv01,conv02);

}

void con_mesures() {
vector <long double> conv01;

//Longueurs mises en gigametres

conv01.push_back(3.14159265358979323846/180);
conv01.push_back(1);

vector <string> conv02;

conv02.push_back("degre");
conv02.push_back("radian");

/*Demande de l'avis de l'utilisateur
et affichage de la reponse
 |
 |
 +--> */ con_convert(conv01,conv02);

}

void menuconvertisseur() {
	for(int choix(1);(choix>0&&choix<5);) {
		cout <<"\n\nMath 2nd - Outils utiles - Convertisseur";
		cout <<"\n\n1 - De longueurs";
		cout <<"\n2 - De temperatures";
		cout <<"\n3 - De temps";
		cout <<"\n4 - De mesures d\'angle";
		cout <<"\n---------------";
		cout <<"\nAutre - Retour menu principal";
		cout <<"\n\nVotre choix : ";
		choix=getint();
		if(choix==1) con_longueur();
		if(choix==2) con_temperature();
		if(choix==3) con_temps();
		if(choix==4) con_mesures();
	}
}

#endif

