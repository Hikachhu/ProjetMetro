#include "../../Structure.h"
#include "../../Includes/ListeChaine/ListeCoordonnes.h"

// --------------------------------------------------------------------------------------
// Simulateur de gare
// Code réalisé par Morin Florian et Raphaël PtitHaddad
// Réalisé dans le cadre du projet de 1er Semestre de 3eme année de l'ESIEA
//
// Fonctions de gestions des coordonnées
// --------------------------------------------------------------------------------------

//Ajout d'une coordonnées dans la liste
void Add_Coord_Gare(EnteteListeCoordonnes *EnteteListeDesCoordonnes,Limitation *Limite){
	printf(" ");
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

//Ajout de toutes les positions de personnages dont leurs directions est null
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

//Ajout d'un élément dans la liste
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

//Renvoi 1 si la position n'est pas disponible, 0 sinon
int Find_Duo_Coord(ListeCoordonnes *ElementCoordonnes,int FuturX,int FuturY){
	while(ElementCoordonnes!=NULL){
		if (ElementCoordonnes->Position->x==FuturX&&ElementCoordonnes->Position->y==FuturY){
			return 1;
		}
		ElementCoordonnes=ElementCoordonnes->Suivant;
	}
	return 0;
}

//Initialise le tableau des listes de personnages
EnteteListeCoordonnes* Init_List_Coord(){
	EnteteListeCoordonnes *EnteteListeDesCoordonnes=malloc(2*sizeof(EnteteListeDesCoordonnes));
	for(int j=0;j<2;j++){
		EnteteListeDesCoordonnes[j].PremiereCoordonnes=NULL;
	}
	return EnteteListeDesCoordonnes;
}

//Suppression du premier personnage de la liste
ListeCoordonnes* Rm_Elem_List_Coord(ListeCoordonnes *Element){
	ListeCoordonnes *ElementTemporaire=Element->Suivant;
	free(Element->Position);
	Element->Suivant=NULL;
	free(Element);
	return ElementTemporaire;
}

//Suppression de la liste des coordonnées
void Rm_List_Coord(EnteteListeCoordonnes *EnteteListeDesCoordonnes){
	do{
		if(EnteteListeDesCoordonnes->PremiereCoordonnes==NULL){
			break;
		}
		EnteteListeDesCoordonnes->PremiereCoordonnes=Rm_Elem_List_Coord(EnteteListeDesCoordonnes->PremiereCoordonnes);
	}while(EnteteListeDesCoordonnes->PremiereCoordonnes!=NULL);
	EnteteListeDesCoordonnes->DerniereCoordonnes=NULL;
}

//Affiche list des coordonnées
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