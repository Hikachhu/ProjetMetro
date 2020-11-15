#include "AllIncludes.h"

EnteteListePersonnages* Init_List_Perso(){
	EnteteListePersonnages* EnteteListesDesPersonnages;
	EnteteListesDesPersonnages=malloc(2*sizeof(EnteteListePersonnages));
	for(int j=0;j<2;j++){
		EnteteListesDesPersonnages[j].PremierPersonnage=NULL;
		EnteteListesDesPersonnages[j].DernierPersonnage=NULL;
	}
	return EnteteListesDesPersonnages;
}

Personnage* Creat_New_Perso(int id,int x,int y,int type){
	
	Personnage *NouvellePersonne=NULL;
	NouvellePersonne=(Personnage*)malloc(2*sizeof(Personnage));
	Coordonnes *Position=malloc(2*sizeof(Coordonnes));
	
	for(int i=0;i<2;i++){

		NouvellePersonne[i].PositionActuel=Position;
		NouvellePersonne[i].Direction=malloc(sizeof(Coordonnes));
		NouvellePersonne[i].FuturPosition=malloc(sizeof(Coordonnes));

		NouvellePersonne[i].ID=id;
		NouvellePersonne[i].Type=type;

		NouvellePersonne[i].PositionActuel->x=x;
		NouvellePersonne[i].PositionActuel->y=y;

		NouvellePersonne[i].Direction->x=0;
		NouvellePersonne[i].Direction->y=0;
		
		NouvellePersonne[i].FuturPosition->x=0;
		NouvellePersonne[i].FuturPosition->y=0;
	
	}
	return NouvellePersonne;
}

void Add_Perso_In_List(EnteteListePersonnages *EnteteListesDesPersonnages,int id,int x,int y,int type){
	Personnage *NouvellePersonne=Creat_New_Perso(id,x,y,type);
	ElementListePersonnages *NouvelElementListePersonnages=malloc(sizeof(ElementListePersonnages));
	NouvelElementListePersonnages->Usager=NouvellePersonne;
  
	if (EnteteListesDesPersonnages->PremierPersonnage==NULL){
		EnteteListesDesPersonnages->PremierPersonnage=NouvelElementListePersonnages;
	}
	else{
		EnteteListesDesPersonnages->DernierPersonnage->Suivant=NouvelElementListePersonnages;
	}
	EnteteListesDesPersonnages->DernierPersonnage=NouvelElementListePersonnages;
}

void Print_All_Info_Perso_G(Personnage *PersonnageActuel){
	int Hauteur=PersonnageActuel->ID+15;
	mvprintw(Hauteur,0,"adresse %p \tId:%d Type:%d\t PositionActuel[x:%2d y:%2d]\tDirection[x:%2d y:%2d]\tFuturPosition[x:%2d y:%2d]\n",PersonnageActuel,PersonnageActuel->ID,PersonnageActuel->Type,PersonnageActuel->PositionActuel->x,PersonnageActuel->PositionActuel->y,PersonnageActuel->Direction->x,PersonnageActuel->Direction->y,PersonnageActuel->FuturPosition->x,PersonnageActuel->FuturPosition->y);
}

void Print_Position_Perso_G(Personnage *PersonnageActuel){
	int Hauteur=PersonnageActuel->ID+15;
	mvprintw(Hauteur,0,"Id:%d Type:%d x:%d y:%d\n",PersonnageActuel->ID,PersonnageActuel->Type,PersonnageActuel->PositionActuel->x,PersonnageActuel->PositionActuel->y);
}

void Print_Direction_Perso_G(Personnage *PersonnageActuel){
	int Hauteur=PersonnageActuel->ID+15;
	mvprintw(Hauteur,0,"Id:%d Type:%d x:%d y:%d\n",PersonnageActuel->ID,PersonnageActuel->Type,PersonnageActuel->Direction->x,PersonnageActuel->Direction->y);
}

void Print_Futur_Position_Perso_G(Personnage *PersonnageActuel){
	int Hauteur=PersonnageActuel->ID+15;
	mvprintw(Hauteur,0,"Id:%d Type:%d x:%d y:%d\n",PersonnageActuel->ID,PersonnageActuel->Type,PersonnageActuel->FuturPosition->x,PersonnageActuel->FuturPosition->y);
}

