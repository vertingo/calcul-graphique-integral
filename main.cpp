/************************************************************************/
/*Régression linéaire méthode des moindres carrés version 1.1c avec menu*/
/************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <sdl/sdl.h>
#include <string.h> // Penser à inclure string.h pour strchr()
#include <iostream>
#include <vector>
#include <locale.h>
#include "headers/mini_rsa.h"
#include "headers/vecteurs.h"
#include "headers/utilisateur.h"
#include "headers/outils.h"

#define COUNT(t) (sizeof(t)/sizeof(t[0]))

using namespace std ;

#define MAX 100 /*définition de la taille maximum des tableaux donc du nombre d'element Xi et Yi*/
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

/***************************/
/*Déclaration des fonctions*/
/***************************/

void entete();
int nbrelement();
void ligne(int nbr);
void ligne2(int deb,int nbr,int fin);
void titre(char titre[]);
int Factorielle (int nombre);
float somme(float tab[],int N);
float moyenne(float somme,int N);
void produittab(float tab1[],float tab2[],float tab_produit[],int N);
float pente(float SommeProduitXiYi,float MoyenneXi,float MoyenneYi,float SommeCarreXiMoinMoyenneXi,int N);
float ordonee(float MoyenneXi,float MoyenneYi,float a);
void ecart_a_moyenne(float tab[],float tab_ecart_a_moyenne[],float Moyenne,int N);
void affich_tab(float tab[],float tab1[],float tab2[],float tab3[],float tab4[],float tab5[],int N);
double corr(float SommeCarreXiMoinMoyenneXi,float SommeCarreYiMoinMoyenneYi,float a);
void affichage(float tab[]);
void aff_equation(float tab[]);
void regression(float Xi[],float Yi[],int N,float result[],float ProduitXiYi[],float carre_ecart_a_moyenne_Xi[],float carre_ecart_a_moyenne_Yi[]);
void fichier(float tab[],float tab1[],float tab2[],float tab3[],float tab4[],float tab5[],int N);
void Calcul_Integral();
void bernouilli();

SDL_Surface * screen;
Uint32 white, black, couleur[100];

/*********************************/
/*         Les Fonctions         */
/*********************************/


/*Fonction d'affichage de l'en-tête avec nom et version du programme etc...*/

void entete()
{
	printf("************************************************************************\n");
    printf("* R%cgression lin%caire par la m%cthodes des moindres carr%cs Version 1.1c *\n",130,130,130,130);
	printf("*                    R%calisation: LEMAGICIEN.                          *\n",130);
	printf("************************************************************************\n");
	printf("* Nouveaut%cs par rapport %c la version 1.1b:                            *\n",130,133);
	printf("*    ==> Un menu                                                       *\n",130,130);
	printf("************************************************************************\n\n");
}

int Factorielle(int nombre)
{
    int i;
    int resultat = 1;

    /* Nous commencons la boucle qu'a partir de 2 car 0! == 1 et 1! == 1, 1 etant la valeur par initialisation.
    Nous avons donc seulement besoins de multiplier si le nombre rentrer par l'utilisateur est >= 2 */
    for (i=2;i<=nombre;i++)
        resultat *= i;

    return resultat;
}


/*Fonction d'entrée du nombre d'elements*/

int nbrelement()
{
	float n;
	int N;

	printf("Entrez le nombre de mesures N (entre 2 et %d):",MAX);
	scanf("%f",&n);

	N=int(n);

	while((N<2)||(N>(MAX+1))||(n!=N))  /*verification que "n" est bien entier*/
    {
		if(n!=N)
        {
			while (n!=N)
			{
			printf("\nLa valeur de N doit %ctre enti%cre",136,138);
	        printf("\nEntrez une nouvelle valeur:");
	        scanf("%f",&n);
			N=n;
	        };
	    };

		if((N<2)||(N>(MAX+1)))
		{
		printf("\nLa valeur doit %ctre comprise entre 2 et %d:",136,MAX);
		printf("\nEntrez une nouvelle valeur:");
		scanf("%f",&n);
		N=n;
		};

	};
	return(N);
}


/*Fonction de calcul de somme d'element d'un tableau*/

float somme(float tab[],int N)
{
	float somme=0;
	int i=1;

	while (i<(N+1))
	{
	 somme=((tab[i])+(somme));i++;
   	};

	return(somme);
}

/*Fonction de calcul de moyenne d'element d'un tableau*/

float moyenne(float somme,int N)
{
	float moyenne;

	moyenne=((somme)/(float)N);

	return(moyenne);
}

/*Fonction de calcul du produit d'element de deux tableau ligne par ligne*/

void produittab(float tab1[],float tab2[],float tab_produit[],int N)
{
	int i=1;

	while(i<(N+1))
	{
		tab_produit[i]=(tab1[i]*tab2[i]);i++;
	};
}

/*Fonction de calcul de la pente "a" de la droite*/

float pente(float SommeProduitXiYi,float MoyenneXi,float MoyenneYi,float SommeCarreXiMoinMoyenneXi,int N)
{
	float a;

	a=((SommeProduitXiYi)-(N*MoyenneXi*MoyenneYi))/(SommeCarreXiMoinMoyenneXi);

	return (a);
}

/*Fonction de calcul de l'ordonee a l'orrigine "b"*/

float ordonee(float MoyenneXi,float MoyenneYi,float a)
{
	float b;

	b=(MoyenneYi-(a*MoyenneXi));
	return (b);
}

/*Fonction de calcul des écarts à la moyenne*/

void ecart_a_moyenne(float tab[],float tab_ecart_a_moyenne[],float Moyenne,int N)
{
	int i=1;

	while(i<(N+1))
	{
	tab_ecart_a_moyenne[i]=(tab[i]-Moyenne);i++;
	};
}

/*Calcul du coefficient de corrélation "r"*/

double corr(float SommeCarreXiMoinMoyenneXi,float SommeCarreYiMoinMoyenneYi,float a)
{
	double r,q,rCarre;

	/*Calcul de r*/

	rCarre=(((a*a)*(SommeCarreXiMoinMoyenneXi))/SommeCarreYiMoinMoyenneYi);

	/*Le signe de r est le meme que a*/

	if(a>=0.0)
	{
	    q=1;
	}
	else
	{
	    q=-1;
	};

	r=(sqrt(rCarre))*q;
	return (r);

}

/*************************************/
/*    Fonction d'affichage divers    */
/*************************************/


/*Fonction d'affichage des résultats*/

void affichage(float tab[])
{
	printf("\n%c",201);
	ligne(12);/*boucle d'affichage double ligne*/
	printf("%c\n",187);

    printf("%c R%csultats: %c\n",186,130,186);

	printf("%c",200);
	ligne(12);/*boucle d'affichage double ligne*/
	printf("%c",188);

	printf("\n\nSomme Xi = %f",tab[0]);
	printf("\nSomme Yi = %f\n",tab[1]);


	printf("\nMoyenne des Xi = %f",tab[2]);
	printf("\nMoyenne des Yi = %f\n",tab[3]);

	printf("\nSomme des (Xi * Yi) = %f",tab[4]);

	printf("\n\nPente de la droite:=========> a = %f",tab[7]);

	printf("\nOrdonn%ce %c l'origine:=======> b = %f",130,133,tab[8]);

	printf("\nCoefficient de corr%clation:=> r = %lf",130,tab[9]);

	/*Fonction d'affichage de l'equation*/

	aff_equation(tab);

	printf("\n");

	getchar();
}

/*Fonction d'affichage simple de l'équation*/

void aff_equation(float tab[])
{
	printf("\n\nL'%cquation de la droite est:\n\n",130);
	printf("     ");
	ligne2(201,27,187);
	printf("\n     %c Y = %f X + %f %c\n",186,tab[7],tab[8],186);
	printf("     ");
	ligne2(200,27,188);
	printf("\n");
}

/*Fonction d'affichage des doubles lignes*/

void ligne(int nbr)
{
	int j=0;

	while(j<nbr)
	{
	    printf("%c",205);j++;
    };
}

/*Fonction d'affichage des doubles lignes2*/

void ligne2(int deb,int nbr,int fin)
{
	int j=0;

	printf("%c",deb);

	while(j<nbr)
	{
	    printf("%c",205);j++;
	}

	printf("%c",fin);
}

/*Fonction d'affichage des titres*/

void titre(char titre[])
{
	int nbr,j=0;

	nbr = strlen(titre)+2;

	printf("\n");
	ligne2(201,nbr,187);
	printf("\n%c %s %c",186,titre,186);
	printf("\n");
	ligne2(200,nbr,188);
	printf("\n\n");
}

/*Fonction d'affichage des donnée sous forme de tableau*/

void affich_tab(float tab[],float tab1[],float tab2[],float tab3[],float tab4[],float tab5[],int N)
{
	int i=1,j=0;

	printf("\n\n%c",201);

	ligne(22);/*boucle d affichage double ligne*/

	printf("%c",187);
	printf("\n%c Tableau des donn%ces: %c",186,130,186);
	printf("\n%c",200);

	ligne(22);/*boucle d affichage double ligne*/

	printf("%c",188);

	printf("\n\n%c",201);

	ligne(7);/*boucle d affichage double ligne*/

	printf("%c",203);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",203);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",203);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",203);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",203);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",187);

	printf("\n%c   N   %c      Xi     %c      Yi     %c     XiYi    %c  (Xi-<X>)%c  %c  (Yi-<Y>)%c  %c",186,186,186,186,186,253,186,253,186);
	printf("\n%c",204);
	ligne(7);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",185);

    /*Boucle d affichage des données proprement dites*/

	while(i<N+1)
	{
		printf("\n%c %3.d   %c%12.4e %c%12.4e %c%12.4e %c%12.4e %c%12.4e %c",186,i,186,tab1[i],186,tab2[i],186,tab3[i],186,tab4[i],186,tab5[i],186);i++;
	}

	printf("\n%c",204);
	ligne(7);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",185);

	printf("\n%c Somme %c%12.4e %c%12.4e %c%12.4e %c%12.4e %c%12.4e %c",186,186,tab[0],186,tab[1],186,tab[4],186,tab[5],186,tab[6],186);

	printf("\n%c",204);
	ligne(7);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",206);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",202);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",202);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",188);

	printf("\n%cMoyenne%c%12.4e %c%12.4e %c",186,186,tab[2],186,tab[3],186);

	printf("\n%c",200);
	ligne(7);/*boucle d affichage double ligne*/
	printf("%c",202);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",202);
	ligne(13);/*boucle d affichage double ligne*/
	printf("%c",188);

	printf("\n");
}

/*Fonction de Saufgarde dans un fichier text*/

void fichier(float tab[],float tab1[],float tab2[],float tab3[],float tab4[],float tab5[],int N)
{
	FILE *sortie1;
	char car,filename[20];
	int i=1;

	printf("\nVoulez-vous enregistrer les resultats dans un fichier (o/n)?");
	scanf("%s",&car);

	if(car =='o')
	{
	 /* Entree du nom du fichier*/
		 /* il est cree si il n'existe pas */

		printf("\n\nTapez un nom de fichier:");
		scanf("%s",filename);

		printf("\nOuverture du fichier: %s",filename);

	/*Ouvreture du fichier */

		 sortie1  = fopen (filename, "a");

	 /* Test d ouvreture */
		 if(sortie1 == NULL)
         {
		   /* fopen a echoue */
		  printf ("\nErreur a l'ouverture du fichier: %s.",filename);
		  printf ("\nFin anormale!!!");
		  exit(4);
	     }

     /* Si tout va bien, ecriture dans le fichier */

	fprintf(sortie1,"\n\n************************");
    fprintf(sortie1,"\n* Tableau des données: *");
	fprintf(sortie1,"\n************************\n\n");
	fprintf(sortie1,"\n************************************************************************************");
	fprintf(sortie1,"\n*   N   *       Xi     *       Yi     *      XiYi    *   (Xi-<X>)²  *   (Yi-<Y>)²  *");
	fprintf(sortie1,"\n************************************************************************************");

	while(i<N+1)
	{
		fprintf(sortie1,"\n* %3.d   * %12.4e * %12.4e * %12.4e * %12.4e * %12.4e *",i,tab1[i],tab2[i],tab3[i],tab4[i],tab5[i]);i++;
	}

	fprintf(sortie1,"\n************************************************************************************");
	fprintf(sortie1,"\n* Somme * %12.4e * %12.4e * %12.4e * %12.4e * %12.4e *",tab[0],tab[1],tab[2],tab[3],tab[4]);
	fprintf(sortie1,"\n************************************************************************************");
	fprintf(sortie1,"\n*Moyenne* %12.4e * %12.4e *",tab[2],tab[3]);
	fprintf(sortie1,"\n***************************************");

	fprintf(sortie1,"\n\n");
	fprintf(sortie1,"*************\n");
    fprintf(sortie1,"* Résultats:*\n");
	fprintf(sortie1,"*************\n\n");

	fprintf(sortie1,"\nSomme Xi = %f",tab[0]);
	fprintf(sortie1,"\nSomme Yi = %f\n",tab[1]);

	fprintf(sortie1,"\nMoyenne des Xi = %f",tab[2]);
	fprintf(sortie1,"\nMoyenne des Yi = %f\n",tab[3]);

	fprintf(sortie1,"\nSomme des (Xi * Yi) = %f",tab[4]);

	fprintf(sortie1,"\n\nPente de la droite:=========> a = %f",tab[7]);

	fprintf(sortie1,"\nOrdonnée %c l'origine:=======> b = %f",133,tab[8]);

	fprintf(sortie1,"\nCoefficient de corrélation:=> r = %lf",tab[9]);

	fprintf(sortie1,"\n\nL'équation de la droite est:");
	fprintf(sortie1,"\n\n   *****************************");
	fprintf(sortie1,"\n   * Y = %f X + %f *",tab[7],tab[8]);
	fprintf(sortie1,"\n   *****************************");
	fprintf(sortie1,"\n\n");

  /* fermeture des fichiers */

	fclose (sortie1);

	printf ("\nEcriture termin%ce...\n\n",130);

}
	;getchar();

}

