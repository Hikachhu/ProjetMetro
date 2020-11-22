#include "../../Structure.h"
#include "../../Includes/Affichage/AffichageGare.h"
#include "../../Includes/Affichage/FonctionsUtiles.h"

// --------------------------------------------------------------------------------------
// Simulateur de gare
// Code réalisé par Morin Florian et Raphaël PtitHaddad
// Réalisé dans le cadre du projet de 1er Semestre de 3eme année de l'ESIEA
//
// Fonctions pour l'affiche de la gare et du train
// --------------------------------------------------------------------------------------

//Création du tableau pour stocker les informations du fichier du train
char **initialisation_train(){
    char **mat = NULL;
    mat = (char **)malloc(Haut_train * sizeof(char *));
    for (int i = 0; i < Haut_train; i++){
        mat[i] = (char *)malloc(Long_train * sizeof(char));
    }
    return mat;
}

//Affiche en fonction du train du fichier selectionné
void affichage(char **mat, char sentence[],int y,int x, int cache){
    int Haut = 0, Long = 0; 
    char train_txt[] = "train";
    char metro_txt[] = "Texture/metro";
    char trainEnGare_txt[] = "Texture/trainEnGare";
    char trainEnGare2_txt[] = "Texture/trainEnGare2";

    if (strcmp(sentence,train_txt) == 0 || strcmp(sentence,trainEnGare_txt) == 0 ||strcmp(sentence,trainEnGare2_txt) == 0){
        Haut = Haut_train;
        Long = Long_train;
    }
    else if(strcmp(sentence,metro_txt) == 0){
        Haut = Haut_metro;
        Long = Long_metro;
    }   

    for(int i = 0 ; i < Haut; i ++){
        x = 0;
        for(int j = 0; j < Long ; j++){
            conversion(mat,i,j,y,x+cache);
            x++;
        }
        y++;
    }
    refresh();
}

//Affiche le déplacement du train
void deplacementTrain(char **train,int x, int y, int stop, int verif){
    int xCache = x;
    int yCache = y;
    int xbleue = 24;
    int compt = 0;

    while(xCache < stop && verif > 0){
        xCache = xCache + verif; // vitesse du train
        usleep(1000);
        refresh();

        if (xCache > xbleue){
            compt ++;
        }
        for (int i = 0; i < Haut_train; i++){
            x = 0;
            for (int j = 0; j < Long_train - compt; j++){
                if(x+xCache<156)conversion(train,i,j,y,x + xCache);
                x++;
                refresh();
            }
            y++;
        }
        y = yCache;
    }

    while(verif < 0 && xCache > stop){
        xCache = xCache + verif; // vitesse du train
        usleep(1000);
        refresh();

        for (int i = 0; i < Haut_train; i++){
            x = 0;
            for (int j = 0; j < Long_train ; j++){
                if(x+xCache<156)conversion(train,i,j,y,x + xCache);
                x++;
                refresh();
            }
            y++;
        }
        y = yCache;
    }
}

//Fais correspondre les lettres lu à des caracteres spéciaux grâce à un switch case
void conversion(char **matrix , int i , int j, int y, int x ){
    switch (matrix[i][j]){
        case ' ':
            mvprintw(y, x , " ");
            break;
        case 'a':
            mvprintw(y, x , "═");
            break;
        case 'b':
            mvprintw(y, x , "║");
            break;
        case 'c':
            mvprintw(y, x , "╦");
            break;
        case 'd':
            mvprintw(y, x , "╩");
            break;
        case 'e':
            mvprintw(y, x , "╔");
            break;
        case 'f':
            mvprintw(y, x , "╗");
            break;
        case 'g':
            mvprintw(y, x , "╚");
            break;
        case 'h':
            mvprintw(y, x , "╝");
            break;
        case 'i':
            mvprintw(y, x , "╠");
            break;
        case 'j':
            mvprintw(y, x , "╣");
            break;
        case 'k':
            mvprintw(y, x , "╬");
            break;
        case 'l':
            mvprintw(y, x , "┌");
            break;
        case 'm':
            mvprintw(y, x , "┐");
            break;
        case 'n':
            mvprintw(y, x , "└");
            break;
        case 'o':
            mvprintw(y, x , "┘");
            break;
        case 'p':
            mvprintw(y, x , "│");
        case 'q':
            mvprintw(y, x , "█");
            break;
        case 'r':
            mvprintw(y, x , "■");
            break;
        case 's':
            mvprintw(y, x , "▒");
            break;
        case 't':
            mvprintw(y, x , "▓");
            break;
        case 'u':
            mvprintw(y, x , "░");
            break;
        default:
            break;
    }
}

//Affiche le train en gare
void trainEnGare(char c){
    char **trainGare1 = initialisation_trainEnGare();
    char **trainGare2 = initialisation_trainEnGare();

    char trainEngare1_txt[] = "Texture/trainEnGare";
    char trainEngare2_txt[] = "Texture/trainEnGare2";

    int x_haut = 13 , y_haut = 13, x_bas = 23 , y_bas = 13;
    remplissage_mat(trainGare1, trainEngare1_txt);
    remplissage_mat(trainGare2, trainEngare2_txt);

    if(c == 'h'){
        affichage(trainGare1,trainEngare1_txt, y_haut , x_haut, 13);
    }

    else if(c == 'b'){
        affichage(trainGare2,trainEngare2_txt, x_bas , y_bas, 13);
    }
}