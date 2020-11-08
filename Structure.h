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