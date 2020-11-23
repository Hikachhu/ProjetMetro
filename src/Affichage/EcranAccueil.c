#include "../../Structure.h"

// --------------------------------------------------------------------------------------
// Simulateur de gare
// Code réalisé par Morin Florian et Raphaël PtitHaddad
// Réalisé dans le cadre du projet de 1er Semestre de 3eme année de l'ESIEA
//
// Fonctions d'écran d'accueil
// --------------------------------------------------------------------------------------

// Fonction d'affichage d'écran d'accueil avec explication de son fonctionnement
int AffichageEcranAccueil(){
	erase();
	int max=0;
	int mode=-1;
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
	do{
		mvprintw(19,50,"Choix mode");
		mvprintw(20,50,"0=train seul");
		mvprintw(21,50,"1=Deplacement personnage sans choix de personnage a selectionner");
		mvprintw(22,50,"2=Deplacement personnage avec choix personnage haut dispo");
		mvprintw(23,50,"3=Deplacement personnage avec choix personnage bas dispo");
		mvprintw(24,50,"4=Deplacement personnage avec choix personnage haut et bas dispo");
		mvprintw(25,50,"%3d",mode);
		refresh();
		scanf("%d",&mode);
	}while(!(mode>=0&&mode<=4));
	mvprintw(26,50,"%d",mode);
	refresh();
	getch();
	erase();
	return mode;
}