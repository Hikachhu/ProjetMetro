#include "../../Structure.h"

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

int Find_Duo_Coord(ListeCoordonnes *ElementCoordonnes,int FuturX,int FuturY){
	while(ElementCoordonnes!=NULL){
		if (ElementCoordonnes->Position->x==FuturX&&ElementCoordonnes->Position->y==FuturY){
			return 1;
		}
		ElementCoordonnes=ElementCoordonnes->Suivant;
	}
	return 0;
}


EnteteListeCoordonnes* Init_List_Coord(){
	EnteteListeCoordonnes *EnteteListeDesCoordonnes=malloc(2*sizeof(EnteteListeDesCoordonnes));
	for(int j=0;j<2;j++){
		EnteteListeDesCoordonnes[j].PremiereCoordonnes=NULL;
	}
	return EnteteListeDesCoordonnes;
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