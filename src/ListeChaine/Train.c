#include "../../Structure.h"
#include "../../Includes/ListeChaine/ListePersonnages.h"

// --------------------------------------------------------------------------------------
// Simulateur de gare
// Code réalisé par Morin Florian et Raphaël PtitHaddad
// Réalisé dans le cadre du projet de 1er Semestre de 3eme année de l'ESIEA
// https://github.com/Hikachhu/ProjetMetro
//
// Fonctions relative a la manipulations des personnages vis à vis du train
// --------------------------------------------------------------------------------------

//Fonction de verification si un personnage se trouve a la bonne position pour rentrée par une porte du train
void Verif_Go_In_Train(Train *TrainActuel,ElementListePersonnages *ElemPersonnageActuel,EnteteListePersonnages *EnteteListeDesPersonnages){
	Personnage *PersonnageActuel=NULL;
	ElementListePersonnages *ElementSuivant=NULL;
  //Pour tout les personnages
	do{
		if(PersonnageActuel==NULL){
			ElementSuivant=EnteteListeDesPersonnages->PremierPersonnage;
		}
		PersonnageActuel=ElemPersonnageActuel->Usager;
		ElementSuivant=ElemPersonnageActuel->Suivant;

    //Pour toutes les portes
		for (int i = 0; i < 8&&PersonnageActuel!=NULL; i++){

      //Si le personnage est sur une porte du train
			if(PersonnageActuel->PositionActuel->y==TrainActuel->PositionPorte[i]->y&&(PersonnageActuel->PositionActuel->x==TrainActuel->PositionPorte[i]->x-2||PersonnageActuel->PositionActuel->x==TrainActuel->PositionPorte[i]->x)){
				
        //Si c'est le premier personnage nous supprimons le 1er personnage
        if(PersonnageActuel->ID==EnteteListeDesPersonnages->PremierPersonnage->Usager->ID){
					ElementSuivant=ElemPersonnageActuel->Suivant;
					Rm_Elem_List_Perso(EnteteListeDesPersonnages);
				}
        //Sinon nous supprimons le personnage ciblé par son id
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
    if(j==1)XGeneral=Limite[1].DebutX+2;
    else    XGeneral=(Limite[0].FinX+1);
    int Position[4]={43,65,87,109};
    for(int a=0;a<4;a++){
      TrainActuel[j].PositionPorte[a*2]->x=XGeneral;
      TrainActuel[j].PositionPorte[a*2]->y=Position[a];
      TrainActuel[j].PositionPorte[(a*2)+1]->x=XGeneral;
      TrainActuel[j].PositionPorte[(a*2)+1]->y=Position[a]+1;
    }
  }
  return TrainActuel;
}

//Affiche les portes du train
void AffichageTrain(Train *TrainActuel){
  for (int a = 0; a < 4; a++){
    mvprintw(TrainActuel->PositionPorte[a*2]->x,TrainActuel->PositionPorte[a*2]->y,"G");
    mvprintw(TrainActuel->PositionPorte[a*2+1]->x,TrainActuel->PositionPorte[a*2+1]->y,"D");
    refresh();
  }
}

//Trouve la porte dont le personnage est le plus proche par zone
void TrouveTrain(Personnage *PersonnageActuel,Train* TrainActuel,Limitation *Limite){
  int TXAvant,TXActuel,TXApres,TY,PX,PY;

  TY=TXActuel=TrainActuel->PositionPorte[0]->x;
  PX=PersonnageActuel->PositionActuel->y;
  PY=PersonnageActuel->PositionActuel->x;

  //Pour toutes les protes
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

    //Si le X le personne à le bon x il n'y a pas a faire de déplacement dans ce sens
    if(TXActuel==PX){
      PersonnageActuel->Direction->y=0;
      
      //Si le personnage est proche de la porte actuel par la gauche il va vers la droite
    }else if(TXAvant<=PX&&PX<TXActuel){
      PersonnageActuel->Direction->y=1;

      //De meme pour l'autre sens
    }else if(TXActuel<PX && PX<=TXApres){
      PersonnageActuel->Direction->y=-1;
    }

    //Gestion de la hauteur
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