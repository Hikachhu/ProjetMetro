#include "../../Structure.h"

void Add_Perso_In_List(EnteteListePersonnages *EnteteListesDesPersonnages,int id,int x,int y,int type);
EnteteListePersonnages* Init_List_Perso();
Personnage* Creat_New_Perso(int id,int x,int y,int type);
void Free_List_Perso(EnteteListePersonnages *EnteteListeDesPersonnages);
void Parcours_L_Gene(void (*FonctionActive)(Personnage*),EnteteListePersonnages *EnteteListeDesPersonnages);
ElementListePersonnages* Parcours_L_Gene_Recur(ElementListePersonnages *ElementPersonnages,int id,int XVerif,int YVerif,int *Possible);
void Rm_Elem_List_Perso(EnteteListePersonnages *EnteteListesDesPersonnages);
ElementListePersonnages *Rm_Elem_List_Perso_Cible(EnteteListePersonnages *EnteteListesDesPersonnages,int IdASup);
void ChoixDirection(Personnage *PersonnageActuel);
void New_Pos_To_Current_Pos(Personnage *PersonnageActuel);