#include "../../Structure.h"

//Rempli une matrice grâce au nom d'un fichier passé en parametre
void remplissage_mat(char **mat, char chemin[]){
    FILE *fichier = NULL;

    char caractere_actuel = 0;
    int i = 0, j = 0;

    char path[20];

    if (sprintf(path, "%s.txt", chemin) == 0){
        printw("Erreur du sprintf\n");
    }

    fichier = fopen(path, "r+");

    if (fichier != NULL){
        caractere_actuel = fgetc(fichier);
        while (caractere_actuel != EOF){
            if (caractere_actuel == '\n'){
                i++;
                j = 0;
            }
            else{
                mat[i][j] = caractere_actuel;
                j++;
            }
            caractere_actuel = fgetc(fichier);
        }
    }
    fclose(fichier);
}

//Allocation mémoire pour la matrice du train en gare
char **initialisation_trainEnGare(){
    char **mat = NULL;
    mat = (char **)malloc(Haut_train * sizeof(char *));
    for (int i = 0; i < Haut_train; i++){
        mat[i] = (char *)malloc(Long_train * sizeof(char));
    }
    return mat;
}

//Allocation mémoire pour la station de metro
char **initialisation_metro(){
    char **mat = NULL;
    mat = (char **)malloc(Haut_metro * sizeof(char *));
    for (int i = 0; i < Haut_metro; i++){
        mat[i] = (char *)malloc(Long_metro * sizeof(char));
    }
    return mat;
}