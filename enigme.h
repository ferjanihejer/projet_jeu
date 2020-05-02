#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED


typedef struct 
{
 
 char question[200];
 char r1[50];
 char r2[50];
 char solution[50];
 
 SDL_Surface *fonds;
 
 SDL_Surface *q;
 SDL_Surface *rep1;
 SDL_Surface *rep2;
 SDL_Surface *s;
 
 SDL_Rect position_fonds;
 SDL_Rect pos_q;
 SDL_Rect pos_rep1;
 SDL_Rect pos_rep2;
 SDL_Rect pos_s;
 

} enigme;



void init_enigme(enigme *e,char* nom_fich);
char return_solution(char* nom_fich,enigme *e);
int  aleatoire(int n);
int  compter_nombre_de_ligne_fichier(char* nom_fich);
void afficher_enigme(SDL_Surface * screen,char* nom_fich, enigme *e);
int  resolution (char* nom_fich,enigme *e, SDL_Surface *screen,int *a,int *b,char solution);

void afficher_resultat (SDL_Surface * screen,int r);

#endif//ENIGME_H_INCLUDED
