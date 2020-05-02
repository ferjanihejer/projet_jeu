#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "enigme.h"


void init_enigme(enigme *e,char* nom_fich)
{
 
 
 e->fonds=NULL;
e->position_fonds.x=235;
 e->position_fonds.y=100;

 e->pos_q.x=310;
 e->pos_q.y=200;

 e->pos_rep2.x=450;
 e->pos_rep2.y=450;
 
 e->pos_rep1.x=450;
 e->pos_rep1.y=300;
 
 
}

int aleatoire(int n)
{

int alea;

do{
    srand(time(NULL));
    alea=1+rand()%n;
  }

while(alea==0||alea>n);
  
 
  return alea;

}



int compter_nombre_de_ligne_fichier(char* nom_fich)
{

int i;

FILE* f=NULL;

char chaine[265]="";

f=fopen(nom_fich,"r");

if(f!=NULL)
{

   while(fgets(chaine,256,f)!=NULL)
    {
        i++;  // i contient le nmbre de ligne de ton fichier
    }

fclose(f);
}

return i;


}

char return_solution(char* nom_fich,enigme *e)
{

 FILE* f=NULL;
 int n_ligne=0,ligne,j,k=0;
 int trouve;
 int solu[50];

 trouve=0;
 char chaine[256]="";
 char caractere;

 TTF_Font *police1 =NULL;
 TTF_Font *police2 =NULL;


 SDL_Color coulerNoir= {255,255,255};
 TTF_Init();

 police1 = TTF_OpenFont("police1.ttf",55);
 police2 = TTF_OpenFont("police1.ttf",65);


 
 ligne=compter_nombre_de_ligne_fichier("fichier.txt");
 j=aleatoire(ligne);      


// Ouvrir Le fichier
f=fopen(nom_fich,"r");
if(f!=NULL)
{

while (fgets(chaine,sizeof(chaine),f)!=NULL && j!=n_ligne)

{ n_ligne ++;}

if(j==n_ligne)
{


k=0;

do {
     caractere=fgetc(f);
     e->question[k]=caractere;
     k++;
   }while(caractere!='?');


k=0;

do {
     caractere=fgetc(f);
     e->r1[k]=caractere;
     k++;
   }while(caractere!='.');

k=0;

do {
     caractere=fgetc(f);
     e->r2[k]=caractere;
     k++;
   }while(caractere!='.');

k=0;

do {
     caractere=fgetc(f);
     //e->solution[k]=caractere;
     solu[k]=caractere;
     k++;
    }while(caractere!='.');

}

fclose(f);
}

 // Charge texte
 e->q =TTF_RenderText_Blended(police1,e->question,coulerNoir);
 e->rep1 =TTF_RenderText_Blended(police1,e->r1,coulerNoir);
 e->rep2 =TTF_RenderText_Blended(police1,e->r2,coulerNoir);

 TTF_CloseFont(police1);
 TTF_CloseFont(police2);
 TTF_Quit();

 return solu[0];

}


void afficher_enigme(SDL_Surface * screen,char* nom_fich, enigme *e)
{

e->fonds=IMG_Load("font.png");
  
// Blit
SDL_BlitSurface(e->fonds,NULL,screen, &(e->position_fonds));
SDL_BlitSurface(e->q,NULL,screen, &(e->pos_q));
SDL_BlitSurface(e->rep1,NULL,screen, &(e->pos_rep1));
SDL_BlitSurface(e->rep2,NULL,screen, &(e->pos_rep2));


}



int resolution (char* nom_fich,enigme *e, SDL_Surface *screen,int *a,int *b,char solution)
{
  int r,k=0,res;
  char ch;

  if (*a >e->pos_rep1.x && *a< e->pos_rep1.x+e->pos_rep1.w && *b >e->pos_rep1.y && *b < e->pos_rep1.y+e->pos_rep1.h)
            
    ch='a';
     
  else if (*a >e->pos_rep2.x && *a< e->pos_rep2.x+e->pos_rep2.w && *b >e->pos_rep2.y && *b < e->pos_rep2.y+e->pos_rep2.h)
                
     ch='b';
   
   if(ch==solution)
     
       r=1;
   else 
      
       r=0;
   return r;
}
