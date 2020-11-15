#include "Structure.h"

//ListeChainee.c
void AffichageGare(Limitation *Limite);
EnteteListePersonnages* Init_List_Perso();
Personnage* Creat_New_Perso(int id,int x,int y,int type);
void Add_Perso_In_List(EnteteListePersonnages *EnteteListesDesPersonnages,int id,int x,int y,int type);
void Print_All_Info_Perso_G(Personnage *PersonnageActuel);
void Print_Position_Perso_G(Personnage *PersonnageActuel);
void Print_Direction_Perso_G(Personnage *PersonnageActuel);
void Print_Futur_Position_Perso_G(Personnage *PersonnageActuel);
void Print_In_Gare_Perso_G(Personnage *PersonnageActuel);
void Erase_In_Gare_Perso_G(Personnage *PersonnageActuel);
void Add_Coord_NULL(EnteteListePersonnages *EnteteListeDesPersonnages,EnteteListeCoordonnes *EnteteListeDesCoordonnes);
void Erase_List_Perso(Personnage *PersonnageActuel);
void Erase_List_Perso_G();
void Parcours_L_Gene(void (*FonctionActive)(Personnage*),EnteteListePersonnages *EnteteListeDesPersonnages);
ElementListePersonnages* Parcours_L_Gene_Recur(ElementListePersonnages *ElementPersonnages,int id,int XVerif,int YVerif,int *Possible);
ElementListePersonnages *Rm_Elem_List_Perso_Cible(EnteteListePersonnages *EnteteListesDesPersonnages,int IdASup);
void Rm_Elem_List_Perso(EnteteListePersonnages *EnteteListesDesPersonnages);
void Free_List_Perso(EnteteListePersonnages *EnteteListeDesPersonnages);
EnteteListeCoordonnes* Init_List_Coord();
void Add_Elem_List_Coord(EnteteListeCoordonnes *EnteteListeDesCoordonnes,Coordonnes *CoordonnesAjoute);
void Add_Coord_Gare(EnteteListeCoordonnes *EnteteListeDesCoordonnes,Limitation *Limite);
ListeCoordonnes* Rm_Elem_List_Coord(ListeCoordonnes *Element);
void Rm_List_Coord(EnteteListeCoordonnes *EnteteListeDesCoordonnes);
int Find_Duo_Coord(ListeCoordonnes *ElementCoordonnes,int FuturX,int FuturY);
void Print_List_Coord(ListeCoordonnes *ElementCoordonnes);
void Verif_Go_In_Train(Train *TrainActuel,ElementListePersonnages *ElemPersonnageActuel,EnteteListePersonnages *EnteteListeDesPersonnages);


//TourParTour.c
void TourParTour(EnteteListePersonnages *Entete,int TourARealise,int PresenceTrain,Train *TrainActuel,EnteteListeCoordonnes *EnteteListeDesCoordonnes,Limitation *Limite);
void ChoixDirection(Personnage *PersonnageActuel);
void Add_New_Position(EnteteListePersonnages *EnteteListeDesPersonnages,EnteteListeCoordonnes *EnteteListeDesCoordonnes,Limitation *Limite);
void New_Pos_To_Current_Pos(Personnage *PersonnageActuel);
int Verif_Futur_Pos_Exist(EnteteListePersonnages *EnteteListeBase,int IdActuel,int XVerif,int YVerif);

//Train.c
Train* CreationTrain(Limitation *Limite);
void AffichageTrain(Train *TrainActuel);
int TrouveTrain(Personnage *PersonnageActuel,Train* TrainActuel,Limitation *Limite);
void ChoixDirectionTrain(EnteteListePersonnages *EnteteListeDesPersonnages,Train *TrainActuel,Limitation *Limite);
void AfficheCoordonnesTrain(Train *TrainActuel);
