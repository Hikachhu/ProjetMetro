#include "../../Structure.h"

void AffichageGare(Limitation *Limite){
  usleep(150000);
  FILE *Gare=NULL;
  int Lecture=0;
  int x=0,y=0; 
  Gare=fopen("Texture/Gare.txt","r");
  if (Gare==NULL) {
    printf("Erreur ouverture Gare.txt");
  }else{
  while(!feof(Gare)){
        Lecture=fgetc(Gare);
        switch (Lecture){
          case 48:
            mvprintw(y+Limite->DebutX,x+Limite->DebutY," ");
            break;
          case 49:
            mvprintw(y+Limite->DebutX,x+Limite->DebutY,"═");
            break;
          case 50:
            mvprintw(y+Limite->DebutX,x+Limite->DebutY,"║");
            break;
          case 51:
            mvprintw(y+Limite->DebutX,x+Limite->DebutY,"╔");
            break;
          case 52:
            mvprintw(y+Limite->DebutX,x+Limite->DebutY,"╗");
            break;
          case 53:
            mvprintw(y+Limite->DebutX,x+Limite->DebutY,"╝");
            break;
          case 54:
            mvprintw(y+Limite->DebutX,x+Limite->DebutY,"╚");
            break;
          case 10:
            x=-1;y++;
            break;
          default:
            break;
        }
        x++;
    }
    fclose(Gare);
    refresh();
    getch();
  }
}