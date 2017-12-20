#ifndef INTERPRETEUR_C_H

#define INTERPRETEUR_C_H

/*
Fichier : interpreteur_c.h
--------------------------
    Fichier d'en-tete pour l'implementation (interpreteur.c) uniquement
    Contient :
        Les prototypes de fonctions utilisees dans interpreteur.c
        La definition des types utilises dans interpreteur.c
*/

typedef int    BOOL     ;
#define        FALSE    0
#define        TRUE     1

typedef enum OPERATIONS {
	/* Fonction invalide */
	INVALIDF = -1,

	/* 1. Delimiteurs de bloc*/
	P_O, P_F, END,

	/* 2. Operateurs arithmetiques */
	PLUS, MOINS, FOIS, DIV, POW,

	/* 3. Fonctions */
	OPP, SIN, COS, TAN, ABS, RACINE, LOG, LOG10, EXP,
}OPERATION;

#define NB_OPERATIONS 17

typedef enum PRIORITY_LEVELS {
	PRIOR_P_F,
	PRIOR_P_O,
	PRIOR_END,
	PRIOR_PLUS_MOINS,
	PRIOR_FOIS_DIV,
	PRIOR_FONCTION,
	PRIOR_POW
}PRIORITY_LEVEL;

typedef enum TYPES_ASSOCIATIVITE {
	GAUCHE, DROITE
}TYPE_ASSOCIATIVITE;

typedef double (*F1VAR)(double);
typedef double (*F2VAR)(double, double);

typedef struct tagOPERATIONINFO {
	/********************************************\
	* Une operation est definie par sa priorite, *
	* son associativite,                         *
	* le nombres d'arguments qu'elle requiert    *
	* l'adresse de la fonction en question       *
	\********************************************/
	PRIORITY_LEVEL        priorite;
	TYPE_ASSOCIATIVITE    associativite;
	size_t                nbArgs;
	void *                p_fonction;
}OPERATIONINFO;

OPERATIONINFO TabOperations[NB_OPERATIONS];

int     EnleverEspaces(char * lpszString);
BOOL    IsSeparator(int c);
int     EmpilerMot(char * lpMot, size_t cchMot, LPPARAM lpParams, size_t nbParams);
int     EmpilerSep(int c);
int     EmpilerOperande(double x);
int     EmpilerChaine(char * lpszMot, LPPARAM lpParams, size_t nbParams);
int     EmpilerFonction(int f);
int     EmpilerParam(char * lpszParam, LPPARAM lpParams, size_t nbParams);
BOOL    Prioritaire(int operation, int second_operation);
int     Evaluer(void);

double  Somme(double a, double b);
double  Diff(double a, double b);
double  Prod(double a, double b);
double  Div(double a, double b);
double  Pow(double a, double b);
double  Opp(double x);
double  Sin(double x);
double  Cos(double x);
double  Tan(double x);
double  Abs(double x);
double  Racine(double x);
double  Log(double x);
double  Log10(double x);
double  Exp(double x);

int     Ignorer(char const * s, ...);

#define MAX_OPERATIONS    20
#define MAX_OPERANDES     20

struct {
	size_t    NbElements;
	int       t[MAX_OPERATIONS];
}Operations;

struct {
	size_t    NbElements;
	double    t[MAX_OPERANDES];
}Operandes;

#endif


