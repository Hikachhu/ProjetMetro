#include "../../Structure.h"

void AffichageGare();
char **initialisation_train();
void affichage(char **mat, char sentence[],int y,int x, int cache);
void deplacementTrain(char **train,int x, int y, int stop, int verif);
void trainEnGare(char c);
void convertion(char **matrix , int i , int j, int y, int x );
void affichageTemps(int x , int y , int temp);
