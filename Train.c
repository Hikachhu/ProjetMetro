#include "Structure.h"

Train* CreationTrain(int NbGare){
  Train *TrainActuel=malloc(sizeof(Train));
  for(int a=0;a<8;a++){
    TrainActuel->PositionPorte[a]=malloc(sizeof(Coordonnes));
  }
  int XGeneral;
  if(NbGare==1)XGeneral=11;
  else XGeneral=13;
  int Position[4]={20,40,60,80};
  for(int a=0;a<4;a++){
    TrainActuel->PositionPorte[a*2]->x=XGeneral;
    TrainActuel->PositionPorte[a*2]->y=Position[a];
    TrainActuel->PositionPorte[(a*2)+1]->x=XGeneral;
    TrainActuel->PositionPorte[(a*2)+1]->y=Position[a]+1;
  }
  return TrainActuel;
}

void AffichageTrain(Train *TrainActuel){
  for (int a = 0; a < 4; a++){
    mvprintw(TrainActuel->PositionPorte[a*2]->x,TrainActuel->PositionPorte[a*2]->y+1,"G");
    mvprintw(TrainActuel->PositionPorte[a*2+1]->x,TrainActuel->PositionPorte[a*2+1]->y+1,"D");
    refresh();
  }
}

void TrouveTrain(Personnage *PersonnageActuel,Train* TrainActuel,Limitation *Limite){
  int TXAvant,TXActuel,TXApres,TY,PX,PY;
  TY=TXActuel=TrainActuel->PositionPorte[0]->x;
  PX=PersonnageActuel->PositionActuel->y;
  PY=PersonnageActuel->PositionActuel->x;
  for(int a=0;a<8;a++){
    TXActuel=TrainActuel->PositionPorte[a]->y;
    if(a==0){
      TXAvant=Limite->DebutX;
    }
    else{
      TXAvant=((TrainActuel->PositionPorte[a-1]->y)+(TXActuel))/2;
    }
    if(a==7){
      TXApres=Limite->FinX;
    }
    else{
      TXApres=((TrainActuel->PositionPorte[a+1]->y)+(TXActuel))/2;
    }
    if(TXActuel==PX){
      PersonnageActuel->Direction->y=0;
    }else if(TXAvant<PX&&PX<TXActuel){
      PersonnageActuel->Direction->y=1;
    }else if(TXActuel<PX && PX<TXApres){
      PersonnageActuel->Direction->y=-1;
    }
    if(TY>PY){
      PersonnageActuel->Direction->x=1;
    }else{
      PersonnageActuel->Direction->x=-1;
    }
  }
}

void ChoixDirectionTrain(EnteteListePersonnages *EnteteListeDesPersonnages,Train *TrainActuel,Limitation *Limite){
  ElementListePersonnages *Actuel=EnteteListeDesPersonnages->PremierPersonnage;
  Personnage *PersonnageActuel=NULL;
  do{
    PersonnageActuel=Actuel->Usager;
    TrouveTrain(PersonnageActuel,TrainActuel,Limite);
    Actuel=Actuel->Suivant;
  }while(Actuel!=NULL);

}

void AfficheCoordonnesTrain(Train *TrainActuel){
  for(int i=0;i<8;i++){
    mvprintw(30+i,1,"%d x:%d y:%d",i,TrainActuel->PositionPorte[i]->x,TrainActuel->PositionPorte[i]->y);
  }
  refresh();
}