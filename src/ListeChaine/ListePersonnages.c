#include "../../Includes/ListeChaine/ListePersonnages.h"

// --------------------------------------------------------------------------------------
// Simulateur de gare
// Code réalisé par Morin Florian et Raphaël PtitHaddad
// Réalisé dans le cadre du projet de 1er Semestre de 3eme année de l'ESIEA
//
// Ensemble des fonctions servant au fonctionnement de la liste des personnages
// --------------------------------------------------------------------------------------

//Ajout d'un personnage en fin de liste des personnages
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

//Création d'un tableau de listes de personnages
EnteteListePersonnages* Init_List_Perso(){
	EnteteListePersonnages* EnteteListesDesPersonnages;
	EnteteListesDesPersonnages=malloc(2*sizeof(EnteteListePersonnages));
	for(int j=0;j<2;j++){
		EnteteListesDesPersonnages[j].PremierPersonnage=NULL;
		EnteteListesDesPersonnages[j].DernierPersonnage=NULL;
	}
	return EnteteListesDesPersonnages;
}

//Création d'une structure de personnage
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

//Suppression d'une liste de personnage
void Free_List_Perso(EnteteListePersonnages *EnteteListeDesPersonnages){
	do{
		Rm_Elem_List_Perso(EnteteListeDesPersonnages);
	}while(EnteteListeDesPersonnages->PremierPersonnage!=NULL);
	EnteteListeDesPersonnages->DernierPersonnage=NULL;
	free(EnteteListeDesPersonnages);
}

//Parcours de la liste en prennant en parametre un pointeur de fonction
//Cette fonction prend en parametre un pointeur de personnage
//Ainsi nous appellons cette fonction pour balayer la liste de personnage
//Et nous modifions ce que nous faisons sur chaque personnage grâce à la fonction passée en parametre
void Parcours_L_Gene(void (*FonctionActive)(Personnage*),EnteteListePersonnages *EnteteListeDesPersonnages){
	if(EnteteListeDesPersonnages->PremierPersonnage!=NULL){
		mvprintw(50,130,"LISTE VIDE");
		refresh();
		ElementListePersonnages *Actuel=EnteteListeDesPersonnages->PremierPersonnage;
		Personnage *PersonnageActuel=NULL;
		do{
			PersonnageActuel=Actuel->Usager;
			//Appel de la fonction pour chaque personnage
			(*FonctionActive)(PersonnageActuel);
			Actuel=Actuel->Suivant;
		}while(Actuel!=NULL);
	}
}

//Fonction qui renvoi l'élement suivant par rapport à l'id passé en parametre, ainsi si l'id est incrémenté, cette fonction balaye l'ensemble de la liste chainée
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

//Suppression du premier élément de la liste des personnages
void Rm_Elem_List_Perso(EnteteListePersonnages *EnteteListesDesPersonnages){
	ElementListePersonnages *ElementTemporaire=EnteteListesDesPersonnages->PremierPersonnage;
	EnteteListesDesPersonnages->PremierPersonnage=ElementTemporaire->Suivant;
	free(ElementTemporaire->Usager->PositionActuel);
	free(ElementTemporaire->Usager->Direction);
	free(ElementTemporaire->Usager->FuturPosition);
	free(ElementTemporaire->Usager);
	free(ElementTemporaire);
}

//Suppression d'un element ciblé dont nous passons l'id en parametre
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
	refresh();
	return ElemActuel->Suivant;

}

//Attribue une direction aléatoire pour un personnage
void ChoixDirection(Personnage *PersonnageActuel){
	PersonnageActuel->Direction->x=random()%3-1;
	PersonnageActuel->Direction->y=random()%3-1;
}

//Remplace la position actuel d'un personnage par sa futur position
void New_Pos_To_Current_Pos(Personnage *PersonnageActuel){
	PersonnageActuel->PositionActuel->x=PersonnageActuel->FuturPosition->x;
	PersonnageActuel->PositionActuel->y=PersonnageActuel->FuturPosition->y;
}

//Permet de modifier la direction d'un personnage où le choix du personnage sera entrée par l'utilisateur, tout comme la direction
int Direction_Choix_Personnage(EnteteListePersonnages *EnteteListesDesPersonnages,int Listes){
	char Direction;
	int IdPersonnage;
	char charPersonnage;

	if(Listes==0) mvprintw(29+Listes*6,160,"Dans la gare du haut");
	else mvprintw(29+Listes*6,160,"Dans la gare du bas");	
	
	mvprintw(30+6*Listes,160,"Nom d'un personnage à controler");
	refresh();
	scanw("%c",&charPersonnage);
	IdPersonnage=(int)charPersonnage-97;
	mvprintw(31+6*Listes,160,"%c",IdPersonnage+'a');
	refresh();

	if(IdPersonnage>=0&&IdPersonnage<=25) Affichage_Gare_Couleur(EnteteListesDesPersonnages,IdPersonnage);

	mvprintw(32+6*Listes,160,"Quelle direction ? azeqsdwc");
	refresh();
	scanw("%c",&Direction);
	mvprintw(33+6*Listes,160,"%c",Direction);

	int xDirection=0,yDirection=0;
	switch(Direction){
		case 'a':
			xDirection=-1;
			yDirection=-1;
			break;
		case 'z':
			xDirection=-1;
			yDirection=0;
			break;
		case 'e':
			xDirection=-1;
			yDirection=1;
			break;
		case 'd':
			xDirection=0;
			yDirection=1;
			break;
		case 'c':
			xDirection=1;
			yDirection=1;
			break;
		case 'x':
			xDirection=1;
			yDirection=0;
			break;
		case 'w':
			xDirection=1;
			yDirection=-1;
			break;
		case 'q':
			xDirection=0;
			yDirection=-1;
			break;
		case 's':
			xDirection=0;
			yDirection=0;
			break;
	}
	if(EnteteListesDesPersonnages->PremierPersonnage!=NULL&&(IdPersonnage>=0&&IdPersonnage<=25)){
		ElementListePersonnages *Actuel=EnteteListesDesPersonnages->PremierPersonnage;
		Personnage *PersonnageActuel=Actuel->Usager;
		while(Actuel!=NULL&&PersonnageActuel->ID!=IdPersonnage){
			PersonnageActuel=Actuel->Usager;
			Actuel=Actuel->Suivant;
		}
		PersonnageActuel->Direction->x=xDirection;
		PersonnageActuel->Direction->y=yDirection;
		mvprintw(34+6*Listes,160,"Personnage:%c xDirection%2d yDirection:%2d",PersonnageActuel->ID+'a',PersonnageActuel->Direction->x,PersonnageActuel->Direction->y);
		refresh();
	}
	return IdPersonnage;
}

//fonction pour afficher un personnage en rouge
void Affichage_Gare_Couleur(EnteteListePersonnages *EnteteListesDesPersonnages,int IdPersonnage){
	ElementListePersonnages *Actuel=EnteteListesDesPersonnages->PremierPersonnage;
	Personnage *PersonnageActuel=Actuel->Usager;
	while(Actuel!=NULL&&PersonnageActuel->ID!=IdPersonnage){
		PersonnageActuel=Actuel->Usager;
		Actuel=Actuel->Suivant;
	}
	attron(COLOR_PAIR(2));
	mvprintw(PersonnageActuel->PositionActuel->x+1,PersonnageActuel->PositionActuel->y+1,"%c",PersonnageActuel->ID+'a');
	attron(COLOR_PAIR(1));
}