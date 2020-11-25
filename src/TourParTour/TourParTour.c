#include "../../Includes/ListeChaine/ListeCoordonnes.h"
#include "../../Includes/ListeChaine/ListePersonnages.h"
#include "../../Includes/ListeChaine/AffichagePerso.h"
#include "../../Includes/ListeChaine/Train.h"
#include "../../Includes/TourParTour/TourParTour.h"
#include "../../Includes/Affichage/AffichageGare.h"
#include "../../Includes/Affichage/FonctionsUtiles.h"

// --------------------------------------------------------------------------------------
// Simulateur de gare
// Code réalisé par Morin Florian et Raphaël PtitHaddad
// Réalisé dans le cadre du projet de 1er Semestre de 3eme année de l'ESIEA
// https://github.com/Hikachhu/ProjetMetro
//
// Fonctions de tour par tour gérant le fonctionnement d'un tour de jeu
// --------------------------------------------------------------------------------------

//Fonction permettant de manipuler les listes afin de réalisé les différent tour pour le déplacment des personnages, et des trains
void TourParTour(EnteteListePersonnages *Entete,int TourARealise,Train *TrainActuel,EnteteListeCoordonnes *EnteteListeDesCoordonnes,Limitation *Limite,int mode){
	if((Entete[0].PremierPersonnage!=NULL&&Entete[1].PremierPersonnage!=NULL)||mode==0){
		char **train = initialisation_train();
	    char train_txt[] = "Texture/train";
	    remplissage_mat(train, train_txt);
	    int DepartHaut=-Long_train-10,ArriveHaut=-Long_train-9,DepartBas=Long_train+36,ArriveBas=Long_train+35,MouvementTrain,PresenceTrain=0,SORTIE,IdPersonnage1,IdPersonnage2;

	    //Pour les 3 états du train possible, à savoir Entre en gare, Arret en gare, sortie de gare

	    for(PresenceTrain=0;PresenceTrain<3;PresenceTrain++){

	    	//Pour tout les déplacement des personnages durant ce tour
			for(int NombreDeTour=0;NombreDeTour<TourARealise&&((Entete[0].PremierPersonnage!=NULL||Entete[1].PremierPersonnage!=NULL)||(mode==0));NombreDeTour++){

				//Affichage des personnages dans la gare
				if(Entete[0].PremierPersonnage!=NULL&&mode!=0)Parcours_L_Gene(&Print_In_Gare_Perso_G,&Entete[0]);
				if(Entete[1].PremierPersonnage!=NULL&&mode!=0)Parcours_L_Gene(&Print_In_Gare_Perso_G,&Entete[1]);
				if(NombreDeTour!=0&&(mode==2||mode==4)&&IdPersonnage1>=0&&IdPersonnage1<=25)Affichage_Gare_Couleur(Entete,IdPersonnage1);
				if(NombreDeTour!=0&&(mode==3||mode==4)&&IdPersonnage2>=0&&IdPersonnage2<=25)Affichage_Gare_Couleur(Entete,IdPersonnage2);
				
				//Si le train entre ou sort
				if(PresenceTrain==0||PresenceTrain==2){
					mvprintw(0,10,"                                              ");
					refresh();
					
					//Si le train entre en gare
					if(PresenceTrain==0){
						mvprintw(3,4,"%2d MIN",TourARealise-NombreDeTour);
						mvprintw(3,143,"%2d MIN",TourARealise-NombreDeTour);
						mvprintw(35,4,"%2d MIN",TourARealise-NombreDeTour);
						mvprintw(35,143,"%2d MIN",TourARealise-NombreDeTour);

						mvprintw(5,4,"%2d MIN",2*TourARealise+(TourARealise-NombreDeTour));
						mvprintw(5,143,"%2d MIN",2*TourARealise+(TourARealise-NombreDeTour));
						mvprintw(37,4,"%2d MIN",2*TourARealise+(TourARealise-NombreDeTour));
						mvprintw(37,143,"%2d MIN",2*TourARealise+(TourARealise-NombreDeTour));
						SORTIE=9;
					}
					//Si le train sort
					else {
						SORTIE=20;
						mvprintw(3,4,"%2d MIN",TourARealise-NombreDeTour+17);
						mvprintw(3,143,"%2d MIN",TourARealise-NombreDeTour+17);
						mvprintw(35,4,"%2d MIN",TourARealise-NombreDeTour+17);
						mvprintw(35,143,"%2d MIN",TourARealise-NombreDeTour+17);

						mvprintw(5,4,"%2d MIN",3*TourARealise+(TourARealise-NombreDeTour));
						mvprintw(5,143,"%2d MIN",3*TourARealise+(TourARealise-NombreDeTour));
						mvprintw(37,4,"%2d MIN",3*TourARealise+(TourARealise-NombreDeTour));
						mvprintw(37,143,"%2d MIN",3*TourARealise+(TourARealise-NombreDeTour));
					} 

					//Le train se déplacement plusieurs fois durant un déplacement de personnage
					for(MouvementTrain=0;MouvementTrain<SORTIE;MouvementTrain++){
						if(NombreDeTour!=TourARealise){
							DepartBas-=1;
							ArriveBas-=1;
							DepartHaut+=1;
							ArriveHaut+=1;
						}
						//Affiche le déplacement des deux trains
						deplacementTrain(train,DepartBas,23,ArriveBas,-1);
						deplacementTrain(train,DepartHaut,13,ArriveHaut,1);
					}

					//Modifications des directions de personnages de maniere aléatoire si le train n'est pas en gare
					if(Entete[0].PremierPersonnage!=NULL&&mode!=0)Parcours_L_Gene(&ChoixDirection,&Entete[0]);
					if(Entete[1].PremierPersonnage!=NULL&&mode!=0)Parcours_L_Gene(&ChoixDirection,&Entete[1]);

					//Déplacement à la main d'un personnage
					if(Entete[0].PremierPersonnage!=NULL&&(mode==2||mode==4))IdPersonnage1=Direction_Choix_Personnage(&Entete[0],0,IdPersonnage1);
					if(Entete[1].PremierPersonnage!=NULL&&(mode==3||mode==4))IdPersonnage2=Direction_Choix_Personnage(&Entete[1],1,IdPersonnage2);

				}
				else if(PresenceTrain==1){
				//Si le train est en gare
					if(NombreDeTour==0){
						mvprintw(0,10,"Nombre de tour avant que le train parte: %2d",NombreDeTour);

						//Affichage du train en gare
				    	trainEnGare('b');
				    	trainEnGare('h');
				    }
					mvprintw(0,109,"TRAIN EN STATION           ");

					mvprintw(3,4,"STATION",TourARealise-NombreDeTour);
					mvprintw(3,143,"STATION",TourARealise-NombreDeTour);
					mvprintw(35,4,"STATION",TourARealise-NombreDeTour);
					mvprintw(35,143,"STATION",TourARealise-NombreDeTour);

					//Selection de la direction en fonction de la position des portes pour trouver la porte la plus proche
					if(Entete[0].PremierPersonnage!=NULL&&mode!=0)ChoixDirectionTrain(&Entete[0],&TrainActuel[0],&Limite[0]);
					if(Entete[1].PremierPersonnage!=NULL&&mode!=0)ChoixDirectionTrain(&Entete[1],&TrainActuel[1],&Limite[1]);

					//Déplacement manuel d'un personnage par l'utilisateur
					if(Entete[0].PremierPersonnage!=NULL&&(mode==2||mode==4))IdPersonnage1=Direction_Choix_Personnage(&Entete[0],0,IdPersonnage1);
					if(Entete[1].PremierPersonnage!=NULL&&(mode==3||mode==4))IdPersonnage2=Direction_Choix_Personnage(&Entete[1],1,IdPersonnage2);

				}
				if(mode==0||mode==1) usleep(400000);

				//Effacement des personnages dans la gare
				if(Entete[0].PremierPersonnage!=NULL&&mode!=0)Parcours_L_Gene(&Erase_In_Gare_Perso_G,&Entete[0]);
				if(Entete[1].PremierPersonnage!=NULL&&mode!=0)Parcours_L_Gene(&Erase_In_Gare_Perso_G,&Entete[1]);

				//Ajout des coordonnées des personnage ne se déplacant pas
				if(Entete[0].PremierPersonnage!=NULL&&mode!=0)Add_Coord_NULL(&Entete[0],&EnteteListeDesCoordonnes[0]);
				if(Entete[1].PremierPersonnage!=NULL&&mode!=0)Add_Coord_NULL(&Entete[1],&EnteteListeDesCoordonnes[1]);

				//Gestion des direction en fonction des positions des autres personnages et de la gare
				if(Entete[0].PremierPersonnage!=NULL&&mode!=0)Add_New_Position(&Entete[0],&EnteteListeDesCoordonnes[0],&Limite[0]);
				if(Entete[1].PremierPersonnage!=NULL&&mode!=0)Add_New_Position(&Entete[1],&EnteteListeDesCoordonnes[1],&Limite[1]);
				
				//Si le train est en gare, nous verifions si les personnages sont sur les positions des portes pour les supprimer de la liste
				if(PresenceTrain==1){
					if(Entete[0].PremierPersonnage!=NULL&&mode!=0)Verif_Go_In_Train(&TrainActuel[0],Entete[0].PremierPersonnage,&Entete[0]);
					if(Entete[1].PremierPersonnage!=NULL&&mode!=0)Verif_Go_In_Train(&TrainActuel[1],Entete[1].PremierPersonnage,&Entete[1]);
				}

				//Suppression de la liste des coordonnées des personnages
				if(Entete[0].PremierPersonnage!=NULL&&mode!=0)Rm_List_Coord(&EnteteListeDesCoordonnes[0]);
				if(Entete[1].PremierPersonnage!=NULL&&mode!=0)Rm_List_Coord(&EnteteListeDesCoordonnes[1]);
			}
		}
	}
}


