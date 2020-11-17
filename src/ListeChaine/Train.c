#include "../../Structure.h"

void Verif_Go_In_Train(Train *TrainActuel,ElementListePersonnages *ElemPersonnageActuel,EnteteListePersonnages *EnteteListeDesPersonnages){
//	AfficheCoordonnesTrain(TrainActuel);
	Personnage *PersonnageActuel=NULL;
	ElementListePersonnages *ElementSuivant=NULL;
	do{
		if(PersonnageActuel==NULL){
			ElementSuivant=EnteteListeDesPersonnages->PremierPersonnage;
		}
		PersonnageActuel=ElemPersonnageActuel->Usager;
		ElementSuivant=ElemPersonnageActuel->Suivant;
		// mvprintw(2,150,"perso %c x %d y %2d",PersonnageActuel->ID+'a',PersonnageActuel->PositionActuel->x,PersonnageActuel->PositionActuel->y);
		// refresh();
		// getch();
		for (int i = 0; i < 8&&PersonnageActuel!=NULL; i++){
			if(PersonnageActuel->PositionActuel->y==TrainActuel->PositionPorte[i]->y&&(PersonnageActuel->PositionActuel->x==TrainActuel->PositionPorte[i]->x-2||PersonnageActuel->PositionActuel->x==TrainActuel->PositionPorte[i]->x+2)){
				mvprintw(3+PersonnageActuel->ID,150,"Suppression de %d",PersonnageActuel->ID);
				refresh();
	//			getch();
				if(PersonnageActuel->ID==EnteteListeDesPersonnages->PremierPersonnage->Usager->ID){
					ElementSuivant=ElemPersonnageActuel->Suivant;
					Rm_Elem_List_Perso(EnteteListeDesPersonnages);
				}
				else{
					ElementSuivant=Rm_Elem_List_Perso_Cible(EnteteListeDesPersonnages,PersonnageActuel->ID);
					break;
				}
				refresh();
				if(ElementSuivant==NULL||EnteteListeDesPersonnages->PremierPersonnage!=NULL){
					break;
				}
			}
		}
		
		ElemPersonnageActuel=ElementSuivant;
		
	}while(ElemPersonnageActuel!=NULL&&EnteteListeDesPersonnages->PremierPersonnage!=NULL);
}

Train* CreationTrain(Limitation *Limite){
  Train *TrainActuel=malloc(2*sizeof(Train));
  for(int j=0;j<2;j++){
    for(int a=0;a<8;a++){
      TrainActuel[j].PositionPorte[a]=malloc(sizeof(Coordonnes));
    }
    int XGeneral;
    if(j==1)XGeneral=Limite[1].DebutX;
    else    XGeneral=(Limite[0].FinX+1);
    int Position[4]={20,40,60,80};
    for(int a=0;a<4;a++){
      TrainActuel[j].PositionPorte[a*2]->x=XGeneral;
      TrainActuel[j].PositionPorte[a*2]->y=Position[a];
      TrainActuel[j].PositionPorte[(a*2)+1]->x=XGeneral;
      TrainActuel[j].PositionPorte[(a*2)+1]->y=Position[a]+1;
    }
  }
  return TrainActuel;
}

void AffichageTrain(Train *TrainActuel){
  for (int a = 0; a < 4; a++){
    mvprintw(TrainActuel->PositionPorte[a*2]->x,TrainActuel->PositionPorte[a*2]->y,"G");
    mvprintw(TrainActuel->PositionPorte[a*2+1]->x,TrainActuel->PositionPorte[a*2+1]->y,"D");
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
      TXAvant=Limite->DebutY;
    }
    else{
      TXAvant=((TrainActuel->PositionPorte[a-1]->y)+(TXActuel))/2;
    }

    if(a==7){
      TXApres=Limite->FinY;
    }
    else{
      TXApres=((TrainActuel->PositionPorte[a+1]->y)+(TXActuel))/2;
    }

    if(TXActuel==PX){
      PersonnageActuel->Direction->y=0;
    }else if(TXAvant<=PX&&PX<TXActuel){
      PersonnageActuel->Direction->y=1;
    }else if(TXActuel<PX && PX<=TXApres){
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
    mvprintw(i+14,150,"%d x:%d y:%d",i,TrainActuel->PositionPorte[i]->x,TrainActuel->PositionPorte[i]->y);
  }
  refresh();
  getch();
}