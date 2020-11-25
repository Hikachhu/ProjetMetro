#include "../../Structure.h"

// --------------------------------------------------------------------------------------
// Simulateur de gare
// Code réalisé par Morin Florian et Raphaël PtitHaddad
// Réalisé dans le cadre du projet de 1er Semestre de 3eme année de l'ESIEA
// https://github.com/Hikachhu/ProjetMetro
//
// Fonctions pour l'affiche et l'effacement des differents personnages
// --------------------------------------------------------------------------------------

//Efface l'ensemble des informations affichée concernant les personnages
void Erase_List_Perso(Personnage *PersonnageActuel){
	int Hauteur=(PersonnageActuel->ID)+15;
  	mvprintw(Hauteur,0,"                                                                                                \n");
}

//Efface visuellement un personnage de la gare
void Erase_In_Gare_Perso_G(Personnage *PersonnageActuel){
	int X=PersonnageActuel->PositionActuel->x+1;
	int Y=PersonnageActuel->PositionActuel->y+1;
	mvprintw(X,Y," ");		
}

//Efface les lignes d'informations des personnages
void Erase_List_Perso_G(){
	for(int i=0;i<10;i++){
		mvprintw(i+15,0,"                                                                                                \n");		
	}
	refresh();
}

//Affichage toute les informations concernant un personnage
void Print_All_Info_Perso_G(Personnage *PersonnageActuel){
	int Hauteur=PersonnageActuel->ID+15;
	mvprintw(Hauteur,0,"adresse %p \tId:%d Type:%d\t PositionActuel[x:%2d y:%2d]\tDirection[x:%2d y:%2d]\tFuturPosition[x:%2d y:%2d]\n",PersonnageActuel,PersonnageActuel->ID,PersonnageActuel->Type,PersonnageActuel->PositionActuel->x,PersonnageActuel->PositionActuel->y,PersonnageActuel->Direction->x,PersonnageActuel->Direction->y,PersonnageActuel->FuturPosition->x,PersonnageActuel->FuturPosition->y);
}

//Affichage les directions d'un personnage
void Print_Direction_Perso_G(Personnage *PersonnageActuel){
	int Hauteur=PersonnageActuel->ID+15;
	mvprintw(Hauteur,0,"Id:%d Type:%d x:%d y:%d\n",PersonnageActuel->ID,PersonnageActuel->Type,PersonnageActuel->Direction->x,PersonnageActuel->Direction->y);
}

//Affichage les futurs position d'un personnage
void Print_Futur_Position_Perso_G(Personnage *PersonnageActuel){
	int Hauteur=PersonnageActuel->ID+15;
	mvprintw(Hauteur,0,"Id:%d Type:%d x:%d y:%d\n",PersonnageActuel->ID,PersonnageActuel->Type,PersonnageActuel->FuturPosition->x,PersonnageActuel->FuturPosition->y);
}

//Affichage un personnage dans la gare
void Print_In_Gare_Perso_G(Personnage *PersonnageActuel){
	int X=PersonnageActuel->PositionActuel->x+1;
	int Y=PersonnageActuel->PositionActuel->y+1;
	mvprintw(X,Y,"%c",PersonnageActuel->ID+'a');	
}

//Affichage les positions d'un personnage
void Print_Position_Perso_G(Personnage *PersonnageActuel){
	int Hauteur=PersonnageActuel->ID+15;
	mvprintw(Hauteur,0,"Id:%d Type:%d x:%d y:%d\n",PersonnageActuel->ID,PersonnageActuel->Type,PersonnageActuel->PositionActuel->x,PersonnageActuel->PositionActuel->y);
}