//Attribution des positions en fonctions des positions des personnages
void Add_New_Position(EnteteListePersonnages *EnteteListeDesPersonnages,EnteteListeCoordonnes *EnteteListeDesCoordonnes,Limitation *Limite){
	ElementListePersonnages *ListePersonnages=EnteteListeDesPersonnages->PremierPersonnage;
	Personnage *PersonnageActuel=ListePersonnages->Usager;
	int FuturX=(PersonnageActuel->Direction->x)+(PersonnageActuel->PositionActuel->x);
	int FuturY=(PersonnageActuel->Direction->y)+(PersonnageActuel->PositionActuel->y);
	int PossibiliteDeplacement=0;

	//Pour tout les éléments de la liste
	for(ElementListePersonnages *ElementPersonnageParcouru=ListePersonnages;ElementPersonnageParcouru!=NULL;ElementPersonnageParcouru=Parcours_L_Gene_Recur(ListePersonnages,PersonnageActuel->ID,FuturX,FuturY,&PossibiliteDeplacement)){
		PersonnageActuel=ElementPersonnageParcouru->Usager;

		//Si la positions n'est pas occupée
		if(PossibiliteDeplacement==0&&Find_Duo_Coord(EnteteListeDesCoordonnes->PremiereCoordonnes,FuturX,FuturY)==0){

			//Si la futur position se trouve dans les limites de la gare
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
			//Le personnage reste a sa positions
			(PersonnageActuel->FuturPosition->x)=(PersonnageActuel->PositionActuel->x);
			(PersonnageActuel->FuturPosition->y)=(PersonnageActuel->PositionActuel->y);
		}
		//Transforme les futurpositions en positions actuel
		New_Pos_To_Current_Pos(PersonnageActuel);
		PossibiliteDeplacement=0;

		//Ajoute la coordonnée du personnage actuel dans la liste des positions occupées
		Add_Elem_List_Coord(EnteteListeDesCoordonnes,PersonnageActuel->PositionActuel);
		
		//Création de la futur positions du futur personnage
		if(ElementPersonnageParcouru->Suivant!=NULL){
			FuturX=(ElementPersonnageParcouru->Suivant->Usager->Direction->x)+(ElementPersonnageParcouru->Suivant->Usager->PositionActuel->x);
			FuturY=(ElementPersonnageParcouru->Suivant->Usager->Direction->y)+(ElementPersonnageParcouru->Suivant->Usager->PositionActuel->y);
		}
	}
}