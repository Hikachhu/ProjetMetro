#include "../../Structure.h"

void Add_Coord_Gare(EnteteListeCoordonnes *EnteteListeDesCoordonnes,Limitation *Limite);
void Add_Coord_NULL(EnteteListePersonnages *EnteteListeDesPersonnages,EnteteListeCoordonnes *EnteteListeDesCoordonnes);
void Add_Elem_List_Coord(EnteteListeCoordonnes *EnteteListeDesCoordonnes,Coordonnes *CoordonnesAjoute);
int Find_Duo_Coord(ListeCoordonnes *ElementCoordonnes,int FuturX,int FuturY);
EnteteListeCoordonnes* Init_List_Coord();
ListeCoordonnes* Rm_Elem_List_Coord(ListeCoordonnes *Element);
void Rm_List_Coord(EnteteListeCoordonnes *EnteteListeDesCoordonnes);
void Print_List_Coord(ListeCoordonnes *ElementCoordonnes);