void Print_In_Gare_Perso_G(Personnage *PersonnageActuel){
	int X=PersonnageActuel->PositionActuel->x+1;
	int Y=PersonnageActuel->PositionActuel->y+1;
	mvprintw(X,Y,"%c",PersonnageActuel->ID+'a');	
}

void Erase_List_Perso(Personnage *PersonnageActuel){
	int Hauteur=(PersonnageActuel->ID)+15;
  	mvprintw(Hauteur,0,"                                                                                                \n");
}

void Erase_List_Perso_G(){
	for(int i=0;i<10;i++){
		mvprintw(i+15,0,"                                                                                                \n");		
	}
	refresh();
}

void Erase_In_Gare_Perso_G(Personnage *PersonnageActuel){
	int X=PersonnageActuel->PositionActuel->x+1;
	int Y=PersonnageActuel->PositionActuel->y+1;
	mvprintw(X,Y," ");		
}

void Add_Coord_NULL(EnteteListePersonnages *EnteteListeDesPersonnages,EnteteListeCoordonnes *EnteteListeDesCoordonnes){
	ElementListePersonnages *Actuel=EnteteListeDesPersonnages->PremierPersonnage;
	Personnage *PersonnageActuel=NULL;
	do{
		PersonnageActuel=Actuel->Usager;
		if(PersonnageActuel->Direction->x==0&&PersonnageActuel->Direction->y==0){
			Add_Elem_List_Coord(EnteteListeDesCoordonnes,PersonnageActuel->PositionActuel);
		}
		Actuel=Actuel->Suivant;
	}while(Actuel!=NULL);
}

void Parcours_L_Gene(void (*FonctionActive)(Personnage*),EnteteListePersonnages *EnteteListeDesPersonnages){
	if(EnteteListeDesPersonnages->PremierPersonnage!=NULL){
		mvprintw(50,130,"LISTE VIDE");
		refresh();
		ElementListePersonnages *Actuel=EnteteListeDesPersonnages->PremierPersonnage;
		Personnage *PersonnageActuel=NULL;
		do{
			PersonnageActuel=Actuel->Usager;
			(*FonctionActive)(PersonnageActuel);
			Actuel=Actuel->Suivant;
		}while(Actuel!=NULL);
	}
}

ElementListePersonnages* Parcours_L_Gene_Recur(ElementListePersonnages *ElementPersonnages,int id,int XVerif,int YVerif,int *Possible){
	if(ElementPersonnages!=NULL){
		if(ElementPersonnages->Usager->ID<=id){
			Personnage *PersonnageActuel=ElementPersonnages->Usager;
			if (XVerif==PersonnageActuel->PositionActuel->x&&YVerif==PersonnageActuel->PositionActuel->y)(*Possible)++;
				return Parcours_L_Gene_Recur(ElementPersonnages->Suivant,id,XVerif,YVerif,Possible);
		}
	}
	return ElementPersonnages;
}

ElementListePersonnages *Rm_Elem_List_Perso_Cible(EnteteListePersonnages *EnteteListesDesPersonnages,int IdASup){
	ElementListePersonnages *ElemActuel=EnteteListesDesPersonnages->PremierPersonnage;
	while(ElemActuel!=NULL&&ElemActuel->Suivant->Usager->ID!=IdASup&&ElemActuel->Suivant!=NULL){
		ElemActuel=ElemActuel->Suivant;
	}
	ElementListePersonnages *ElementTemporaire=ElemActuel->Suivant;
	ElemActuel->Suivant=ElemActuel->Suivant->Suivant;
	refresh();
	free(ElementTemporaire->Usager->PositionActuel);
	free(ElementTemporaire->Usager->Direction);
	free(ElementTemporaire->Usager->FuturPosition);
	free(ElementTemporaire->Usager);
	free(ElementTemporaire);

//	Parcours_L_Gene(&Erase_List_Perso,EnteteListesDesPersonnages);
	// Parcours_L_Gene(&Print_All_Info_Perso_G,EnteteListesDesPersonnages);
	refresh();
	return ElemActuel->Suivant;

}

void Rm_Elem_List_Perso(EnteteListePersonnages *EnteteListesDesPersonnages){
	ElementListePersonnages *ElementTemporaire=EnteteListesDesPersonnages->PremierPersonnage;
	EnteteListesDesPersonnages->PremierPersonnage=ElementTemporaire->Suivant;
	free(ElementTemporaire->Usager->PositionActuel);
	free(ElementTemporaire->Usager->Direction);
	free(ElementTemporaire->Usager->FuturPosition);
	free(ElementTemporaire->Usager);
	free(ElementTemporaire);
}

