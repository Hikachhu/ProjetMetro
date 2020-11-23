#include "Includes/Affichage/AffichageGare.h"
#include "Includes/Affichage/FonctionsUtiles.h"
#include "Includes/Affichage/EcranAccueil.h"

#include "Includes/ListeChaine/ListePersonnages.h"
#include "Includes/ListeChaine/ListeCoordonnes.h"
#include "Includes/ListeChaine/Train.h"

#include "Includes/TourParTour/TourParTour.h"

// --------------------------------------------------------------------------------------
// Simulateur de gare
// Code réalisé par Morin Florian et Raphaël PtitHaddad
// Réalisé dans le cadre du projet de 1er Semestre de 3eme année de l'ESIEA
//
// Fonction de fonctionnement des gares et main
// --------------------------------------------------------------------------------------

void FonctionnementEnsembleGare(int mode){
  Limitation *Limite=malloc(2*sizeof(Limite));



  //Délimitations des bords des gares dans une structures pour les passer en parametre
  Limite[0].DebutX=3;
  Limite[0].FinX=Limite[0].DebutX+7;
  Limite[0].DebutY=16;
  Limite[0].FinY=141;
  Limite[1].DebutX=27;
  Limite[1].FinX=Limite[1].DebutX+8;
  Limite[1].DebutY=16;
  Limite[1].FinY=141;

  //Ensemble des entete de structure contenant les trains, les personnages et les listes de positions pour leurs déplacements
  Train *TrainGeneral=CreationTrain(Limite);
  EnteteListePersonnages *TeteListe=Init_List_Perso();
  EnteteListeCoordonnes *ListePositionImpossible=Init_List_Coord();
  EnteteListeCoordonnes *ListePositionGare =Init_List_Coord();
  

  Add_Coord_Gare(&ListePositionGare[0],&Limite[0]);
  Add_Coord_Gare(&ListePositionGare[1],&Limite[1]);

  //Affichage des portes des trains
  AffichageTrain(&TrainGeneral[0]);
  AffichageTrain(&TrainGeneral[1]);

  if(mode!=0){
    //Création de la liste des personnages de la gare du haut
    for (int i = 0; i < 26; i++){
      Add_Perso_In_List(&TeteListe[0],i,(rand()%(Limite[0].FinX-Limite[0].DebutX-2))+Limite[0].DebutX+2,(rand()%(Limite[0].FinY-Limite[0].DebutY-1))+1+Limite[0].DebutY,0);
    }

    //Création de la liste des personnages de la gare du bas
    for (int i = 0; i < 26; i++){
      Add_Perso_In_List(&TeteListe[1],i,(rand()%(Limite[1].FinX-Limite[1].DebutX-2))+Limite[1].DebutX+2,(rand()%(Limite[1].FinY-Limite[1].DebutY-1))+1+Limite[1].DebutY,0);
    }
  }

  //Appel de la fonctionne réalisant les tour de chaque déplacement de train de personnage
  for(int i=0;i<6&&((TeteListe[0].PremierPersonnage!=NULL&&TeteListe[1].PremierPersonnage!=NULL)||(mode==0));i++){

    TourParTour(TeteListe,17,TrainGeneral,ListePositionImpossible,Limite,mode);
  } 

  if(TeteListe[0].PremierPersonnage!=NULL&&mode!=0)
    Free_List_Perso(&TeteListe[0]);
  else
    mvprintw(32,0,"VIDE");
  refresh();
  getch();

}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  setlocale(LC_ALL,"");
  initscr();
  start_color();

  init_pair(1,COLOR_WHITE,COLOR_BLACK);
  init_pair(2,COLOR_RED,COLOR_BLACK);
  attron(COLOR_PAIR(1));
  if(COLS>192){
    int mode=AffichageEcranAccueil();

    char **metro = initialisation_metro();

    char metro_txt[] = "Texture/metro";

    //Affichage de la Gare depuis le fichier txt
    remplissage_mat(metro, metro_txt);
    affichage(metro ,metro_txt, 0, 0, 0);

    //Boucle principale servant à manipuler les structures d'informations afin de faire
    //fonctionner les deux gares ensemble
    FonctionnementEnsembleGare(mode);

    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(1));
  }else{
    mvprintw(0,0,"Votre taille d'écran est trop petite, minimal = 192, votre taille =%d",COLS);
    refresh();
    getch();
  }
  endwin();

return 0;
}

