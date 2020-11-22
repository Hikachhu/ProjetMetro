#include "../../Structure.h"

// --------------------------------------------------------------------------------------
// Simulateur de gare
// Code réalisé par Morin Florian et Raphaël PtitHaddad
// Réalisé dans le cadre du projet de 1er Semestre de 3eme année de l'ESIEA
//
// Fonctions d'écran d'accueil
// --------------------------------------------------------------------------------------

// Fonction d'affichage d'écran d'accueil avec explication de son fonctionnement
void AffichageEcranAccueil(){
	erase();
	int max=0;
	char *ListeLigne[10]={		"Bienvenu dans ce simu",
								"Ce programme cest du tour par tour",
								"Chaque personnage peut se deplacer sur les 8 cases autour de lui ou alors ne pas bouger, donc 9 possibilites",
								"Pour controler un personnage vous devez dabord donner sa lettre correspondante puis sa direction",
								"Pour choisir une direction vous devrez utilisez une des lettres suivantes [a,z,e,q,s,d,w,x,c]",
								"Vous devrez choisir la direction comme si le personnage étant sur la lettre s",
								"Si par exemple vous voulez aller en haut à droite vous devez appuyez sur e",
								"Appuyez sur nimporte quelle touche pour continuer"
							};
	for(int i =0;i<8;i++){
		if(max<strlen(ListeLigne[i]))max=strlen(ListeLigne[i]);
	}
	for(int i=0;i<8;i++){
		mvprintw(10+i,50+(int)(max-strlen(ListeLigne[i]))/2,"%s",ListeLigne[i]);
	}
	refresh();
	getch();
	erase();
}