void Free_List_Perso(EnteteListePersonnages *EnteteListeDesPersonnages){
	do{
		Rm_Elem_List_Perso(EnteteListeDesPersonnages);
	}while(EnteteListeDesPersonnages->PremierPersonnage!=NULL);
	EnteteListeDesPersonnages->DernierPersonnage=NULL;
	free(EnteteListeDesPersonnages);
}

EnteteListeCoordonnes* Init_List_Coord(){
	EnteteListeCoordonnes *EnteteListeDesCoordonnes=malloc(2*sizeof(EnteteListeDesCoordonnes));
	for(int j=0;j<2;j++){
		EnteteListeDesCoordonnes[j].PremiereCoordonnes=NULL;
	}
	return EnteteListeDesCoordonnes;
}

void Add_Elem_List_Coord(EnteteListeCoordonnes *EnteteListeDesCoordonnes,Coordonnes *CoordonnesAjoute){
	ListeCoordonnes* ElemListe=malloc(sizeof(ElemListe));
	ElemListe->Position=malloc(sizeof(Coordonnes));
	ElemListe->Position->x=CoordonnesAjoute->x;
	ElemListe->Position->y=CoordonnesAjoute->y;
	ElemListe->Suivant=NULL;
	if(EnteteListeDesCoordonnes->PremiereCoordonnes==NULL){
		EnteteListeDesCoordonnes->DerniereCoordonnes=ElemListe;
		EnteteListeDesCoordonnes->PremiereCoordonnes=ElemListe;
	}else{
		EnteteListeDesCoordonnes->DerniereCoordonnes->Suivant=ElemListe;
		EnteteListeDesCoordonnes->DerniereCoordonnes=ElemListe;
	}
}

void Add_Coord_Gare(EnteteListeCoordonnes *EnteteListeDesCoordonnes,Limitation *Limite){
	Coordonnes *Actuel=malloc(sizeof(Coordonnes));
	for(int i =Limite->DebutX;i<Limite->FinY;i++){
		for(int j=Limite->DebutY;j<Limite->FinY;j++){
			Actuel->x=i;
			Actuel->y=j;
			Add_Elem_List_Coord(EnteteListeDesCoordonnes,Actuel);	
		}
	}
	free(Actuel);
}

ListeCoordonnes* Rm_Elem_List_Coord(ListeCoordonnes *Element){
	ListeCoordonnes *ElementTemporaire=Element->Suivant;
	free(Element->Position);
	Element->Suivant=NULL;
	free(Element);
	return ElementTemporaire;
}

void Rm_List_Coord(EnteteListeCoordonnes *EnteteListeDesCoordonnes){
	do{
		if(EnteteListeDesCoordonnes->PremiereCoordonnes==NULL){
			break;
		}
		// printf("A;%p\n",EnteteListeDesCoordonnes->PremiereCoordonnes);
		EnteteListeDesCoordonnes->PremiereCoordonnes=Rm_Elem_List_Coord(EnteteListeDesCoordonnes->PremiereCoordonnes);
		// printf("P:%p\n",EnteteListeDesCoordonnes->PremiereCoordonnes);
		}while(EnteteListeDesCoordonnes->PremiereCoordonnes!=NULL);
	EnteteListeDesCoordonnes->DerniereCoordonnes=NULL;
}

int Find_Duo_Coord(ListeCoordonnes *ElementCoordonnes,int FuturX,int FuturY){
	while(ElementCoordonnes!=NULL){
		if (ElementCoordonnes->Position->x==FuturX&&ElementCoordonnes->Position->y==FuturY){
			return 1;
		}
		ElementCoordonnes=ElementCoordonnes->Suivant;
	}
	return 0;
}

void Print_List_Coord(ListeCoordonnes *ElementCoordonnes){
	int i=0;
	mvprintw(19,130,"Liste Coordonnes:");
	for(int i=0;i<20;i++){
		mvprintw(i+20,130,"        ");
	}
	while(ElementCoordonnes!=NULL){
		mvprintw(i+20,130,"       ");
		mvprintw(i+20,130,"%d %d",ElementCoordonnes->Position->x,ElementCoordonnes->Position->y);
		i++;
		ElementCoordonnes=ElementCoordonnes->Suivant;
	}
	printf("FIN\n");
	refresh();
}

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