/*Fonction de calcul de la DMC*/

void regression(float Xi[],float Yi[],int N,float result[],float ProduitXiYi[],float carre_ecart_a_moyenne_Xi[],float carre_ecart_a_moyenne_Yi[])
{
	float SommeXi;
	float SommeYi;
	float MoyenneXi;
	float MoyenneYi;
	float SommeProduitXiYi;
	float SommeCarreXiMoinMoyenneXi;
	float SommeCarreYiMoinMoyenneYi;
	float a;
	float b;
   	double r;
	float tab_ecart_a_moyenne[MAX];
	float ecart_a_moyenne_Xi[MAX];
	float ecart_a_moyenne_Yi[MAX];
	int i=1;

   /*Calcul de la somme des Xi et Yi*/

		SommeXi= somme(Xi,N);
   		SommeYi= somme(Yi,N);

   /*Calcul des moyennes des Xi et Yi*/

		MoyenneXi = moyenne(SommeXi,N);
		MoyenneYi = moyenne(SommeYi,N);

   /*Calcul de de la pente "a"de la droite et de l'ordonee à l'origine "b" */

   /*Somme des Xi*Yi*/

		produittab(Xi,Yi,ProduitXiYi,N);
		SommeProduitXiYi = somme(ProduitXiYi,N);

	/*calcul des (Xi- MoyenneXi)² et (Yi- MoyenneYi)² */

	ecart_a_moyenne(Xi,tab_ecart_a_moyenne,MoyenneXi,N);

	i=1;
	while(i<(N+1))
	{
		ecart_a_moyenne_Xi[i] = tab_ecart_a_moyenne[i];
		carre_ecart_a_moyenne_Xi[i] = ((ecart_a_moyenne_Xi[i])*(ecart_a_moyenne_Xi[i]));i++;
	};

	ecart_a_moyenne(Yi,tab_ecart_a_moyenne,MoyenneYi,N);

	i=1;
	while(i<(N+1))
	{
		ecart_a_moyenne_Yi[i] = tab_ecart_a_moyenne[i];
		carre_ecart_a_moyenne_Yi[i] = ((ecart_a_moyenne_Yi[i])*(ecart_a_moyenne_Yi[i]));i++;
	};

	/*Somme des (Xi- MoyenneXi)²*/

	SommeCarreXiMoinMoyenneXi = somme(carre_ecart_a_moyenne_Xi,N);
    SommeCarreYiMoinMoyenneYi = somme(carre_ecart_a_moyenne_Yi,N);

	/*Appel de la fonction de calcul de la pente "a" de la droite*/

	a=pente(SommeProduitXiYi,MoyenneXi,MoyenneYi,SommeCarreXiMoinMoyenneXi,N);

	/*Appel de la fonction de calcul de l'ordonee a l'orrigine "b"*/

	b=ordonee(MoyenneXi,MoyenneYi,a);

    /*Calcul du coefficient de corrélation "r"*/

	r=corr(SommeCarreXiMoinMoyenneXi,SommeCarreYiMoinMoyenneYi,a);

    /*Stockage des résultats dans une tableau de varialbes*/

	result[0]=SommeXi;
	result[1]=SommeYi;
	result[2]=MoyenneXi;
	result[3]=MoyenneYi;
	result[4]=SommeProduitXiYi;
	result[5]=SommeCarreXiMoinMoyenneXi;
	result[6]=SommeCarreYiMoinMoyenneYi;
	result[7]=a;
	result[8]=b;
	result[9]=r;

}

void bernouilli()
{
     int n, k;
     double e, p, q, r, t, x, y, z;

     printf("Entrez la valeur de k entier non nul positif\n");
     scanf("%d", &k);
     printf("Entrez le nombre d'essais n entier non nul positif\n");
     scanf("%d", &n);

     x = Factorielle(n);
     y = Factorielle(k);
     z = Factorielle(n-k);

     r = x/(y*z);

     printf("La combinaison n de k est: %lf\n", r);

     x = n-1;
     y = k-1;
     z = x-y;
     x = Factorielle(x);
     y = Factorielle(y);
     z = Factorielle(z);

     e = x/(y*z);
     e = e/x;
     p = pow(e, k);

     printf("La probabilit%c de succ%cs k de n est: %lf\n",130,138,p);

     x = n-k;
     y = 1-p;
     q = pow(y, x);

     r = r*p*q;
     printf("Le r%csultat de la loi binomiale est: %lf\n",130,r);
     e = n*p;
     printf("L'esp%crance est de: %lf\n",130,e);
     t = sqrt(e*q);
     printf("L'%ccart type est de: %lf\n",130,t);

     x = exp(-e);
     y = pow (e,k);
     z = x*y;
     k = Factorielle(k);
     x = z/k;
     printf("La loi de poisson est: %g\n", x);
}

int pgcd(int a1, int b1)
    {
    int a;
    int b;

    if(a1<b1){
        a = b1;
        b = a1;
    }
    else{
        a = a1;
        b = b1;
    }

    if(b == 0)
        return a;

    int reste=1;

    while(reste != 0){
        int q=0;
        while((b*q)<a){
        q++;
        }
        if((b*q)!=a)
        q--;
        reste = a - (q*b);
        a = b;
        b = reste;
    }


    return a;
    }

void extgcd(int m,int n)
{
   // Both arrays ma and na are arrays of 3 integers such that
	// ma[0] = m ma[1] + n ma[2] and na[0] = m na[1] + n na[2]
	int ma[3] = {m, 1, 0};
	int na[3] = {n, 0, 1};

	int ta[3];		// Temporary variable
	int i;			// Loop index
	int q;			// Quotient
	int r;			// Rest

	// Exchange ma and na if m < n
	if(m < n)
	{
	    ta[0]=na[0];
	    ta[1]=na[1];
	    ta[2]=na[2];

	    na[0] = ma[0];
	    na[1] = ma[1];
	    na[2] = ma[2];

	    ma[0] = ta[0];
	    ma[1] = ta[1];
	    ma[2] = ta[2];
	}

	if(pgcd(m,n)==1)
	{
		printf("M et N premiers entre-eux on aura donc une %cquivalence de la forme: %i.u + %i.v = 1!\nCalculons d%csormais les coefficients de b%czouts:\n",130,m,n,130,130);
	}
	else
	{
		printf("M et N ne sont pas premiers entre-eux on aura donc une %cquivalence de la forme: %i.u +%i.v = 1.k avec k appartenant %c \nl'ensemble des entiers naturels except%c:1!\n",130,m,n,133,130);
	}

	//Divisions euclidiennes successives à programmer!

		while (na[0] > 0)
		{
			q = ma[0] / na[0];	// Quotient
				for (i = 0; i < 3; i++)
				{
					r = ma[i] - q * na[i];
						ma[i] = na[i];
						na[i] = r;
                }
        }


	printf("Le r%csultat nous am%cne donc %c la relation d'%cquivalence suivante tel que u et v = (%i,%i) soit %i=%i.%i+%i.%i",130,138,133,130,ma[1],ma[2],ma[0],m,ma[1],n,ma[2]);
}

void bezout()
{
    int a, b;

        printf("Entrez un entier a: \n");
        scanf("%i",&a);
        printf("Entrez un entier b: \n");
        scanf("%i",&b);

        extgcd(a,b);
}

double poisson(int x,int y)
{
    double fact_x,puis;

        fact_x=Factorielle(x);
        puis=pow(y,x);

     return (puis*exp(-y))/(fact_x);
}

double f(double x,double a,double b,int choix_f)
{

    if(choix_f==1)
    {
     return a*x+b;
    }
    else if(choix_f==2)
    {
     return a*x*x+b;
    }
    else if(choix_f==3)
    {
     return a*x*x*x+b;
    }
    else if(choix_f==4)
    {
     return 1/(a*x+b);
    }
    else if(choix_f==5)
    {
     return log(a*x+b);
    }
    else if(choix_f==6)
    {
     return sin(a*x+b);
    }
    else if(choix_f==7)
    {
     return cos(a*x+b);
    }
    else if(choix_f==8)
    {
     return poisson(x,a);
    }
    else if(choix_f==9)
    {
     return a*exp(-b*x);
    }

}

double f_second_degree(double x,double a,double b,double c,int choix_f)
{
    if(choix_f==1)
    {
     return a*x*x+b*x+c;
    }
}

long int a_parmi_b(long int a, long int b)
{
 long int res;
 res=Factorielle(b)/(Factorielle(a)*Factorielle(b-a));
 return res;
}

double f_binome_de_newton(int x,int n,int a,int b,int choix_f)
{
    if(choix_f==1)
    {
        return a_parmi_b(x,n)*pow(b,x)*pow(a,(n-x));
    }
    else if(choix_f==2)
    {
        return (a+b)^x;
    }
}

double f_derive(double x,double a,double b,int choix_f)
{

    if(choix_f==1)
    {
     return a;
    }
    else if(choix_f==2)
    {
     return a*2*x;
    }
    else if(choix_f==3)
    {
     return a*x*x;
    }
    else if(choix_f==4)
    {
     return a/(a*x+b)*(a*x+b);
    }
    else if(choix_f==5)
    {
     return  a/(a*x+b);
    }
    else if(choix_f==6)
    {
     return a*cos(a*x+b);
    }
    else if(choix_f==7)
    {
     return -a*sin(a*x+b);
    }
    else if(choix_f==8)
    {
     return a*2*x+b;
    }
}

void waitkey()            // attend qu'on appuie sur ESC
{
    SDL_Event event;
    while(1)            // boucle
    {
        while(SDL_PollEvent(&event))        // aquisition d'evenement
        {
            if(event.type==SDL_KEYDOWN)  // on appuie sur une touche ?
            {
                if(event.key.keysym.sym==SDLK_ESCAPE) return;  // c'est "ESC" ?
            }
        }
        SDL_Delay(1);
    }
}

void pause(void)
{
 SDL_Event evenement;
 do SDL_WaitEvent(&evenement);
 while(evenement.type != SDL_QUIT && evenement.type != SDL_KEYDOWN);
}

