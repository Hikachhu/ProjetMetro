#include "AllIncludes.h"

void TourParTour(EnteteListePersonnages *Entete,int TourARealise,int PresenceTrain,Train *TrainActuel,EnteteListeCoordonnes *EnteteListeDesCoordonnes,Limitation *Limite){
	if(Entete[0].PremierPersonnage!=NULL&&Entete[1].PremierPersonnage!=NULL){
		for(int NombreDeTour=0;NombreDeTour<TourARealise&&(Entete[0].PremierPersonnage!=NULL||Entete[1].PremierPersonnage!=NULL);NombreDeTour++){
			mvprintw(0,50,"Numero tour = %2d",NombreDeTour);
			refresh();
			
			if(Entete[0].PremierPersonnage!=NULL)Parcours_L_Gene(&Print_In_Gare_Perso_G,&Entete[0]);
			if(Entete[1].PremierPersonnage!=NULL)Parcours_L_Gene(&Print_In_Gare_Perso_G,&Entete[1]);

			if(PresenceTrain==0){
				mvprintw(0,109,"PROCHAIN TRAIN DANS %2d MIN",TourARealise-NombreDeTour);
				if(Entete[0].PremierPersonnage!=NULL)Parcours_L_Gene(&ChoixDirection,&Entete[0]);
				if(Entete[1].PremierPersonnage!=NULL)Parcours_L_Gene(&ChoixDirection,&Entete[1]);
			}
			else{
				mvprintw(0,109,"TRAIN EN STATION           ");
				if(Entete[0].PremierPersonnage!=NULL)ChoixDirectionTrain(&Entete[0],&TrainActuel[0],&Limite[0]);
				if(Entete[1].PremierPersonnage!=NULL)ChoixDirectionTrain(&Entete[1],&TrainActuel[1],&Limite[1]);
			}
			getch();
			if(Entete[0].PremierPersonnage!=NULL)Parcours_L_Gene(&Erase_In_Gare_Perso_G,&Entete[0]);
			if(Entete[1].PremierPersonnage!=NULL)Parcours_L_Gene(&Erase_In_Gare_Perso_G,&Entete[1]);

			if(Entete[0].PremierPersonnage!=NULL)Add_Coord_NULL(&Entete[0],&EnteteListeDesCoordonnes[0]);
			if(Entete[1].PremierPersonnage!=NULL)Add_Coord_NULL(&Entete[1],&EnteteListeDesCoordonnes[1]);

			if(Entete[0].PremierPersonnage!=NULL)Add_New_Position(&Entete[0],&EnteteListeDesCoordonnes[0],&Limite[0]);
			if(Entete[1].PremierPersonnage!=NULL)Add_New_Position(&Entete[1],&EnteteListeDesCoordonnes[1],&Limite[1]);
			
			if(PresenceTrain==1){
				if(Entete[0].PremierPersonnage!=NULL)Verif_Go_In_Train(&TrainActuel[0],Entete[0].PremierPersonnage,&Entete[0]);
				if(Entete[1].PremierPersonnage!=NULL)Verif_Go_In_Train(&TrainActuel[1],Entete[1].PremierPersonnage,&Entete[1]);
			}

			if(Entete[0].PremierPersonnage!=NULL)Rm_List_Coord(&EnteteListeDesCoordonnes[0]);
			if(Entete[1].PremierPersonnage!=NULL)Rm_List_Coord(&EnteteListeDesCoordonnes[1]);
		}
		if(Entete->PremierPersonnage==NULL){
			mvprintw(30,0,"TOUT LE MONDE EST DANS LE TRAIN");
		}
		refresh();
	}
}

void ChoixDirection(Personnage *PersonnageActuel){
	PersonnageActuel->Direction->x=random()%3-1;
	PersonnageActuel->Direction->y=random()%3-1;
}

void Add_New_Position(EnteteListePersonnages *EnteteListeDesPersonnages,EnteteListeCoordonnes *EnteteListeDesCoordonnes,Limitation *Limite){
	ElementListePersonnages *ListePersonnages=EnteteListeDesPersonnages->PremierPersonnage;
	Personnage *PersonnageActuel=ListePersonnages->Usager;
	int FuturX=(PersonnageActuel->Direction->x)+(PersonnageActuel->PositionActuel->x);
	int FuturY=(PersonnageActuel->Direction->y)+(PersonnageActuel->PositionActuel->y);
	int PossibiliteDeplacement=0;
	for(ElementListePersonnages *ElementPersonnageParcouru=ListePersonnages;ElementPersonnageParcouru!=NULL;ElementPersonnageParcouru=Parcours_L_Gene_Recur(ListePersonnages,PersonnageActuel->ID,FuturX,FuturY,&PossibiliteDeplacement)){
		PersonnageActuel=ElementPersonnageParcouru->Usager;
		if(PossibiliteDeplacement==0&&Find_Duo_Coord(EnteteListeDesCoordonnes->PremiereCoordonnes,FuturX,FuturY)==0){
			if(FuturX>1+Limite->DebutX&&FuturX<Limite->FinX){
				(PersonnageActuel->FuturPosition->x)=FuturX;
			}
			else{
				(PersonnageActuel->FuturPosition->x)=PersonnageActuel->PositionActuel->x;	
			}
			if(FuturY>1+Limite->DebutY&&FuturY<Limite->FinY){
				(PersonnageActuel->FuturPosition->y)=FuturY;
			}
			else{
				(PersonnageActuel->FuturPosition->y)=PersonnageActuel->PositionActuel->y;	
			}
		}
		else{
			(PersonnageActuel->FuturPosition->x)=(PersonnageActuel->PositionActuel->x);
			(PersonnageActuel->FuturPosition->y)=(PersonnageActuel->PositionActuel->y);
//			mvprintw(10+PersonnageActuel->ID,140,"%d <- NON MOUVEMENT",PersonnageActuel->ID);

		}
		New_Pos_To_Current_Pos(PersonnageActuel);
		refresh();
		PossibiliteDeplacement=0;
		Add_Elem_List_Coord(EnteteListeDesCoordonnes,PersonnageActuel->PositionActuel);
		if(ElementPersonnageParcouru->Suivant!=NULL){
			FuturX=(ElementPersonnageParcouru->Suivant->Usager->Direction->x)+(ElementPersonnageParcouru->Suivant->Usager->PositionActuel->x);
			FuturY=(ElementPersonnageParcouru->Suivant->Usager->Direction->y)+(ElementPersonnageParcouru->Suivant->Usager->PositionActuel->y);
		}
	}
}

void New_Pos_To_Current_Pos(Personnage *PersonnageActuel){
	PersonnageActuel->PositionActuel->x=PersonnageActuel->FuturPosition->x;
	PersonnageActuel->PositionActuel->y=PersonnageActuel->FuturPosition->y;
}