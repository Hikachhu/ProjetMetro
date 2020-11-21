#include "Includes/Affichage/AffichageGare.h"
#include "Includes/Affichage/FonctionsUtiles.h"
#include "Includes/Affichage/EcranAccueil.h"

#include "Includes/ListeChaine/ListePersonnages.h"
#include "Includes/ListeChaine/ListeCoordonnes.h"
#include "Includes/ListeChaine/Train.h"

#include "Includes/TourParTour/TourParTour.h"


void FonctionnementEnsembleGare(){
  Limitation *Limite=malloc(2*sizeof(Limite));
  Limite[0].DebutX=3;
  Limite[0].FinX=Limite[0].DebutX+7;
  Limite[0].DebutY=16;
  Limite[0].FinY=141;
  Limite[1].DebutX=27;
  Limite[1].FinX=Limite[1].DebutX+8;
  Limite[1].DebutY=16;
  Limite[1].FinY=141;

  Train *TrainGeneral=CreationTrain(Limite);
  EnteteListePersonnages *TeteListe=Init_List_Perso();
  EnteteListeCoordonnes *ListePositionImpossible=Init_List_Coord();
  EnteteListeCoordonnes *ListePositionGare =Init_List_Coord();
  
  Add_Coord_Gare(&ListePositionGare[0],&Limite[0]);
  Add_Coord_Gare(&ListePositionGare[1],&Limite[1]);


  AffichageTrain(&TrainGeneral[0]);
  AffichageTrain(&TrainGeneral[1]);

  for (int i = 0; i < 26; i++){
    Add_Perso_In_List(&TeteListe[0],i,(rand()%(Limite[0].FinX-Limite[0].DebutX-2))+Limite[0].DebutX+2,(rand()%(Limite[0].FinY-Limite[0].DebutY-1))+1+Limite[0].DebutY,0);
  }

  for (int i = 0; i < 26; i++){
    Add_Perso_In_List(&TeteListe[1],i,(rand()%(Limite[1].FinX-Limite[1].DebutX-2))+Limite[1].DebutX+2,(rand()%(Limite[1].FinY-Limite[1].DebutY-1))+1+Limite[1].DebutY,0);
  }

  for(int i=0;i<6&&TeteListe[0].PremierPersonnage!=NULL&&TeteListe[1].PremierPersonnage!=NULL;i++){
    TourParTour(TeteListe,17,TrainGeneral,ListePositionImpossible,Limite);
  } 
  // if(TeteListe[1].PremierPersonnage!=NULL)
  //   Free_List_Perso(&TeteListe[1]);
  // else
  //   mvprintw(31,0,"VIDE");
  if(TeteListe[0].PremierPersonnage!=NULL)
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
  init_pair(2,COLOR_WHITE,COLOR_BLACK);
  attron(COLOR_PAIR(1));

  AffichageEcranAccueil();

  char **metro = initialisation_metro();

  char metro_txt[] = "Texture/metro";

  remplissage_mat(metro, metro_txt);
  affichage(metro ,metro_txt, 0, 0, 0);

  FonctionnementEnsembleGare();
  attroff(COLOR_PAIR(2));
  attroff(COLOR_PAIR(1));
  endwin();
  pthread_exit(NULL);

return 0;
}

