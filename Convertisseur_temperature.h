///////////////////////////////////////
//                                   //
//          MATH 2nd (M2nd)          //
//                                   //
//     (c) Nicolas DUBIEN - 2006     //
//                                   //
///////////////////////////////////////

#include <iostream>

#include "utilisateur.h"

using namespace std;


#ifndef CONVERTISSEUR_TEMPERATURES_H
#define CONVERTISSEUR_TEMPERATURES_H


void celsius_fahrenheit(double temperature) {
cout <<"\n\n"<<temperature<<"C = "<<temperature*1.8+32<<"F";
}
void fahrenheit_celsius(double temperature) {
cout <<"\n\n"<<temperature<<"F = "<<(temperature-32)/1.8<<"C";
}
void kelvin_celsius(double temperature) {
cout <<"\n\n"<<temperature<<"K = "<<temperature-273.15<<"C";
}
void celsius_kelvin(double temperature) {
cout <<"\n\n"<<temperature<<"C = "<<temperature+273.15<<"K";
}
void kelvin_fahrenheit(double temperature) {
cout <<"\n\n"<<temperature<<"K = "<<(temperature*1.8)-459.67<<"F";
}
void fahrenheit_kelvin(double temperature) {
cout <<"\n\n"<<temperature<<"F = "<<(temperature+459.67)/1.8<<"K";
}
void con_temperature() {
cout <<"\n\nConvertions de temperatures : ";
cout <<"\n\n1 - Celsius    ->     kelvin";
cout <<"\n2 - Celsius    -> Fahrenheit";
cout <<"\n3 - kelvin     ->    Celsius";
cout <<"\n4 - kelvin     -> Fahrenheit";
cout <<"\n5 - Fahrenheit ->    Celsius";
cout <<"\n6 - Fahrenheit ->     kelvin";
cout <<"\n\nVotre choix : ";
int choix(getint());
cout <<"\n\nTemperature initiale = ";
double temperature(getdouble());
if(choix==1) celsius_kelvin(temperature);
if(choix==2) celsius_fahrenheit(temperature);
if(choix==3) kelvin_celsius(temperature);
if(choix==4) kelvin_fahrenheit(temperature);
if(choix==5) fahrenheit_celsius(temperature);
if(choix==6) fahrenheit_kelvin(temperature);
}

#endif

