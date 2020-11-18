#include "../../Structure.h"
#include "../../Includes/Affichage/AffichageGare.h"
#include "../../Includes/Affichage/FonctionsUtiles.h"

void AffichageGare(){
  fopen("Texture/Gare.txt","r");
}

char **initialisation_train()
{
    char **mat = NULL;
    mat = (char **)malloc(Haut_train * sizeof(char *));
    for (int i = 0; i < Haut_train; i++)
    {
        mat[i] = (char *)malloc(Long_train * sizeof(char));
    }
    return mat;
}

void affichage(char **mat, char sentence[],int y,int x, int cache){

    int Haut = 0, Long = 0; 
    char train_txt[] = "train";
    char metro_txt[] = "Texture/metro";
    char trainEnGare_txt[] = "Texture/trainEnGare";
    char trainEnGare2_txt[] = "Texture/trainEnGare2";

    if (strcmp(sentence,train_txt) == 0 || strcmp(sentence,trainEnGare_txt) == 0 ||strcmp(sentence,trainEnGare2_txt) == 0){
        Haut = Haut_train;
        Long = Long_train;
       // printf("%d %d\n", Haut, Long);
    }
    else if(strcmp(sentence,metro_txt) == 0){
        Haut = Haut_metro;
        Long = Long_metro;
        //printf("%d %d\n", Haut, Long);
    }   

    for(int i = 0 ; i < Haut; i ++){
        x = 0;
        for(int j = 0; j < Long ; j++){
            convertion(mat,i,j,y,x+cache);
            x++;
        }
        y++;
    }
    refresh();
}

void deplacementTrain(char **train,int x, int y, int stop, int verif){
    int xCache = x;
    int yCache = y;
    int xbleue = 24;
    int compt = 0;

    while(xCache < stop && verif > 0)
    {
        xCache = xCache + verif; // vitesse du train
        usleep(5000);
        refresh();

        if (xCache > xbleue){
            compt ++;
        }
        for (int i = 0; i < Haut_train; i++)
        {
            x = 0;
            for (int j = 0; j < Long_train - compt; j++)
            {
                convertion(train,i,j,y,x + xCache);
                x++;
                refresh();
            }
            y++;
        }
        y = yCache;
    }

    while(verif < 0 && xCache > stop)
    {
        xCache = xCache + verif; // vitesse du train
        usleep(5000);
        refresh();

        for (int i = 0; i < Haut_train; i++)
        {
            x = 0;
            for (int j = 0; j < Long_train ; j++)
            {
                convertion(train,i,j,y,x + xCache);
                x++;
                refresh();
            }
            y++;
        }
        y = yCache;
    }
}

void convertion(char **matrix , int i , int j, int y, int x ){
    switch (matrix[i][j])
    {
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


void affichageTemps(int x , int y , int temp)
{
    char text[] = "next";
    mvprintw(y,x,"%s=%d",text,temp);
}

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