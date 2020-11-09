#include "AllIncludes.h"

void *FonctionnementGareHaut(){
  Limitation *Limite=malloc(sizeof(Limite));
  Limite->DebutX=0;
  Limite->FinX=9;
  Limite->DebutY=0;
  Limite->FinY=99;
  Train *TrainGeneral=CreationTrain(1);
  EnteteListePersonnages *TeteListe=Init_List_Perso();
  EnteteListeCoordonnes *ListePositionImpossible=Init_List_Coord();
  EnteteListeCoordonnes *ListePositionGare=Init_List_Coord();
  
  AffichageGare(Limite);

  Add_Coord_Gare(ListePositionGare,Limite);

  for (int i = 0; i < 10; i++){
    Add_Perso_In_List(TeteListe,i,(rand()%(Limite->FinX-Limite->DebutX-1))+1,(rand()%(Limite->FinY-Limite->DebutY-1))+1,0);
  }
  for(int i=0;i<6&&TeteListe->PremierPersonnage!=NULL;i++){
    TourParTour(TeteListe,20,(i)%2,TrainGeneral,ListePositionImpossible,Limite);
  }
  if(TeteListe->PremierPersonnage!=NULL)
    Free_List_Perso(TeteListe);
  else
    mvprintw(31,0,"VIDE");
  refresh();
  getch();
  pthread_exit(NULL);
}

void *FonctionnementGareBas(){
  Limitation *Limite=malloc(sizeof(Limite));
  Limite->DebutX=14;
  Limite->FinX=23;
  Limite->DebutY=0;
  Limite->FinY=99;
  Train *TrainGeneral=CreationTrain(2);
  EnteteListePersonnages *TeteListe=Init_List_Perso();
  EnteteListeCoordonnes *ListePositionImpossible=Init_List_Coord();
  EnteteListeCoordonnes *ListePositionGare=Init_List_Coord();
  
  AffichageGare(Limite);

  Add_Coord_Gare(ListePositionGare,Limite);

  for (int i = 0; i < 10; i++){
    Add_Perso_In_List(TeteListe,i,(rand()%(Limite->FinX-Limite->DebutX-1))+1+Limite->DebutX,(rand()%(Limite->FinY-Limite->DebutY-1))+1,0);
  }
  for(int i=0;i<6&&TeteListe->PremierPersonnage!=NULL;i++){
    TourParTour(TeteListe,20,(i)%2,TrainGeneral,ListePositionImpossible,Limite);
  }
  if(TeteListe->PremierPersonnage!=NULL)
    Free_List_Perso(TeteListe);
  else
    mvprintw(31,0,"VIDE");
  refresh();
  getch();
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  setlocale(LC_ALL,"");
  initscr();
  start_color();
  init_pair(1,COLOR_GREEN,COLOR_BLACK);
  attron(COLOR_PAIR(1));

  pthread_t GareHaut;
  pthread_t GareBas;
  // mvprintw(10,50,"TAILLEX:%d TAILLEY:%d",TAILLEX,TAILLEY);


//  pthread_create(&GareHaut,NULL,FonctionnementGareHaut(),NULL);
  pthread_create(&GareBas,NULL,FonctionnementGareBas(),NULL);
  attroff(COLOR_PAIR(1));
  endwin();
  pthread_exit(NULL);

return 0;
}