void putpixel(int xe, int ye, Uint32 c)
{
 Uint32 * numerocase;
 numerocase= (Uint32 *)(screen->pixels)+xe+ye*screen->w; *numerocase=c;
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


void ShowFoncion(SDL_Surface* screen,Uint32 couleur,double (*fonc)(double,double,double,int),double minX,double maxX,double minY,double maxY,double a,double b,int choix_f)
{
    int i;
    int lastx = 0;
    int lasty = 0;
    int x,y;
    double resfonc;

    for(i=0;i<XRES;i++)
    {
        x = i;
        resfonc = fonc(Ecr_to_ReX(i,minX,maxX),a,b,choix_f);
        y = Re_to_EcrY(resfonc,minY,maxY);

        if(i!=0)
            Line(screen,x,y,lastx,lasty,couleur);
        lastx = x;
        lasty = y;
    }
}

void ShowFoncionSecondDegree(SDL_Surface* screen,Uint32 couleur,double (*fonc)(double,double,double,double,int),double minX,double maxX,double minY,double maxY,double a,double b,double c,int choix_f)
{
    int i;
    int lastx = 0;
    int lasty = 0;
    int x,y;
    double resfonc;

    for(i=0;i<XRES;i++)
    {
        x = i;
        resfonc = fonc(Ecr_to_ReX(i,minX,maxX),a,b,c,choix_f);
        y = Re_to_EcrY(resfonc,minY,maxY);

        if(i!=0)
            Line(screen,x,y,lastx,lasty,couleur);
        lastx = x;
        lasty = y;
    }
}

void ShowFoncionBinomeDeNewton(SDL_Surface* screen,Uint32 couleur,double (*fonc)(int,int,int,int,int),double minX,double maxX,double minY,double maxY,double a,double b,double n,int choix_f)
{
    int i;
    int lastx = 0;
    int lasty = 0;
    int x,y;
    double resfonc;

    for(i=0;i<XRES;i++)
    {
        x = i;
        resfonc = fonc(Ecr_to_ReX(i,minX,maxX),n,a,b,choix_f);
        y = Re_to_EcrY(resfonc,minY,maxY);

        if(i!=0)
            Line(screen,x,y,lastx,lasty,couleur);
        lastx = x;
        lasty = y;
    }
}

void ShowTengente(SDL_Surface* screen,Uint32 couleur,double (*fonc)(double,double,double,int),double minX,double maxX,double minY,double maxY,double a,double b,double x1,int choix_f)
{
    int i;
    int lastx = 0;
    int lasty = 0;
    int x,y;
    double resfonc;

    for(i=0;i<XRES;i++)
    {
        x = i;
        resfonc = fonc(Ecr_to_ReX(i,minX,maxX)-x1,a,b,1);
        y = Re_to_EcrY(resfonc,minY,maxY);

        if(i!=0)
            Line(screen,x,y,lastx,lasty,couleur);
        lastx = x;
        lasty = y;
    }
}

void ShowAxis(SDL_Surface* screen,double minX,double maxX,double minY,double maxY,double a,double b,double c,int choix_f,bool integral,bool derive,bool poly,bool binome,bool binome2)
{
    int centreX = Re_to_EcrX(0.0,minX,maxX);
    int centreY = Re_to_EcrY(0.0,minY,maxY);
    Line(screen,centreX,0,centreX,YRES-1,0xFFFFFF);  // axe vertical
    Line(screen,0,centreY,XRES-1,centreY,0xFFFFFF);  // axe horizontal
    Uint32 rouge = SDL_MapRGB(screen->format, 255, 0, 0);
    Uint32 bleu = SDL_MapRGB(screen->format, 0, 0, 255);
    Uint32 bleu_ciel = SDL_MapRGB(screen->format, 0, 140, 255);

    if(binome2==true)
    {
        Line(screen,(XRES/(maxX+1))*maxX,0,(XRES/(maxX+1))*maxX,YRES-1,rouge);
        Line(screen,(XRES/(maxX+1))*(maxX-1),0,(XRES/(maxX+1))*(maxX-1),YRES-1,rouge);
    }
    else
    {
        Line(screen,(XRES/(maxX+1))*maxX,0,(XRES/(maxX+1))*maxX,YRES-1,rouge);
        Line(screen,(XRES/(maxX+1)),0,(XRES/(maxX+1)),YRES-1,rouge);
    }

    if(poly==true)
    {
        if(integral==true)
        {
        int xmax,xpas,y;
        double resfonc2;
        xmax=(XRES/(maxX+1))*maxX;
        xpas=(XRES/(maxX+1));

            for(int i=xpas;i<xmax;i++)
            {
                if(derive==true)
                {
                resfonc2 = f_derive(Ecr_to_ReX(i,minX,maxX),a,b,8);
                }
                else
                {
                resfonc2 = f_second_degree(Ecr_to_ReX(i,minX,maxX),a,b,c,1);
                }

            y = Re_to_EcrY(resfonc2,minY,maxY);
            Line(screen,i,y,i,centreY,bleu_ciel);
            }
        }
    }
    else
    {
        if(integral==true)
        {
        int xmax,xpas,y;
        double resfonc2;
        xmax=(XRES/(maxX+1))*maxX;

        if(binome2)
        {
            xpas=(XRES/(maxX+1))*(maxX-1);
        }
        else
        {
            xpas=(XRES/(maxX+1));
        }

            for(int i=xpas;i<xmax;i++)
            {
                if(derive==true)
                {
                resfonc2 = f_derive(Ecr_to_ReX(i,minX,maxX),a,b,choix_f);
                }
                else if(binome==true)
                {
                   if(binome2==true)
                   {
                       resfonc2 = f_binome_de_newton((int)Ecr_to_ReX(i,minX,maxX),(int)c,(int)a,(int)b,2);
                   }
                   else
                   {
                       resfonc2 = f_binome_de_newton((int)Ecr_to_ReX(i,minX,maxX),(int)c,(int)a,(int)b,1);
                   }

                }
                else
                {
                resfonc2 = f(Ecr_to_ReX(i,minX,maxX),a,b,choix_f);
                }

            y = Re_to_EcrY(resfonc2,minY,maxY);
            Line(screen,i,y,i,centreY,bleu_ciel);
            }
        }
    }

    while(0);
}

void line(int x0,int y0, int x1,int y1, Uint32 c)
{
int dx,dy,x,y,residu,absdx,absdy,stepx,stepy,i;
dx=x1-x0; dy=y1-y0; residu=0; x=x0;y=y0; putpixel(x,y,c);
if (dx>0) stepx=1;else stepx=-1; if (dy>0) stepy=1; else stepy=-1;
absdx=abs(dx);absdy=abs(dy);
if (dx==0) for(i=0;i<absdy;i++) { y+=stepy;
 putpixel(x,y,c); }
else if(dy==0) for(i=0;i<absdx;i++){ x+=stepx;
 putpixel(x,y,c); }
else if (absdx==absdy)
 for(i=0;i<absdx;i++) {x+=stepx; y+=stepy;
 putpixel(x,y,c);
 }
else if (absdx>absdy)
 for(i=0;i<absdx;i++)

 { x+=stepx; residu+=absdy;
 if(residu >= absdx) {residu -=absdx; y+=stepy;}
 putpixel(x,y,c);
 }
else for(i=0;i<absdy;i++)
 {y+=stepy; residu +=absdx;
 if (residu>=absdy) {residu -= absdy;x +=stepx;}
 putpixel(x,y,c);
 }
}

void ShowAxisCercle(SDL_Surface* screen,double minX,double maxX,double minY,double maxY)
{
    int centreX = Re_to_EcrX(0.0,minX,maxX);
    int centreY = Re_to_EcrY(0.0,minY,maxY);
    //printf("%f",maxX);
    //printf("%i",centreX);
    Line(screen,centreX,0,centreX,YRES-1,0xFFFFFF);  // axe vertical
    Line(screen,0,centreY,XRES-1,centreY,0xFFFFFF);  // axe horizontal
    Uint32 rouge = SDL_MapRGB(screen->format, 255, 0, 0);
    Uint32 bleu = SDL_MapRGB(screen->format, 0, 0, 255);
    Uint32 bleu_ciel = SDL_MapRGB(screen->format, 0, 140, 255);
}

/*Calcul d'une intégral par la méthode des trapèze qui découpe l'interval en n trapèze qui pour tout x variant de 0,1,2,3..etc calcul la somme de x*f(x).
L'aire d'un trapèze étant (l1 + l2) x h / 2 on retrouve dans cette fonction pour n trapèze la formule faisant la somme total des aires des trapèzes avec
(f(a)+f(b)+2*sum)=(l1 + l2) l1 et l2 les longueurs des ses deux côtés(tous les n trapèzes confondues) ce qui nous donne la valeur de la surface
d'un trapèze comme ci l'interval de découpage ne représenté au final qu'un seul trapèze pour n=1 cependant augmenter la valeur de n nous permet d'obtenir
une meilleur précision de la surface de l'intégral!*/
double trapezoidal(double x1,double x2,int n,double a, double b,double c,int choix_f,bool poly){
  double x,h=0,sum=0,integral;
  double i;

  if(poly=true)
  {
      h=fabs(x2-x1)/n;

      for(i=1;i<n;i++)
      {
      x=x1+i*h;
      sum=sum+f_second_degree(x,a,b,c,1);
      }

      integral=(h/2)*(f_second_degree(x1,a,b,c,1)+f_second_degree(x2,a,b,c,1)+2*sum);
  }
  else
  {
      h=fabs(x2-x1)/n;

      for(i=1;i<n;i++)
      {
      x=x1+i*h;
      sum=sum+f(x,a,b,choix_f);
      }

      integral=(h/2)*(f(x1,a,b,choix_f)+f(x2,a,b,choix_f)+2*sum);
  }

  return integral;
}

double simpson(int n, double x1, double x2,double a,double b,int choix_f)
{
  double X, h, Iapp0, Iapp1, Iapp2, Iapp;
  int NN, i;

  // Etape 1
  h = (x2 - x1) / n;

  // Etape 2
  Iapp0 = f(x1,a,b,choix_f) + f(x2,a,b,choix_f);
  Iapp1 = 0.0;
  Iapp2 = 0.0;

  // Etape 3
  NN = n -1;
  for(i=1; i<=NN; i++)
    {
      // Etape 4
      X = x1 + i*h;
      // Etape 5
      if((i%2) == 0)
        Iapp2 = Iapp2 + f(X,a,b,choix_f);
      else
        Iapp1 = Iapp1 + f(X,a,b,choix_f);
    }

  // Etape 6
  Iapp = (Iapp0 + 2.0 * Iapp2 + 4.0 * Iapp1) * h / 3.0;

  // Etape 7
  return (Iapp);

}

void affiche_courbe(double minX,double maxX,double minY,double maxY,double a,double b,double c,int choix_f,bool integral,bool tengente,bool derive,bool poly,bool binome,bool binome2)
{
           SDL_Surface *screen;
           SDL_Init(SDL_INIT_VIDEO);
           float ten_x=0;

           if(poly==true)
           {
               if(tengente==true)
               {
               printf("\nEntrez la valeur x du point de la tengente %c la courbe compris entre %i et %i?:\n",133,(int)minX+1,(int)maxX-1);
               scanf("%f",&ten_x);
               }

               screen=SDL_SetVideoMode(XRES,YRES,32,SDL_SWSURFACE|SDL_DOUBLEBUF);

               if(SDL_MUSTLOCK(screen))
               SDL_LockSurface(screen);

               ShowAxis(screen,minX,maxX,minY,maxY,a,b,c,choix_f,integral,derive,poly,binome,binome2);

               if(derive==true && integral==true)
               {

               }
               else
               {
               ShowFoncionSecondDegree(screen,0x00FF00,f_second_degree,minX,maxX,minY,maxY,a,b,c,1);
               }


              if(tengente==true)
              {
              double ten_a=0,ten_b=0;
              ten_a=f_derive(ten_x,a,b,8);
              ten_b=f_second_degree(ten_x,a,b,c,1);
              ShowTengente(screen,0x0000FF,f,minX,maxX,minY,maxY,ten_a,ten_b,ten_x,1);
              }
              else if(derive==true)
              {
              ShowFoncion(screen,0x0000FF,f_derive,minX,maxX,minY,maxY,a,b,8);
              }

              if(SDL_MUSTLOCK(screen))
              SDL_UnlockSurface(screen);
              SDL_Flip(screen);
              waitkey();
           }
           else if(binome==true)
           {
               screen=SDL_SetVideoMode(XRES,YRES,32,SDL_SWSURFACE|SDL_DOUBLEBUF);

               if(SDL_MUSTLOCK(screen))
               SDL_LockSurface(screen);

               ShowAxis(screen,minX,maxX,minY,maxY,a,b,c,choix_f,integral,derive,poly,binome,binome2);

               if(derive==true && integral==true)
               {

               }
               else
               {
                   if(binome2==true)
                   {
                       ShowFoncionBinomeDeNewton(screen,0x00FF00,f_binome_de_newton,(int)minX,(int)maxX,(int)minY,(int)maxY,(int)a,(int)b,(int)c,2);
                   }
                   else
                   {
                       ShowFoncionBinomeDeNewton(screen,0x00FF00,f_binome_de_newton,(int)minX,(int)maxX,(int)minY,(int)maxY,(int)a,(int)b,(int)c,1);
                   }

               }

              if(SDL_MUSTLOCK(screen))
              SDL_UnlockSurface(screen);
              SDL_Flip(screen);
              waitkey();
           }
           else
           {
              if(tengente==true)
              {
               printf("Equation d'une tengente au point d'abscisse a de la fonction f(x) est y=f'(a)(x-a)+f(a) avec f'(a) la d%criv%c de f(x)!",130,130);
               printf("\nEntrez la valeur a du point de la tengente %c la courbe compris entre %i et %i?:\n",133,(int)minX+1,(int)maxX-1);
               printf("a=");
               scanf("%f",&ten_x);
              }

              screen=SDL_SetVideoMode(XRES,YRES,32,SDL_SWSURFACE|SDL_DOUBLEBUF);

              if(SDL_MUSTLOCK(screen))
              SDL_LockSurface(screen);

              ShowAxis(screen,minX,maxX,minY,maxY,a,b,c,choix_f,integral,derive,poly,binome,binome2);

              if(derive==true && integral==true)
              {

              }
              else
              {
               ShowFoncion(screen,0x00FF00,f,minX,maxX,minY,maxY,a,b,choix_f);
              }


              if(tengente==true)
              {
               double ten_a=0,ten_b=0;
               ten_a=f_derive(ten_x,a,b,choix_f);
               ten_b=f(ten_x,a,b,choix_f);
               ShowTengente(screen,0x0000FF,f,minX,maxX,minY,maxY,ten_a,ten_b,ten_x,1);
               printf("Equation d'une tengente au point d'abscisse a de la fonction f(x) est y=f'(a)(x-a)+f(a) avec f'(a) la d%criv%c de f(x)!",130,130);
               printf("\nEntrez la valeur a du point de la tengente %c la courbe compris entre %i et %i?:\n",133,(int)minX+1,(int)maxX-1);
               printf("a=");
              }
              else if(derive==true)
              {
               ShowFoncion(screen,0x0000FF,f_derive,minX,maxX,minY,maxY,a,b,choix_f);
              }

              if(SDL_MUSTLOCK(screen))
              SDL_UnlockSurface(screen);
              SDL_Flip(screen);
              waitkey();
           }


}

static bool test_encrypt_decrypt(int nb_bit )
    {
    mini_rsa::big_int pub,pri,mod ;

    mini_rsa::compute_keys( nb_bit,&pub,&pri,&mod ) ;      // génération de la bi-clef
    mini_rsa::big_int v = mini_rsa::random( nb_bit-1 ) ;   // génération d'une donnée aléatoire
    mini_rsa::big_int w = mini_rsa::encrypt( pri,mod,v ) ; // chiffrement avec la clef privée
    mini_rsa::big_int x = mini_rsa::encrypt( pub,mod,w ) ; // déchiffrement avec la clef publique
    mini_rsa::big_int y = mini_rsa::encrypt( pub,mod,x ) ; // chiffrement avec la clef publique
    mini_rsa::big_int z = mini_rsa::encrypt( pri,mod,y ) ; // déchiffrement avec la clef privée
    return( (v == x) && (v == z) ) ;                       // vérifications
    }

///////////////////////////////////////////////////////////////////////////////

// le nb d'iterations dépend du nombre de bits
static int nb_loop ( int nb_bit )
    {
    return( nb_bit*nb_bit*nb_bit*nb_bit*nb_bit/1000  ) ;
    }


void saisir_chaine(char * lpBuffer, int buf_size)
{
    char * p;

    fgets(lpBuffer, buf_size, stdin);

    if ((p = strchr(lpBuffer, '\n')) == NULL)
    {
        int c;

        do
            c = getchar();
        while (c != EOF && c != '\n');
    }
    else
        *p = '\0';
}

void Affiche_Courbe_Second_Degree(double a,double b,double c,int choix_f)
{
  int n;
  float x1,x2,spmthd=0;
  double minX, maxX, minY, maxY;
  int choix;
  SDL_Surface *screen;

  SDL_Init(SDL_INIT_VIDEO);

  printf("Entrez la valeur x1 de la borne inf%crieure de l'interval de la fonction!\nx1=",130,130);
  scanf("%f",&x1);
  printf("Entrez la valeur x2 de la borne sup%crieure de l'interval de la fonction!\nx2=",130,130);
  scanf("%f",&x2);
  printf("Entrez la valeur n correspondant au nombre de d%ccoupage de l'interval en trap%cze(Pour le calcul int%cgral)!\nn=",130,138,130);
  scanf("%i",&n);

  spmthd=trapezoidal(x1,x2,n,a,b,c,choix_f,true);
  printf("\nValeur de l'int%cgral de la fonction polyn%cme: %ix%c+%ix+%i sur [%i,%i]: %f \n",130,147,(int)a,253,(int)b,(int)c,(int)x1,(int)x2,spmthd);

  printf("\nEntrez le num%cro de l\'op%cration desir%ce?:\n",130,130,130);
  printf("\n(1) Afficher une repr%csentation graphique de la courbe(En vert!) + Calcul int%cgral(En bleu ciel!) sur l'interval [%i,%i]?\n",130,130,(int)x1,(int)x2);
  printf("\n(2) Afficher une repr%csentation graphique de la courbe(En vert!) + Tengente(En bleu fonc%c!) %c un point x \nde l'interval [%i,%i]?\n",130,130,133,(int)x1,(int)x2);
  printf("\n(3) Afficher une repr%csentation graphique de la courbe(En vert!) + Deriv%c de la fonction(En bleu fonc%c!) sur [%i,%i]?\n",130,130,130,(int)x1,(int)x2);
  printf("\n(4) Afficher une repr%csentation graphique de la derive(En bleu fonc%c!) + Calcul int%cgral(En bleu ciel!) \nsur l'interval [%i,%i]?\n",130,130,130,(int)x1,(int)x2);

  printf("\nQuel est votre choix?:");

  scanf("%d",&choix);

  switch(choix)
  {
         case 1:
         {
          minX=x1-1;
          maxX=x2+1;

                 double minYx1=f_second_degree(x1,a,b,c,choix_f)-5;
                 double minYx2=f_second_degree(x2,a,b,c,choix_f)-5;
                 double maxYx1=f_second_degree(x1,a,b,c,choix_f)+15;
                 double maxYx2=f_second_degree(x2,a,b,c,choix_f)+15;

                 if(maxYx1>maxYx2)
                 {
                    maxY=maxYx1;
                 }
                 else
                 {
                    maxY=maxYx2;
                 }

                 if(minYx1>minYx2)
                 {
                    minY=minYx2;
                 }
                 else
                 {
                    minY=minYx1;
                 }

          affiche_courbe(minX,maxX,minY,maxY,a,b,c,choix_f,true,false,false,true,false,false);
         };break;

         case 2:
         {
           minX=x1-1;
           maxX=x2+1;

                 double minYx1=f_second_degree(x1,a,b,c,choix_f)-5;
                 double minYx2=f_second_degree(x2,a,b,c,choix_f)-5;
                 double maxYx1=f_second_degree(x1,a,b,c,choix_f)+15;
                 double maxYx2=f_second_degree(x2,a,b,c,choix_f)+15;

                 if(maxYx1>maxYx2)
                 {
                    maxY=maxYx1;
                 }
                 else
                 {
                    maxY=maxYx2;
                 }

                 if(minYx1>minYx2)
                 {
                    minY=minYx2;
                 }
                 else
                 {
                    minY=minYx1;
                 }


          affiche_courbe(minX,maxX,minY,maxY,a,b,c,choix_f,false,true,false,true,false,false);

          };break;
          case 3:
          {

           minX=x1-1;
           maxX=x2+1;

                 double minYx1=f_second_degree(x1,a,b,c,choix_f)-5;
                 double minYx2=f_second_degree(x2,a,b,c,choix_f)-5;
                 double maxYx1=f_second_degree(x1,a,b,c,choix_f)+15;
                 double maxYx2=f_second_degree(x2,a,b,c,choix_f)+15;

                 if(maxYx1>maxYx2)
                 {
                    maxY=maxYx1;
                 }
                 else
                 {
                    maxY=maxYx2;
                 }

                 if(minYx1>minYx2)
                 {
                    minY=minYx2;
                 }
                 else
                 {
                    minY=minYx1;
                 }

          affiche_courbe(minX,maxX,minY,maxY,a,b,c,choix_f,false,false,true,true,false,false);

          };break;
          case 4:
          {

           minX=x1-1;
           maxX=x2+1;

                 double minYx1=f_second_degree(x1,a,b,c,choix_f)-5;
                 double minYx2=f_second_degree(x2,a,b,c,choix_f)-5;
                 double maxYx1=f_second_degree(x1,a,b,c,choix_f)+15;
                 double maxYx2=f_second_degree(x2,a,b,c,choix_f)+15;

                 if(maxYx1>maxYx2)
                 {
                    maxY=maxYx1;
                 }
                 else
                 {
                    maxY=maxYx2;
                 }

                 if(minYx1>minYx2)
                 {
                    minY=minYx2;
                 }
                 else
                 {
                    minY=minYx1;
                 }

          affiche_courbe(minX,maxX,minY,maxY,a,b,c,choix_f,true,false,true,true,false,false);

          };break;
  }
}

void Tableau_Variation(double minX, double maxX, double minY, double maxY, double a, double b, int choix_f)
{
    int maxXInter=0,minXInter=minX;
    char lettre[1]="";
    FILE* fichier = NULL;

    fichier = fopen("tableau_de_variation.txt","w");

    printf("Souhaitez vous sauvegarder le tableau de variation dans un fichier(tableau_de_variation.txt)?\n o/n \n");
    printf("Quel est votre choix?:");
    scanf(" %c",&lettre);

    if(strcmp(lettre,"o")==1)
    {

        printf("\n%c Tableau de variation de f(x) sur [%i,%i]: %c",186,(int)minX,(int)maxX,186);
        fprintf(fichier,"\n%c Tableau de variation de f(x) sur [%i,%i]: %c",186,(int)minX,(int)maxX,186);

        for(int i=minX;i<=maxX;i++)
        {
            if(f_derive(i,a,b,choix_f)>0)
            {

                if(i>maxXInter)
                {
                maxXInter=i;
                }

                printf("\n%c Signe de la fonction f'(x) sur [%i,%i]: %c",186, maxXInter-1, maxXInter,186);
                printf("\n%c Sur [%i,%i] le signe de la fonction f'(x) est positif %c",186, maxXInter-1,maxXInter,186);
                printf("\n%c Tableau de variation de la fonction f(x) sur [%i,%i]: %c",186,maxXInter-1,maxXInter,186);
                printf("\n%c Sur [%i,%i] f'(x)>0 ==> f(x) croissante %c",186, maxXInter-1,maxXInter,186);
                fprintf(fichier,"\n%c Signe de la fonction f'(x) sur [%i,%i]: %c",186, maxXInter-1, maxXInter,186);
                fprintf(fichier,"\n%c Sur [%i,%i] le signe de la fonction f'(x) est positif %c",186, maxXInter-1,maxXInter,186);
                fprintf(fichier,"\n%c Tableau de variation de la fonction f(x) sur [%i,%i]: %c",186,maxXInter-1,maxXInter,186);
                fprintf(fichier,"\n%c Sur [%i,%i] f'(x)>0 ==> f(x) croissante %c",186, maxXInter-1,maxXInter,186);
            }
            else if(f_derive(i,a,b,choix_f)<0)
            {
                if(i>maxXInter)
                {
                maxXInter=i;
                }

                printf("\n%c Signe de la fonction f'(x) sur [%i,%i]: %c",186, maxXInter-1, maxXInter,186);
                printf("\n%c Sur [%i,%i] le signe de f'(x) est n%cgatif %c",186, maxXInter-1,maxXInter,130,186);
                printf("\n%c Tableau de variation de la fonction f(x) sur [%i,%i]: %c",186,maxXInter-1,maxXInter,186);
                printf("\n%c Sur [%i,%i] f'(x)<0 ==> f(x) d%ccroissante %c",186, maxXInter-1,maxXInter,130,186);
                fprintf(fichier,"\n%c Signe de la fonction f'(x) sur [%i,%i]: %c",186, maxXInter-1, maxXInter,186);
                fprintf(fichier,"\n%c Sur [%i,%i] le signe de f'(x) est n%cgatif %c",186, maxXInter-1,maxXInter,130,186);
                fprintf(fichier,"\n%c Tableau de variation de la fonction f(x) sur [%i,%i]: %c",186,maxXInter-1,maxXInter,186);
                fprintf(fichier,"\n%c Sur [%i,%i] f'(x)<0 ==> f(x) d%ccroissante %c",186, maxXInter-1,maxXInter,130,186);
            }
            else
            {

                if(i>maxXInter)
                {
                maxXInter=i;
                }

                printf("\n%c Signe de la fonction f'(x) sur [%i,%i]: %c",186,maxXInter-1, maxXInter,186);
                printf("\n%c Sur [%i,%i] le signe de f'(x) est null %c",186,maxXInter-1,maxXInter,186);
                printf("\n%c Tableau de variation de la fonction f(x) sur [%i,%i]: %c",186,maxXInter-1, maxXInter,186);
                printf("\n%c Sur [%i,%i] f'(x)=0 ==> f(x) constante %c",186,maxXInter-1, maxXInter,186);
                fprintf(fichier,"\n%c Signe de la fonction f'(x) sur [%i,%i]: %c",186,maxXInter-1, maxXInter,186);
                fprintf(fichier,"\n%c Sur [%i,%i] le signe de f'(x) est null %c",186,maxXInter-1,maxXInter,186);
                fprintf(fichier,"\n%c Tableau de variation de la fonction f(x) sur [%i,%i]: %c",186,maxXInter-1, maxXInter,186);
                fprintf(fichier,"\n%c Sur [%i,%i] f'(x)=0 ==> f(x) constante %c",186,maxXInter-1, maxXInter,186);
            }
        }
   }
   else
   {
        printf("\n%c Tableau de variation de f(x) sur [%i,%i]: %c",186,(int)minX,(int)maxX,186);

        for(int i=minX;i<=maxX;i++)
        {
            if(f_derive(i,a,b,choix_f)>0)
            {

                if(i>maxXInter)
                {
                maxXInter=i;
                }

                printf("\n%c Signe de la fonction f'(x) sur [%i,%i]: %c",186, maxXInter-1, maxXInter,186);
                printf("\n%c Sur [%i,%i] le signe de la fonction f'(x) est positif %c",186, maxXInter-1,maxXInter,186);
                printf("\n%c Tableau de variation de la fonction f(x) sur [%i,%i]: %c",186,maxXInter-1,maxXInter,186);
                printf("\n%c Sur [%i,%i] f'(x)>0 ==> f(x) croissante %c",186, maxXInter-1,maxXInter,186);
            }
            else if(f_derive(i,a,b,choix_f)<0)
            {
                if(i>maxXInter)
                {
                maxXInter=i;
                }

                printf("\n%c Signe de la fonction f'(x) sur [%i,%i]: %c",186, maxXInter-1, maxXInter,186);
                printf("\n%c Sur [%i,%i] le signe de f'(x) est n%cgatif %c",186, maxXInter-1,maxXInter,130,186);
                printf("\n%c Tableau de variation de la fonction f(x) sur [%i,%i]: %c",186,maxXInter-1,maxXInter,186);
                printf("\n%c Sur [%i,%i] f'(x)<0 ==> f(x) d%ccroissante %c",186, maxXInter-1,maxXInter,130,186);
            }
            else
            {

                if(i>maxXInter)
                {
                maxXInter=i;
                }

                printf("\n%c Signe de la fonction f'(x) sur [%i,%i]: %c",186,maxXInter-1, maxXInter,186);
                printf("\n%c Sur [%i,%i] le signe de f'(x) est null %c",186,maxXInter-1,maxXInter,186);
                printf("\n%c Tableau de variation de la fonction f(x) sur [%i,%i]: %c",186,maxXInter-1, maxXInter,186);
                printf("\n%c Sur [%i,%i] f'(x)=0 ==> f(x) constante %c",186,maxXInter-1, maxXInter,186);
            }
        }
   }
}

void Calcul_Integral(bool stats,float tab[])
{
  int i,n;
  float x1,x2,spmthd=0,a,b,res_poisson=0,res_poisson_au_plus=0,k_poisson=0,y_poisson=0;
  int res_pourcentage_au_plus=0,res_pourcentage=0;
  double minX, maxX, minY, maxY;
  int choix_courbe=-1, choix_f, choix_poisson=0, choix2;
  SDL_Surface *screen;

  SDL_Init(SDL_INIT_VIDEO);

  if(stats==false)
  {
  printf("Entrez la fonction de l'int%cgral %c calculer!\n (1) Fonction lin%caire: a*x+b \n (2) Fonction x au carr%c: a*x%c+b \n (3) Fonction x au cube: a*x%c+b \n (4) Fonction inverse: 1/(a*x+b)\n (5) Fonction logarithme: log(a*x+b) \n (6) Fonction sinus: sin(a*x+b)\n (7) Fonction cosinus: cos(a*x+b)\n (8) Fonction loi de poisson avec P(X=k;y)=(y^k*e^-y)/k!\n",130,133,130,130,253,252);
  printf("\nQuel est votre choix?:");
  scanf("%i",&choix_f);
  }
  else
  {
      choix_f=1;
  }

  if(choix_f==8)
  {
    printf("(1) Probabilit%c de la loi de poisson de type P(X=k,y) Probabilit%c qu'il se produise exactement k %cv%cnements par rapport %c une fr%cquence p%criodique y connue!\n",130,130,130,130,133,130,130);
    printf("(2) Probabilit%c de la loi de poisson de type P(X>=k,y) Probabilit%c qu'il se produise exactement k ou plus %cv%cnements par rapport %c une fr%cquence p%criodique y connue!\n",130,130,130,130,133,130,130);
    printf("(3) Probabilit%c de la loi de poisson de type P(X<=k,y) Probabilit%c qu'il se produise exactement k ou moins %cv%cnements par rapport %c une fr%cquence p%criodique y connue!\n",130,130,130,130,133,130,130);
    printf("Quel est votre choix?:");
    scanf("%i",&choix_poisson);

     switch(choix_poisson)
     {
     case 1:
          {
            printf("Entrez la valeur de k sachant que k correspond au nombre exact qu'un %cv%cnement se produise!\nk=",130,130);
            scanf("%f",&k_poisson);
            printf("Entrez la valeur de y sachant que y correspond au nombre d'%cv%cnements survenue pour une p%criodicit%c connue\n(Exemple: Il se produit en moyenne 10 accidents par an!)!\ny=",130,130,130,130);
            scanf("%f",&y_poisson);

            res_poisson=poisson(k_poisson,y_poisson);
            res_pourcentage=(int)round(res_poisson*100);
            x1=k_poisson-1;
            x2=k_poisson;
            a=y_poisson;
            b=1;

            printf("La probabilit%c qu'il se produise exactement k %cv%cnements pour une fr%cquence p%criodique de: %i est de: %f \nsoit %i pourcent!\n",130,130,130,130,130,(int)y_poisson,res_poisson,res_pourcentage);

          };break;
     case 2:
          {
            printf("Entrez la valeur de k sachant que k correspond au nombre exact ou plus qu'un %cv%cnement se produise!\nk=",130,130);
            scanf("%f",&k_poisson);
            printf("Entrez la valeur de y sachant que y correspond au nombre d'%cv%cnements survenue pour une p%criodicit%c connue\n(Exemple: Il se produit en moyenne 10 accidents par an!)!\ny=",130,130,130,130);
            scanf("%f",&y_poisson);

            for(int i=0; i<=k_poisson; i++)
            {
            res_poisson=res_poisson+poisson(i,y_poisson);
            }

            res_poisson_au_plus=1-res_poisson;
            res_pourcentage=res_poisson*100;
            res_pourcentage_au_plus=(int)round(100-res_pourcentage);
            x1=k_poisson;
            x2=y_poisson;
            a=y_poisson;
            b=1;

            printf("La probabilit%c qu'il se produise exactement k %cv%cnements ou plus pour une fr%cquence p%criodique de: %i \nest de: %f soit %i pourcent!\n",130,130,130,130,130,(int)y_poisson,res_poisson_au_plus,res_pourcentage_au_plus);

          };break;
     case 3:
          {
            printf("Entrez la valeur de k sachant que k correspond au nombre exact ou moins qu'un %cv%cnement se produise!\nk=",130,130);
            scanf("%f",&k_poisson);
            printf("Entrez la valeur de y sachant que y correspond au nombre d'%cv%cnements survenue pour une p%criodicit%c connue\n(Exemple: Il se produit en moyenne 10 accidents par an!)!\ny=",130,130,130,130);
            scanf("%f",&y_poisson);

            for(int i=0; i<=k_poisson; i++)
            {
            res_poisson=res_poisson+poisson(i,y_poisson);
            }

            res_pourcentage=(int)round(res_poisson*100);
            x1=0;
            x2=k_poisson;
            a=y_poisson;
            b=1;


            printf("La probabilit%c qu'il se produise exactement k %cv%cnements ou moins pour une fr%cquence p%criodique de: %i \nest de: %f soit %i pourcent!\n",130,130,130,130,130,(int)y_poisson,res_poisson,res_pourcentage);

          };break;
     }
  }
  else
  {
      if(stats==false)
      {
          printf("Entrez la valeur de a!\na=");
          scanf("%f",&a);
          printf("Entrez la valeur de b!\nb=");
          scanf("%f",&b);
      }
      else
      {
       a=tab[7];
       b=tab[8];
      }

  printf("Entrez la valeur x1 de la borne inf%crieure de l'interval de l'int%cgral!\nx1=",130,130);
  scanf("%f",&x1);
  printf("Entrez la valeur x2 de la borne sup%crieure de l'interval de l'int%cgral!\nx2=",130,130);
  scanf("%f",&x2);
  printf("Entrez la valeur n correspondant au nombre de d%ccoupage de l'interval en trap%cze!\nn=",130,138);
  scanf("%i",&n);

  spmthd=trapezoidal(x1,x2,n,a,b,0,choix_f,false);
  printf("\nValeur de l'int%cgral de la fonction sur [%i,%i]: %f \n",130,(int)x1,(int)x2,spmthd);
  }

  printf("\nEntrez le num%cro de l\'op%cration desir%ce?:\n",130,130,130);
  printf("\n(1) Afficher une repr%csentation graphique de la courbe(En vert!) + Calcul int%cgral(En bleu ciel!) sur l'interval [%i,%i]?\n",130,130,(int)x1,(int)x2);

  if(stats==false && choix_poisson==0)
  {
     printf("\n(2) Afficher une repr%csentation graphique de la courbe(En vert!) + Tengente(En bleu fonc%c!) %c un point x \nde l'interval [%i,%i]?\n",130,130,133,(int)x1,(int)x2);
     printf("\n(3) Afficher une repr%csentation graphique de la courbe(En vert!) + Deriv%c de la fonction(En bleu fonc%c!) sur [%i,%i]?\n",130,130,130,(int)x1,(int)x2);
     printf("\n(4) Afficher une repr%csentation graphique de la derive(En bleu fonc%c!) + Calcul int%cgral(En bleu ciel!) \nsur l'interval [%i,%i]?\n",130,130,130,(int)x1,(int)x2);
     printf("\n(5) Dresser le tableau de variation de la fonction sur l'interval [%i,%i]?\n",(int)x1,(int)x2);
  }
  printf("\nQuel est votre choix?:");

  while(choix_courbe!=0)
  {
  scanf("%d",&choix_courbe);

  switch(choix_courbe)
  {
   case 1:
         {
          minX=x1-1;
          maxX=x2+1;

           if(choix_f==8)
           {
                 minY=-0.1;
                 maxY=f(x2,a,b,choix_f)+0.1;
           }
           else
           {

                 minY=-10;
                 double maxYx1=f(x1,a,b,choix_f)+5;
                 double maxYx2=f(x2,a,b,choix_f)+5;

                 if(maxYx1>maxYx2)
                 {
                    maxY=maxYx1;
                 }
                 else
                 {
                    maxY=maxYx2;
                 }
           }
          affiche_courbe(minX,maxX,minY,maxY,a,b,0,choix_f,true,false,false,false,false,false);
         };break;
         case 2:
         {

           minX=x1-1;
           maxX=x2+1;

           if(choix_f==8)
           {
                 minY=-0.1;
                 maxY=f(x2,a,b,choix_f)+0.1;
           }
           else
           {

                 minY=-10;
                 double maxYx1=f(x1,a,b,choix_f)+5;
                 double maxYx2=f(x2,a,b,choix_f)+5;

                 if(maxYx1>maxYx2)
                 {
                    maxY=maxYx1;
                 }
                 else
                 {
                    maxY=maxYx2;
                 }
           }

          affiche_courbe(minX,maxX,minY,maxY,a,b,0,choix_f,false,true,false,false,false,false);

          };break;
          case 3:
          {

           minX=x1-1;
           maxX=x2+1;

           if(choix_f==8)
           {
                 minY=-0.1;
                 maxY=f(x2,a,b,choix_f)+0.1;
           }
           else
           {

                 minY=-10;
                 double maxYx1=f(x1,a,b,choix_f)+5;
                 double maxYx2=f(x2,a,b,choix_f)+5;

                 if(maxYx1>maxYx2)
                 {
                    maxY=maxYx1;
                 }
                 else
                 {
                    maxY=maxYx2;
                 }
           }

          affiche_courbe(minX,maxX,minY,maxY,a,b,0,choix_f,false,false,true,false,false,false);

          };break;
          case 4:
          {

           minX=x1-1;
           maxX=x2+1;

           if(choix_f==8)
           {
                 minY=-0.1;
                 maxY=f(x2,a,b,choix_f)+0.1;
           }
           else
           {

                 minY=-10;
                 double maxYx1=f(x1,a,b,choix_f)+5;
                 double maxYx2=f(x2,a,b,choix_f)+5;

                 if(maxYx1>maxYx2)
                 {
                    maxY=maxYx1;
                 }
                 else
                 {
                    maxY=maxYx2;
                 }
           }

          affiche_courbe(minX,maxX,minY,maxY,a,b,0,choix_f,true,false,true,false,false,false);

          };break;
          case 5:
          {
           minX=x1-1;
           maxX=x2+1;

           minY=-10;
           double maxYx1=f(x1,a,b,choix_f)+5;
           double maxYx2=f(x2,a,b,choix_f)+5;

           if(maxYx1>maxYx2)
             {
              maxY=maxYx1;
             }
             else
             {
              maxY=maxYx2;
             }

           int choix_courbe2=0;
           Tableau_Variation(minX,maxX,minY,maxY,a,b,choix_f);
           printf("\n\n(1) Afficher une repr%csentation graphique de la courbe(En vert!) + Calcul int%cgral(En bleu ciel!) sur l'interval [%i,%i]?\n",130,130,(int)x1,(int)x2);
           printf("Quel est votre choix?:");
           scanf("%d",&choix_courbe2);

           switch(choix_courbe2)
           {
               case 1:
               {
               affiche_courbe(minX,maxX,minY,maxY,a,b,0,choix_f,true,false,false,false,false,false);
               }break;
           }

          }break;
  }
  }
}

void RSA()
{
     int tot,n,nb_bit;

            // calcul du nb total d'iteration qu'on aurra à faire (juste pour affichier le % !)
            for(tot=0,nb_bit=9;nb_bit<=mini_rsa::max_nb_bit;nb_bit++)
                for(int i=0;i<nb_loop(nb_bit);i++ )
                tot++ ;

            // Boucle sur le nombre de bits : on commence à 9 car en dessous, ça n'a plus de sens
            //(pas assez de nombre premiers dans ces petits intervalles)
            for(n=0,nb_bit=9;nb_bit<=mini_rsa::max_nb_bit;nb_bit++)
            // Le nombre de tests effectués pour un nombre de bit donné n'est pas constant
            for(int i=nb_loop(nb_bit);i>0;--i)
            {
            if((++n&127)==0) // affiche la progression
                cout << "test de mini_rsa sur " << nb_bit << " bits (" << (n*100)/tot << "%)\r" ;

            // appelle le test
            if(!test_encrypt_decrypt( nb_bit )) // et affiche un message en cas d'erreur
                cout << "echec de mini_rsa avec " << nb_bit << " bits !  " << endl ;
            }

            cout << endl << "fini." << endl ;
}

void Second_Degre()
{
       float a,b,c,d,r1,r2,x;
       int choix;

       printf("\n\nCe programme r%csoud une %cquation du second degr%c du type ax%c+bx+c=0",130,130,130,253);

       printf("\n\nEntrez la valeur de a:");
       scanf("%f", &a);
       printf("\nEntrez la valeur de b:");
       scanf("%f", &b);
       printf("\nEntrez la valeur de c:");
       scanf("%f",&c);
       d =b*b-(4*a*c);

       if(a==0)
       {
          if(b!=0)
          {
             x=-c/b;
             printf("\nUne racine simple: %f",x);
          }
          else if(c==0)
             printf("\nInfinit%c de racines",130);

          else printf("\nPas de solutions");
       }
       else
       {
          if(d>0)
          {
               r1 =(b-sqrt(d))/(2*a);
               r2 =(-b-sqrt(d))/(2*a);
               printf("\nIl y a deux solutions: %f %f et le polynome du second degr%c peut d%csormais s'%ccrire ainsi:\n %f(x-%f)(x-%f)",-r1,r2,130,130,130,a,r1,r2);
          }
          else
          {
               if(d==0)
               {
                    r1 =(-b)/(2*a);
                    printf("\nIl y a une solution: %f et le polynome du second degr%c peut d%csormais s'%ccrire ainsi:\n %f(x-%f)",r1,130,130,130,a,r1);
               }
               else printf("\nPas de racines r%celles",130);
          }

          printf("\n(1) Afficher une repr%csentation graphique de la courbe sur un interval donn%c?\n",130,130);
          printf("\nQuel est votre choix?:");
          scanf("%d",&choix);

          switch(choix)
          {
            case 1:
            {
	        Affiche_Courbe_Second_Degree(a,b,c,1);
            }
          }

       }
       getch();
}

void circle(int xo, int yo, int R, Uint32 c)
 {
 int x, y, F, F1, F2,newx,newy;
 x=xo; y=yo+R; F=0;

    if(x<800 && x>=0 && y>=0 && y<600) putpixel(x,y,c);
    if(x<800 && x>=0 && 2*yo-y>=0 && 2*yo-y<600) putpixel (x,2*yo-y, c);

    while(y>yo)
    {
    F1=F+2*(x-xo)+1; F2=F-2*(y-yo)+1;
    if(abs(F1)<abs(F2))
        {
            x+=1; F=F1;
        }
    else
        {
            y-=1; F=F2;
        }

    if(x<800 && x>=0 && y>=0 && y<600)
        putpixel(x,y,c);
        newx=2*xo-x;
        newy=2*yo-y;

    if(x<800 && x>=0 && newy>=0 && newy<600)
        putpixel(x, newy,c);
    if(newx<800 && newx>=0 && y>=0 && y<600)
        putpixel( newx,y,c);
    if(newx<800 && newx>=0 && newy>=0 && newy<600)
        putpixel(newx,newy, c);
    }

    if(xo+R<800 && xo+R>=0) putpixel(xo+R,yo,c);
    if(xo-R<800 && xo-R>=0) putpixel(xo-R,yo, c);
 }

 void filldisc( int xo, int yo, int R, Uint32 c)
 {
 int x, y, F, F1, F2,newx,newy,xx;
 x=xo; y=yo+R; F=0;
 if (x<800 && x>=0 && y>=0 && y<600) putpixel(x,y,c);
 if (x<800 && x>=0 && 2*yo-y>=0 && 2*yo-y<600) putpixel (x,2*yo-y, c);
 while( y>yo)
 {
 F1=F+2*(x-xo)+1; F2=F-2*(y-yo)+1;
 if ( abs(F1)<abs(F2)) { x+=1; F=F1;}
 else {y-=1; F=F2;}
 newx=2*xo-x ; newy=2*yo-y ;
 for(xx=newx; xx<=x; xx++)if (xx<800 && xx>=0 && y>=0 && y<600 )
 putpixel(xx,y,c);
 for(xx=newx; xx<=x; xx++)if (xx<800 && xx>=0 && newy>=0 && newy<600 )
 putpixel(xx,newy,c);
 }
 if (xo+R<800 && xo+R>=0&& y>=0 && y<600) putpixel(xo+R,yo,c);
 if (xo-R<800 && xo-R>=0&& y>=0 && y<600) putpixel(xo-R,yo, c);
 }


void Cercle()
{
    float x=0,y=0,r=0;
    double minX,maxX,minY,maxY;
    int choix_graph=0;

    printf("\n\nEntrez la valeur x des coordonn%ces du centre du cercle:",130);
    scanf("%f",&x);
    printf("\nEntrez la valeur y des coordonn%ces du centre du cercle:",130);
    scanf("%f",&y);
    printf("\nEntrez la valeur r du rayon du cercle de centre(%i,%i):",(int)x,(int)y);
    scanf("%f",&r);
    printf("\nL'%cquation cart%csienne du cercle est de la forme: (x-%i)%c+(y-%i)%c=%i",130,130,(int)x,253,(int)y,253,(int)r*(int)r);
    printf("\n(1) Afficher une repr%csentation graphique du cercle de centre(%i,%i):",130,(int)x,(int)y);
    printf("\nQuel est votre choix?:");
    scanf("%d",&choix_graph);

    switch(choix_graph)
    {
    case 1:
         {
         minX=-r-10;
         maxX=r+10;
         minY=-r-10;
         maxY=r+10;
         SDL_Init(SDL_INIT_VIDEO);
         screen=SDL_SetVideoMode(800,600,32, SDL_SWSURFACE|SDL_DOUBLEBUF);

         if(SDL_MUSTLOCK(screen))
              SDL_LockSurface(screen);

         /* exemples de couleurs avec leurs trois composantes RGB */
         couleur[0]=SDL_MapRGB(screen->format,0,0,0); /** white */
         couleur[1]=SDL_MapRGB(screen->format,255,0,0); /** red */
         couleur[2]=SDL_MapRGB(screen->format,0,250,0); /** vert */
         SDL_FillRect(screen,0,couleur[0]); /* donne un fond blanc à la fenêtre */
         ShowAxisCercle(screen,minX,maxX,minY,maxY);
         circle(Re_to_EcrX(x,minX,maxX),Re_to_EcrY(y,minY,maxY),(XRES/(2*r+2*10))*r,couleur[1]);

         SDL_Flip(screen); /* Cette fonction affiche l’image issue du programme sur l’écran. SI on ne le fait pas, on
         ne verra rien. On sera souvent amené à l’utiliser plusieurs fois dans le programme pour
         voir ce qui se passe */
         pause();
         }
    }
}

void radioactivite(char atome[],float t_un_demi,bool choix_atome)
{

    if(choix_atome=true)
    {
            int i, n;
            float t, l=0, p, m, T, T_max=0;
            float N[10000], dN[10000];
            char val;
            FILE* sortie = NULL;
            FILE* sortie2 = NULL;

            printf("RESOLUTION DE L'EQUATION DIFFERENTIELLE DE DECROISSANCE RADIOACTIVE.\n");
           /* saisie des données */

            printf("-Conditions initiales:\n");
            printf("t0:");
            scanf("%f", &t);

            printf("N0:");
            scanf("%f",&N[0]);

            l=(float)(log(2)/t_un_demi);
            printf("-Constante de radioactivit%c Lambda du %s:\n",130,atome);
            printf("Connaissant le temps de demi vie du %s t(1/2)=%f alors Lambda=log(2)/t(1/2)=%f\n",atome,t_un_demi,l);

            printf("-Pas:");
            scanf("%f",&p);

            retour:;
            printf("-Nombre de calculs(<10000):");
            scanf("%d",&n);

            if(n>=10000)
            {
            printf("%d est sup%crieur %c 10000\n",130,133,n);
            goto retour;
            }

            /* calculs */

            printf("\n      t            dN/dt           N\n");
            printf(" %f     %f      %f\n",t,(-l*N[0]),N[0]);

            dN[0]=-l*N[0];

            for(i=1;i<=n;i++)                    // routine de calcul, selon
            {                            // la méthode d'Euler.
            T=t+(i*p);

            if(T_max<T)
            {
                T_max=T;
            }

            dN[i]=-l*N[i-1];
            N[i]=N[i-1]+(dN[i]*p);
            printf(" %f     %f      %f\n",T,dN[i],N[i]);
            }

            /* ****************************************************** */
            /* sauvegarde des données dans un le fichier donnees.txt  */
            /* ****************************************************** */
            /* demande s'il faut effectuer la sauvegarde */

            int choix;
            printf("(1) Afficher une repr%csentation graphique de la d%ccroissance du %s?\n",130,130,atome);
            printf("(2) Sauvegarder ces donn%ces dans un fichier?\n",130);
            printf("\nQuel est votre choix?:");
            scanf("%d",&choix);

            switch(choix)
            {
                case 1:
                    {
                         double minX=0;
                         double maxX=T_max;

                         double minY=-5;
                         double maxY=N[0]+10;

                         affiche_courbe(minX,maxX,minY,maxY,N[0],l,0,9,false,false,false,false,false,false);

                    }break;
                case 2:
                    {
                        /* **************************************************** */
                        /*         enregistrement du fichier donnees.txt                               */
                        /* **************************************************** */

                        sortie=fopen("C:\\donnees.txt","wt");           //ouvre ou créer le fichier donnees.txt en mode écriture

                        if(sortie==NULL)                //renvoi un message d'erreur si le fichier n'a pas pu être ouvert ou créé
                        {
                        printf("\nErreur dans la creation du fichier donnees.txt\n");
                        }

                        printf("\nLe fichier donnees.txt a ete correctement ouvert\n");
                        printf("Enregistrement de donnees.txt...\n");

                        /* Enregistrement du fichier */

                        fprintf(sortie,"\n      t            dN/dt                        N\n");
                        fprintf(sortie," %f     %f      %f\n",t,(-l*N[0]),N[0]);

                        for(i=1;i<=n;i++)
                        {
                        T=t+(i*p);
                        dN[i]=-l*N[i-1];
                        N[i]=N[i-1]+(dN[i]*p);
                        fprintf(sortie," %f     %f      %f\n",T,dN[i],N[i]);
                        }

                        fprintf(sortie,"\n****** FIN DE FICHIER ******\n");
                        fclose(sortie);

                        printf("Donn%ces enregistr%ces!\n",130,130);

                        /* **************************************************** */
                        /*         enregistrement du fichier courbe.txt                                  */
                        /* **************************************************** */


                        sortie2=fopen("C:\\courbe.txt", "wt");             //ouvre ou créer le fichier courbe.txt en mode écriture

                        if(sortie2==NULL)               //renvoi un message d'erreur si le fichier n'a pas pu être ouvert ou créé
                        {
                        printf("\nErreur dans la creation du fichier courbe.txt\n");
                        }

                        printf("\nLe fichier courbe.txt a ete correctement ouvert\n");
                        printf("Enregistrement de courbe.txt...\n");

                        fprintf(sortie2,"%f,%f\n",t,N[0]);

                        for(i=1;i<=n;i++)
                        {
                        T=t+(i*p);
                        dN[i]=-l*N[i-1];
                        N[i]=N[i-1]+(dN[i]*p);
                        fprintf(sortie2,"%f,%f\n",T,N[i]);
                        }

                        fclose(sortie2);

                        printf("Donn%ces enregistr%ces!\n",130,130);


                    }break;

            }

    }
    else
    {
            int i, n;
            float t, l, p, m, T, T_max;
            float N[10000], dN[10000];
            char val;
            FILE* sortie = NULL;
            FILE* sortie2 = NULL;

            printf("RESOLUTION DE L'EQUATION DIFFERENTIELLE DE DECROISSANCE RADIOACTIVE.\n");
           /* saisie des données */

            printf("-Conditions initiales:\n");
            printf("t0:");
            scanf("%f", &t);

            printf("N0:");
            scanf("%f",&N[0]);

            printf("-Constante de radioactivit%c\n",130);
            printf("Lambda:");
            scanf("%f",&l);

            printf("-Pas:");
            scanf("%f",&p);

            retour2:;
            printf("-Nombre de calculs(<10000):");
            scanf("%d",&n);

            if(n>=10000)
            {
            printf("%d est sup%crieur %c 10000\n",130,133,n);
            goto retour2;
            }

            /* calculs */

            printf("\n      t            dN/dt           N\n");
            printf(" %f     %f      %f\n",t,(-l*N[0]),N[0]);

            dN[0]=-l*N[0];

            for(i=1;i<=n;i++)                    // routine de calcul, selon
            {                                   // la méthode d'Euler.
            T=t+(i*p);

            if(T_max<T)
            {
                T_max=T;
            }

            dN[i]=-l*N[i-1];
            N[i]=N[i-1]+(dN[i]*p);
            printf(" %f     %f      %f\n",T,dN[i],N[i]);
            }

            /* ****************************************************** */
            /* sauvegarde des données dans un le fichier donnees.txt  */
            /* ****************************************************** */
            /* demande s'il faut effectuer la sauvegarde */

            int choix;
            printf("(1) Afficher une repr%csentation graphique?\n",130);
            printf("(2) Sauvegarder ces donn%ces dans un fichier?\n",130);
            printf("\nQuel est votre choix?:");
            scanf("%d",&choix);

            switch(choix)
            {
                case 1:
                    {
                         double minX=0;
                         double maxX=T_max;

                         double minY=-5;
                         double maxY=N[0]+10;

                         affiche_courbe(minX,maxX,minY,maxY,N[0],l,0,9,false,false,false,false,false,false);

                    }break;
                case 2:
                    {
                        /* **************************************************** */
                        /*         enregistrement du fichier donnees.txt                               */
                        /* **************************************************** */

                        sortie=fopen("C:\\donnees.txt","wt");           //ouvre ou créer le fichier donnees.txt en mode écriture

                        if(sortie==NULL)                //renvoi un message d'erreur si le fichier n'a pas pu être ouvert ou créé
                        {
                        printf("\nErreur dans la creation du fichier donnees.txt\n");
                        }

                        printf("\nLe fichier donnees.txt a ete correctement ouvert\n");
                        printf("Enregistrement de donnees.txt...\n");

                        /* Enregistrement du fichier */

                        fprintf(sortie,"\n      t            dN/dt                        N\n");
                        fprintf(sortie," %f     %f      %f\n",t,(-l*N[0]),N[0]);

                        for(i=1;i<=n;i++)
                        {
                        T=t+(i*p);
                        dN[i]=-l*N[i-1];
                        N[i]=N[i-1]+(dN[i]*p);
                        fprintf(sortie," %f     %f      %f\n",T,dN[i],N[i]);
                        }

                        fprintf(sortie,"\n****** FIN DE FICHIER ******\n");
                        fclose(sortie);

                        printf("Donn%ces enregistr%ces!\n",130,130);

                        /* **************************************************** */
                        /*         enregistrement du fichier courbe.txt                                  */
                        /* **************************************************** */


                        sortie2=fopen("C:\\courbe.txt", "wt");             //ouvre ou créer le fichier courbe.txt en mode écriture

                        if(sortie2==NULL)               //renvoi un message d'erreur si le fichier n'a pas pu être ouvert ou créé
                        {
                        printf("\nErreur dans la creation du fichier courbe.txt\n");
                        }

                        printf("\nLe fichier courbe.txt a ete correctement ouvert\n");
                        printf("Enregistrement de courbe.txt...\n");

                        fprintf(sortie2,"%f,%f\n",t,N[0]);

                        for(i=1;i<=n;i++)
                        {
                        T=t+(i*p);
                        dN[i]=-l*N[i-1];
                        N[i]=N[i-1]+(dN[i]*p);
                        fprintf(sortie2,"%f,%f\n",T,N[i]);
                        }

                        fclose(sortie2);

                        printf("Donn%ces enregistr%ces!\n",130,130);

                    }break;

            }


    }

}

void Equation_Diff()
{
    int choix_radioactivite,choix_atome;
    float t, l, p, m, T;
    float N[10000], dN[10000];
    char val;
    FILE* sortie = NULL;
    FILE* sortie2 = NULL;

    printf("(1) Calcul de la d%ccroissance radioactive en s%clectionnant un atome parmi ceux les plus suceptibles de se d%csint%cgrer?\n",130,130,130,130);
    printf("(2) Calcul de la d%ccroissance radioactive en param%ctrant les conditions initiales et constante de radioactivit%c?\n",130,138,130);
    printf("\nQuel est votre choix?:");
    scanf("%d",&choix_radioactivite);

    switch(choix_radioactivite)
    {
     case 1:
         {
             printf("Choississez le type d'atome suceptible de se d%csint%cgrer!\n",130,130);
             printf("(1) Hydrog%cne 7\n",138);
             printf("(2) Azote 16\n");
             printf("(3) Fluor 20\n");
             printf("(4) Oxyg%cne 16\n",138);
             printf("(5) Fluor 18\n");
             printf("(6) Radium 224\n");
             printf("(7) Radon 222\n");
             printf("(8) Sodium 22\n");
             printf("(9) Cobalt 60\n");
             printf("(10) Tritium(Hydrog%cne 3)\n",138);
             printf("(11) Strontium 90\n");
             printf("(12) C%csium 137\n",130);
             printf("(13) Radium 226\n");
             printf("(14) Carbone 14\n");
             printf("(15) Chlore 36\n");
             printf("(16) Aluminium 26\n");
             printf("(17) Uranium 235\n");
             printf("(18) Potassium 40\n");
             printf("(19) Uranium 238\n");
             printf("(20) Thorium 232\n");
             printf("(21) Samarium 147\n");
             printf("(22) Osmium 184\n");
             printf("(23) Indium 115\n");
             printf("(24) X%cnon 124\n",130);
             printf("(25) Vanadium 50\n");
             printf("(26) Calcium 48\n");
             printf("(27) Molybd%cne 100\n",138);
             printf("(28) Bismuth 209\n");
             printf("(29) Zirconium 96\n");
             printf("(30) Tellure 130\n");
             printf("(31) Tellure 128\n");
             printf("\nQuel est votre choix?:");
             scanf("%d",&choix_atome);

             switch(choix_atome)
             {
                case 1:
                    {
                        double t_un_demi;
                        t_un_demi=pow(22.2,-23);
                        radioactivite("Hydrogene 7",t_un_demi,true);
                    }break;
                case 2:
                    {
                        double t_un_demi;
                        t_un_demi=7.13;
                        radioactivite("Azote 16",t_un_demi,true);
                    }break;
                case 3:
                    {
                        double t_un_demi;
                        t_un_demi=11.163;
                        radioactivite("Fluor 20",t_un_demi,true);
                    }break;
                case 4:
                    {
                        double t_un_demi;
                        t_un_demi=2.037*60;
                        radioactivite("Oxygene 16",t_un_demi,true);
                    }break;
                case 5:
                    {
                        double t_un_demi;
                        t_un_demi=1.8293*60*60;
                        radioactivite("Fluor 18",t_un_demi,true);
                    }break;

                case 6:
                    {
                        double t_un_demi;
                        t_un_demi=3.62*24*60*60;
                        radioactivite("Radium 224",t_un_demi,true);
                    }break;
                case 7:
                    {
                        double t_un_demi;
                        t_un_demi=3.8235*24*60*60;
                        radioactivite("Radon 222",t_un_demi,true);
                    }break;
                case 8:
                    {
                        double t_un_demi;
                        t_un_demi=2.605*365*24*60*60;
                        radioactivite("Sodium 22",t_un_demi,true);
                    }break;
                case 9:
                    {
                        double t_un_demi;
                        t_un_demi=5.272*365*24*60*60;
                        radioactivite("Cobalt 60",t_un_demi,true);
                    }break;
                case 10:
                    {
                        double t_un_demi;
                        t_un_demi=12.329*365*24*60*60;
                        radioactivite("Tritium(Hydrogene 3)",t_un_demi,true);
                    }break;
                case 11:
                    {
                        double t_un_demi;
                        t_un_demi=28.78*365*24*60*60;
                        radioactivite("Strontium 90",t_un_demi,true);
                    }break;
                case 12:
                    {
                        double t_un_demi;
                        t_un_demi=30.254*365*24*60*60;
                        radioactivite("Cesium 137",t_un_demi,true);
                    }break;
                case 13:
                    {
                        double t_un_demi;
                        t_un_demi=1602*365*24*60*60;
                        radioactivite("Radium 226",t_un_demi,true);
                    }break;
                case 14:
                    {
                        double t_un_demi;
                        t_un_demi=5730*365*24*60*60;
                        radioactivite("Carbone 14",t_un_demi,true);
                    }break;
                case 15:
                    {
                        double t_un_demi;
                        t_un_demi=301000*365*24*60*60;
                        radioactivite("Chlore 36",t_un_demi,true);
                    }break;
                case 16:
                    {
                        double t_un_demi;
                        t_un_demi=717000*365*24*60*60;
                        radioactivite("Aluminium 26",t_un_demi,true);
                    }break;
                case 17:
                    {
                        double t_un_demi;
                        t_un_demi=pow(7040,6)*365*24*60*60;
                        radioactivite("Uranium 235",t_un_demi,true);
                    }break;
                case 18:
                    {
                        double t_un_demi;
                        t_un_demi=pow(12.8,9)*365*24*60*60;
                        radioactivite("Potassium 40",t_un_demi,true);
                    }break;
                case 19:
                    {
                        double t_un_demi;
                        t_un_demi=pow(44.68,9)*365*24*60*60;
                        radioactivite("Uranium 238",t_un_demi,true);
                    }break;
                case 20:
                    {
                        double t_un_demi;
                        t_un_demi=pow(140.5,9)*365*24*60*60;
                        radioactivite("Thorium 232",t_un_demi,true);
                    }break;
                case 21:
                    {
                        double t_un_demi;
                        t_un_demi=pow(1060,9)*365*24*60*60;
                        radioactivite("Samarium 147",t_un_demi,true);
                    }break;
                case 22:
                    {
                        double t_un_demi;
                        t_un_demi=pow(560,12)*365*24*60*60;
                        radioactivite("Osmium 184",t_un_demi,true);
                    }break;
                case 23:
                    {
                        double t_un_demi;
                        t_un_demi=pow(4410,12)*365*24*60*60;
                        radioactivite("Indium 115",t_un_demi,true);
                    }break;
                case 24:
                    {
                        double t_un_demi;
                        t_un_demi=pow(1100,15)*365*24*60*60;
                        radioactivite("Xenon 124",t_un_demi,true);
                    }break;
                case 25:
                    {
                        double t_un_demi;
                        t_un_demi=pow(1400,15)*365*24*60*60;
                        radioactivite("Vanadium 50",t_un_demi,true);
                    }break;
                case 26:
                    {
                        double t_un_demi;
                        t_un_demi=pow(60,18)*365*24*60*60;
                        radioactivite("Calcium 48",t_un_demi,true);
                    }break;
                case 27:
                    {
                        double t_un_demi;
                        t_un_demi=pow(100,18)*365*24*60*60;
                        radioactivite("Molybdene 100",t_un_demi,true);
                    }break;
                case 28:
                    {
                        double t_un_demi;
                        t_un_demi=pow(210,18)*365*24*60*60;
                        radioactivite("Bismuth 209",t_un_demi,true);
                    }break;
                case 29:
                    {
                        double t_un_demi;
                        t_un_demi=pow(380,18)*365*24*60*60;
                        radioactivite("Zirconium 96",t_un_demi,true);
                    }break;
                case 30:
                    {
                        double t_un_demi;
                        t_un_demi=pow(7900,18)*365*24*60*60;
                        radioactivite("Tellure 130",t_un_demi,true);
                    }break;
                case 31:
                    {
                        double t_un_demi;
                        t_un_demi=pow(22,24)*365*24*60*60;
                        radioactivite("Tellure 128",t_un_demi,true);
                    }break;
             }
         }break;
     case 2:
         {

          radioactivite("",0,false);

         }break;

    }


}

void binome_de_newton()
{
   long int a, b, n, i, coeff,somme_coeff=0;
   int choix,choix_c;

   printf("(1) Calcul du bin%cme de Newton du type (a+b)^n\n",147);
   printf("(2) Calcul du bin%cme de Newton du type f(x)=(a+b)^x \n   (Pour mod%cliser graphiquement sous forme d'escalier le bin%cme de Newton pour chaque valeur x enti%cre!)\n",147,130,147,138);
   printf("(3) Calcul du bin%cme de Newton du type f(x)={Somme de k=0 jusqu'%c n[(k parmi n)a^(n-k)*b^(k)]} \n   (Pour mod%cliser graphiquement sous forme d'escalier la somme des n termes pour chaque valeur x enti%cre!)\n",147,133,130,138);
   printf("(4) D%cmonstration du bin%cme de Newton\n",130,147);
   printf("Quel est votre choix?:");
   scanf("%d",&choix);

   switch(choix)
   {
        case 1:
        {
            printf("Calcul du bin%cme de Newton (a+b)^n",147);
            printf("\nTaper le param%ctre a:",138);
            scanf("%d",&a);
            printf("\nTaper le param%ctre b:",138);
            scanf("%d",&b);
            printf("\nTaper le param%ctre n:",138);
            scanf("%d",&n);

            for(i=0;i<=n;i++)
            {
            coeff=a_parmi_b(i,n)*pow(b,i)*pow(a,(n-i));
            somme_coeff=somme_coeff+coeff;

                if(coeff!=1) printf("%d",coeff);
                else printf("");

                if((n-i)==1) printf("");
                else if((n-i)!=0) printf("^%d",n-i);
                else printf("");

                if((n-i)!=0) printf("+");
            }

            printf("\nValeur du bin%cme de Newton:(%i+%i)^%i=%i",147,a,b,n,somme_coeff);
        }break;
         case 2:
        {
            double minX,maxX,minY,maxY;

            printf("Calcul du bin%cme de Newton (a+b)^x",147);
            printf("\nTaper le param%ctre a:",138);
            scanf("%d",&a);
            printf("\nTaper le param%ctre b:",138);
            scanf("%d",&b);
            printf("\nTaper le param%ctre x:",138);
            scanf("%d",&n);

            printf("Somme des x termes...=");
            for(i=0;i<=n;i++)
            {
            coeff=a_parmi_b(i,n)*pow(b,i)*pow(a,(n-i));
            somme_coeff=somme_coeff+coeff;

            if(coeff!=1) printf("%d",coeff);
            else printf("");

            if((n-i)==1) printf("");
            else if((n-i)!=0) printf("^%d",n-i);
            else printf("");

            if((n-i)!=0) printf("+");
            }

            printf("\nValeur du bin%cme de Newton:(%i+%i)^%i=%i",147,a,b,n,somme_coeff);


            printf("\n(1) Afficher une repr%csentation graphique de la fonction f(x)=(a+b)^x pour x=%i?\n",130,n);
            scanf("%d",&choix_c);

            switch(choix_c)
            {
                case 1:
                {
                      minX=-1;
                      maxX=n+1;

                      double maxY=f_binome_de_newton(n,0,a,b,2);

                    affiche_courbe(minX,maxX,0,maxY,a,b,n,2,true,false,false,false,true,true);
                }
            }

        }break;
        case 3:
        {
            double minX,maxX,minY,maxY;

            printf("Calcul du bin%cme de Newton (a+b)^x",147);
            printf("\nTaper le param%ctre a:",138);
            scanf("%d",&a);
            printf("\nTaper le param%ctre b:",138);
            scanf("%d",&b);
            printf("\nTaper le param%ctre x:",138);
            scanf("%d",&n);

            printf("Somme des x termes...=");
            for(i=0;i<=n;i++)
            {
            coeff=a_parmi_b(i,n)*pow(b,i)*pow(a,(n-i));
            somme_coeff=somme_coeff+coeff;

            if(coeff!=1) printf("%d",coeff);
            else printf("");

            if((n-i)==1) printf("");
            else if((n-i)!=0) printf("^%d",n-i);
            else printf("");

            if((n-i)!=0) printf("+");
            }

            printf("\nValeur du bin%cme de Newton:(%i+%i)^%i=%i",147,a,b,n,somme_coeff);

            if(a>b)
            {
                printf("\nEtant donn%c a>b la repr%csentation graphique sera sous forme d'escalier %c droite pour des valeurs x>3!",130,130,133);
            }
            else if(a<b)
            {
                printf("\nEtant donn%c a<b la repr%csentation graphique sera sous forme d'escalier %c gauche pour des valeurs x>3!",130,130,133);
            }
            else if(b==a)
            {
                printf("\nEtant donn%c a=b la repr%csentation graphique sera sous forme d'escalier %cquilibr%c %c droite et %c gauche pour des valeurs x>3!",130,130,130,130,133,133);
            }

            printf("\n(1) Afficher une repr%csentation graphique de la somme des x termes..?\n",130,a,b,n,somme_coeff);
            scanf("%d",&choix_c);

            switch(choix_c)
            {
                case 1:
                {
                      minX=0;
                      maxX=n;

                    affiche_courbe(minX,maxX,0,somme_coeff,a,b,n,1,true,false,false,false,true,false);
                }
            }

        }break;
        case 4:
        {
             printf("Il s'agit de d%cmontrer par r%ccurrence au rang n+1 que (a+b)^n={Somme de k=0 jusqu'%c n[(k parmi n)a^(n-k)*b^(k)]}",130,130,133);
             printf("Initialisation Pour n=0, (a+b)^0=1=(0 parmi 0)a^0*b^0 donc H0 est vraie au rang n=1.\n");
             printf("Supposons l'hypoth%cse de r%ccurrence vraie au rang n+1 ==> (a+b)^(n+1)=(a+b)*(a+b)^n.\n",138,130);
             printf("\nOn part donc (a+b)^(n+1) ==> (a+b)*(a+b)^n \n=(a+b){Somme de k=0 jusqu'%c n[(k parmi n)a^(n-k)*b^k]}\n=a{Somme de k=0 jusqu'%c n[(k parmi n)a^(n-k)*b^k]}+b{Somme de k=0 jusqu'%c n[(k parmi n)a^(n-k)*b^k]}\n={Somme de k=0 jusqu'%c n[(k parmi n)a^(n-k+1)*b^k]}+{Somme de k=0 jusqu'%c n[(k parmi n)a^(n-k)*b^(k+1)]}\n={Somme de k=0 jusqu'%c n[(k parmi n)a^(n-k+1)*b^k]}+{Somme de k=1 jusqu'%c n+1[(k-1 parmi n)a^(n-(k-1))b^((k-1)+1)]}\n=(0 parmi 0)a^(n+1)*b^0+{Somme de k=1 jusqu'%c n[(k parmi n)a^(n+1-k)*b^k+(n parmi n)a^0*b^(n+1)]}+{Somme de k=1 jusqu'%c n[(k-1 parmi n)a^(n+1-k)b^k]}\n=(0 parmi 0)a^(n+1)*b^0+(n+1 parmi n+1)a^0*b^(n+1)+{Somme de k=1 jusqu'%c n[((k parmi n)+(k-1 parmi n))a^(n+1-k)*b^k]}",133,133,133,133,133,133,133,133,133,133);
             printf("\n\nComme (k parmi n+1)=(k parmi n)+(k-1 parmi n):\n(a+b)^(n+1)=(0 parmi 0)a^(n+1)*b^0+(n+1 parmi n+1)a^0*b^(n+1)+{Somme de k=1 jusqu'%c n[(k parmi (n-1)))a^(n+1-k)*b^k\n={Somme de k=0 jusqu'%c n+1[(k parmi n+1)a^(n+1-k)*b^k \nPar cons%cquent, Un => Un+1.",133,133,130);
             printf("\n\nConclusion: Pour tout n appartenant %c l'ensemble des entiers relatifs, Un est vraie : nous venons de d%cmontrer la formule du bin%cme de Newton!",133,130,147);
        }break;
   }

}

int main(int argc, char *argv[])
{
  	int position,choix=-1,choix1=-1,choix1_2=-1,choix1_1=-1,choix_eq=-1,N,i=1;		/*Déclaration des variables*/
   	float Xi[MAX],Yi[MAX],result[10];
	float ProduitXiYi[MAX];
	float carre_ecart_a_moyenne_Xi[MAX];
	float carre_ecart_a_moyenne_Yi[MAX];

    /*Appel de la fonction d'affichage d'en-tête*/

	entete();

    /********/
    /* MENU */
    /********/

    while(choix1_1!=0)
    {
    freopen("CON", "w", stdout); // redirects stdout
    freopen("CON", "w", stderr); // redirects stderr

	titre("Menu Principal:");

    printf("\n(1) Calcul d'int%cgral + Repr%csentation graphique.",130,130);
    printf("\n(2) Saisir des donn%ces statistiques et calcul de la droite de r%cgression lin%caire.",130,130,130);
    printf("\n(3) Calcul de probabilit%c(Loi de bernouilli de param%ctre n et k).",130,138);
    printf("\n(4) Calcul des coefficients de B%czouts!",130);
    printf("\n(5) Calcul vectorielle dans un plan!",130);
    printf("\n(6) R%csolution d'%cquation!",130,130);
    printf("\n(7) Bin%cme de Newton!",147);
    printf("\n(8) Autres fonctions utiles!");
    printf("\n(9) S'abonner et suivre les derni%cres nouvelles de Vertin Go Website!",138);
    printf("\n(0) Quitter le programme.");
    printf("\n\n Quel est votre choix?:");
    scanf("%d",&choix1_1);

	switch(choix1_1)
	{
        case 1:
	    {
	        Calcul_Integral(false,result);
	    }
        case 2:
	    {

	        while(choix!=0)
            {

	        titre("Menu:");

	        printf("\nEntrez le num%cro de l\'op%cration d%csir%ce:\n",130,130,130,130);
            printf("\n(1) Entrer o%c modifier les donn%ces (Xi et Yi).",151,130);
            printf("\n(2) D%cterminer l\'%cquation de la droite",130,130);
            printf("\n(3) Afficher le tableau des valeurs interm%cdiaires.",130);
            printf("\n(4) Afficher les r%csultats.",130);
            printf("\n(5) Sauvegarder les donn%ces dans un fichier.",130);
            printf("\n(6) Calcul int%cgral + Repr%csentation graphique de la droite de r%cgression lin%caire.",130,130,130,130);
            printf("\n(7) S'abonner et suivre les derni%cres nouvelles de Vertin Go Website!",138);
            //printf("\n(8) Revenir au menu principal.",130);
            printf("\n\nQuel est votre choix?:");
            scanf("%d",&choix);

            switch(choix)
            {
                case 1:
                {	choix1=-1;choix1_2=-1;

                    while(choix1!=0)
                    {
                        titre("Menu Donnees:");
                        printf("\nEntrez le num%cro de l\'op%cration d%csir%ce:\n",130,130,130,130);
                        printf("\n(1) Entrer des nouvelles valeurs.");
                        printf("\n(2) Modifier les valeurs existantes.");
                        printf("\n(3) Revenir au menu pr%cc%cdent.",130,130);
                        printf("\n(0) Quitter le programme.");
                        printf("\n\nQuel est votre choix?:");
                        scanf("%d",&choix1);


                        switch(choix1)
                        {
                            case 1:
							{
								titre("Donnees:");/*Fonction d'affichage de titre*/

								/*Appel de la fonction d'entrée du nombre d'élement*/

								N=nbrelement();

								i=1;

								/*Entree des élements Xi*/

								titre("Entrez des valeurs de Xi:");/*Fonction d'affichage de titre*/

								while(i<(N+1))
								{
									printf("Entrez la valeur de X%d: ",i);
									scanf("%f",&Xi[i]);i++;
								};

								i=1;

								/*Entree des élements Yi*/

								titre("Entrez des valeurs de Yi:");/*Fonction d'affichage de titre*/

								while (i<(N+1))
								{
									printf("Entrez la valeur de Y%d: ",i);
									scanf("%f",&Yi[i]);i++;
								}
								printf("\nTappez une touche pour revenir au menu pr%cc%cdant:",130,130);
								getchar();
								getchar();
								printf("\n\n");

							};break;

                            case 2:
							{
								choix1_2=-1;

								while(choix1_2!=0)
								{
									titre("Menu Modification Donnees");
									printf("\nEntrez le num%cro de l\'op%cration d%csir%ce:\n",130,130,130,130);
									printf("\n(1) Modifier un %cl%cment des Xi.",130,130);
									printf("\n(2) Modifier un %cl%cment des Yi.",130,130);
									printf("\n(3) Revenir au menu pr%cc%cdant.",130,130);
									printf("\n(4) Revenir au menu statistiques.");
									printf("\n(0) Quitter le programme.");
									printf("\n\n Quel est votre choix? :");
									scanf("%d",&choix1_2);

									switch (choix1_2)
									{
										case 1:
											{
												titre("Modification d'un element des Xi:");
												printf("Entrez la position de l\'%cl%cment dans le tableau:",130,130);
												scanf("%d",&position);
												printf("\nEntrez la nouvelle valeur de X%d:",position);
												scanf("%lf",&Xi[position]);
												printf("\n Modification %cffectu%ce...\n",130,130);

											};break;
										case 2:
											{
												printf("\n\nEntrez la position de l\'%cl%cment dans le tableau:",130,130);
												scanf("%d",&position);
												printf("\nEntrez la nouvelle valeur de Y%d:",position);
												scanf("%lf",&Yi[position]);
												printf("\n Modification %cffectu%ce...\n",130,130);

											};break;
										case 3:choix1=-1;choix1_2=0;break;
										case 4:choix1_2=0;choix1=0;choix=-1;break;
										case 0:choix1=0;choix1_2=0;break;
										default:;break;
									}
								}

							};break;

						case 3:choix=-1;choix1=0;break;
						case 0:choix=0;choix1=0;break;
						default:printf("\n Entr%ce non valide!");break;
					}
				}

                };break;

                case 2:
                {
				/*Appel de la fonction de regression linéaire*/

				regression(Xi,Yi,N,result,ProduitXiYi,carre_ecart_a_moyenne_Xi,carre_ecart_a_moyenne_Yi);

				printf("\nOp%Cration termin%ce...\n",130,130);

				/*Affichage de l'éqation et de la corrélation "r"*/

				aff_equation(result);

				printf("\nCoefficient de corr%clation:=> r = %lf\n\n",130,result[9]);
				printf("Tappez une touche pour revenir au menu pr%cc%cdant:",130,130);
				getchar();
				getchar();
				printf("\n\n");

                };break;

                case 3:
                {
				/*Affichage du tableau des resultats*/

				affich_tab(result,Xi,Yi,ProduitXiYi,carre_ecart_a_moyenne_Xi,carre_ecart_a_moyenne_Yi,N);
				printf("\nTappez une touche pour revenir au menu pr%cc%cdant:",130,130);
				getchar();
				getchar();
				printf("\n\n");

                };break;

                case 4:
                {
				/*Affichage des résultats*/

				affichage(result);
				printf("\nTappez une touche pour revenir au menu pr%cc%cdant:",130,130);
				getchar();

                };break;

                case 5:
                {
				fichier(result,Xi,Yi,ProduitXiYi,carre_ecart_a_moyenne_Xi,carre_ecart_a_moyenne_Yi,N);
				printf("\nTappez une touche pour revenir au menu pr%cc%cdant:",130,130);
				getchar();
                }
                case 6:
                {
				Calcul_Integral(true,result);
				getchar();
                }
                case 7:
                {
                system("start chrome.exe https://www.youtube.com/channel/UC2g_-ipVjit6ZlACPWG4JvA?sub_confirmation=1");
                getchar();
                }
                case 8:
                {
                choix1_1=-1;choix=0;break;
                }

                case 0:;break;

                default:printf("\nEntr%ce non valide!\n",130);break;
                getchar();
                };
            }
	    }
	    case 3:
	    {
            bernouilli();
	        getchar();
	        break;
	    }
        case 4:
	    {
            bezout();
	        getchar();
	        break;
	    }
        case 5:
	    {
            menuvecteurs();
	        getchar();
	        break;
	    }
	    case 6:
	    {
	        choix_eq=-1;

	        while(choix_eq!=0)
                {
                    titre("Menu Resolution d'equation");
                    printf("\nEntrez le num%cro de l\'op%cration d%csir%ce:\n",130,130,130,130);
                    printf("\n(1) R%csolution d'une %cquation du second degr%c.",130,130,130);
                    printf("\n(2) Param%ctrer et repr%csenter graphiquement une %cquation de cercle.",138,130,130);
                    printf("\n(3) R%csolution d'une %cquation diff%crentielle(Calcul de la d%ccroissance radioactive!)",130,130,130,130);
                    printf("\n\nQuel est votre choix?:");
                    scanf("%d",&choix_eq);

                    switch(choix_eq)
                          {
                          case 1:
                               {
                                   Second_Degre();
                                   getchar();
	                               break;
                               }break;
                          case 2:
                               {
                                   Cercle();
                                   getchar();
	                               break;
                               }break;
                          case 3:
                               {
                                   Equation_Diff();
                                   getchar();
	                               break;
                               }break;
                          }

                }

	    }
	    case 7:
	    {
            binome_de_newton();
	        getchar();
	        break;
	    }
	    case 8:
	    {
            menuoutils();
	        getchar();
	        break;
	    }
        case 9:
	    {
	        system("start chrome.exe https://www.youtube.com/channel/UC2g_-ipVjit6ZlACPWG4JvA?sub_confirmation=1");
	        getchar();
	        break;
	    }
	};

}
	getchar();
}
