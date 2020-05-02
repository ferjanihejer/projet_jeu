#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "enigme.h"


int main()
{


// Declaration

SDL_Surface *screen;
SDL_Surface *background;
SDL_Surface *passed;
SDL_Surface *failed;
Mix_Chunk *bip;

SDL_Rect position_passed;
SDL_Rect position_failed;
SDL_Rect positionbackground;


char solution;
char pause;
int done=1;
int r=-1,res;
int k,x;
int a=0;
int b=0;

enigme e;

if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
{
	printf("%s",Mix_GetError());
}
bip = Mix_LoadWAV("mus.wav");

if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        printf("Unable to inizialize SDL: %s \n",SDL_GetError());
        return 1;
    }



// Creation screen

screen=SDL_SetVideoMode(1300,800,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
SDL_FillRect (screen,NULL,SDL_MapRGB(screen->format,128,0,0));

    if(screen==NULL)
    {
        printf("Unable to set video mode : %s",SDL_GetError());
        return 1;
    }



// Ajouter background
    
  background=IMG_Load("back.png");
    if(background==NULL)
    {
        printf("Unable to load background: %s\n",SDL_GetError());
        return 1;
    }
    positionbackground.x=0;
    positionbackground.y=0;


// image passed

    passed=IMG_Load("passed.png");
    if(passed==NULL)
    {
        printf("Unable to load passed : %s\n",SDL_GetError());
        return 1;
    }
    
   position_passed.x=235;
   position_passed.y=100;


// image failed

    failed=IMG_Load("failed.png");
    if(failed==NULL)
    {
        printf("Unable to load failed : %s\n",SDL_GetError());
        return 1;
    }
    
   position_failed.x=235;
   position_failed.y=100;


init_enigme(&e,"fichier.txt");

solution=return_solution("fichier.txt",&e);

 
while(done){

SDL_Event event;

SDL_BlitSurface(background,NULL,screen,&positionbackground);

afficher_enigme(screen,"fichier.txt",&e);


while(SDL_PollEvent(&event))
{switch(event.type)
  {


case SDL_QUIT:
  {done=0;
break;}

case SDL_KEYDOWN:
{
  
if(event.key.keysym.sym==SDLK_ESCAPE)
{ done=0;
break;
}}


          case SDL_MOUSEBUTTONDOWN:
             {
              a=event.button.x;
              b=event.button.y ;

              r=resolution ("fichier.txt",&e,screen,&a,&b,solution);
              
           break;
             }


         case SDL_MOUSEBUTTONUP:
             {
              a=event.button.x;
              b=event.button.y ;

              r=resolution ("fichier.txt",&e,screen,&a,&b,solution);
              
         break;
             }

}

if(r==0)
 
{
 Mix_PlayChannel(1, bip,0);
SDL_BlitSurface(failed,&positionbackground,screen,&position_failed);

SDL_Delay(200);
done=0;
}


else if (r==1)

{
Mix_PlayChannel(1, bip,0);
SDL_BlitSurface(passed,&positionbackground,screen,&position_passed);
SDL_Delay(200);
done=0;

}


SDL_Flip(screen);

}
}




// Liberation memoire


SDL_FreeSurface(background);
SDL_Quit();
SDL_Delay(10);
pause=getchar();

return 0;

}
        
    
