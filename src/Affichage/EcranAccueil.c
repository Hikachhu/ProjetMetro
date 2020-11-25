#include "../../Structure.h"

// --------------------------------------------------------------------------------------
// Simulateur de gare
// Code réalisé par Morin Florian et Raphaël PtitHaddad
// Réalisé dans le cadre du projet de 1er Semestre de 3eme année de l'ESIEA
// https://github.com/Hikachhu/ProjetMetro
//
// Fonctions d'écran d'accueil
// --------------------------------------------------------------------------------------

// Fonction d'affichage d'écran d'accueil avec explication de son fonctionnement
int AffichageEcranAccueil(){
	int taille=10,milieu=COLS/2;
	erase();
	int max=0;
	int mode=-1;
	char *ListeLigne[10]={		"Bienvenu dans ce simulateur de station de metro",
								"Ce programme fonctionne grâce à un système de tour par tour.",
								"Chaque tour le train se déplace d'une portion de case et les personnages d'une case autour d'eux",
								"Chaque personnage peut se deplacer sur les 8 cases autour de lui ou alors ne pas bouger, donc 9 possibilites",
								"Pour controler un personnage vous devez dabord donner sa lettre correspondante puis sa direction",
								"Pour choisir une direction vous devrez utilisez une des lettres suivantes [a,z,e,q,s,d,w,x,c]",
								"Vous devrez choisir la direction comme si le personnage étant sur la lettre s",
								"Si par exemple vous voulez aller en haut à droite vous devez appuyez sur e",
								"Vous pouvez voir la correspondance de matrice ci-dessous pour mieux comprendre",
								"Appuyez sur nimporte quelle touche pour continuer"
							};
	for(int i =0;i<taille;i++){
		if(max<strlen(ListeLigne[i]))max=strlen(ListeLigne[i]);
	}
	for(int i=0;i<taille;i++){
		mvprintw(10+i,milieu-(int)(max/2)+(int)(max-strlen(ListeLigne[i]))/2,"%s",ListeLigne[i]);
	}
	mvprintw(taille+18,milieu-37,"--------------------------     -------------------------------------------");
	mvprintw(taille+19,milieu-37,"|   a    |   z   |   e   |     | haut gauche | haut simple | haut droite |");
	mvprintw(taille+20,milieu-37,"--------------------------     -------------------------------------------");
	mvprintw(taille+21,milieu-37,"|   q    |   s   |   d   |  -> |    gauche   |  statique   |    droite   |");
	mvprintw(taille+22,milieu-37,"--------------------------     -------------------------------------------");
	mvprintw(taille+23,milieu-37,"|   w    |   x   |   c   |     | bas gauche  | bas simple  | bas droite  |");
	mvprintw(taille+24,milieu-37,"--------------------------     -------------------------------------------");

	do{
		mvprintw(taille+10,50,"Choix mode");
		mvprintw(taille+11,50,"0=train seul");
		mvprintw(taille+12,50,"1=Deplacement personnage sans choix de personnage a selectionner");
		mvprintw(taille+13,50,"2=Deplacement personnage avec choix personnage haut dispo");
		mvprintw(taille+14,50,"3=Deplacement personnage avec choix personnage bas dispo");
		mvprintw(taille+15,50,"4=Deplacement personnage avec choix personnage haut et bas dispo");
		mvprintw(taille+16,49," ");
		refresh();
		scanw("%d",&mode);
	}while(!(mode>=0&&mode<=4));
	erase();
	return mode;
}