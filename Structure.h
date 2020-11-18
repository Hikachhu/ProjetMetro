#ifndef STRUCTURE
	#define STRUCTURE
	#include <fcntl.h>
	#include <locale.h>
	#include <math.h>
	#include <pthread.h>
	#include <ncurses.h>
	#include <signal.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <termios.h>
	#include <time.h>
	#include <unistd.h>
	#include <wchar.h>

	#define TAILLEX 9
	#define TAILLEY 99

	#define HautDebutX 5
	#define HautFinX 10
	#define HautDebutY 16
	#define HautFinY 141
	#define BasDebutX 32
	#define BasFinX 37
	#define BasDebutY
	#define BasFinY


	#define Haut_train 5
	#define Long_train 131

	#define Haut_metro 42
	#define Long_metro 156

	#define vitesse_Train 40000

	#define trainSuivant 20

	typedef struct Limitation Limitation;
	typedef struct Coordonnes Coordonnes;
	typedef struct Personnage Personnage;
	typedef struct ElementListePersonnages ElementListePersonnages;
	typedef struct EnteteListePersonnages EnteteListePersonnages;
	typedef struct ListeCoordonnes ListeCoordonnes;
	typedef struct EnteteListeCoordonnes EnteteListeCoordonnes;
	typedef struct Train Train;


	struct Limitation
	{
		int DebutX;
		int FinX;
		int DebutY;
		int FinY;
		
	};
	struct Coordonnes
	{
		int x;
		int y;
	};

	struct Personnage
	{
		int ID;
		int Type;
		Coordonnes *PositionActuel;
		Coordonnes *Direction;
		Coordonnes *FuturPosition;
	};

	struct ElementListePersonnages
	{
		Personnage *Usager;
		ElementListePersonnages *Suivant;
	};

	struct EnteteListePersonnages
	{
		ElementListePersonnages *PremierPersonnage;
		ElementListePersonnages *DernierPersonnage;
	};

	struct ListeCoordonnes
	{
		Coordonnes *Position;
		ListeCoordonnes *Suivant;
	};

	struct EnteteListeCoordonnes
	{
		ListeCoordonnes *PremiereCoordonnes;
		ListeCoordonnes *DerniereCoordonnes;
	};

	struct Train
	{
		Coordonnes *PositionPorte[8];
	};
#endif