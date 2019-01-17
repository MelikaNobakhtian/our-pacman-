#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL2_rotozoom.h>
#include <string>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<SDL2/SDL_ttf.h>
using namespace std;

const int SCREEN_WIDTH = 481;
const int SCREEN_HEIGHT = 720;
SDL_Surface* Surface=NULL;
SDL_Window* window=NULL;
SDL_Renderer* rend=NULL;
SDL_Texture * texture=NULL;
SDL_Surface * image=NULL;
bool quit=false;
SDL_Event event;

void init(){
SDL_Init(SDL_INIT_EVERYTHING);
window= SDL_CreateWindow("Project", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
if(!window){
	printf("error creating window: %s\n", SDL_GetError());
	SDL_Quit();
}
rend= SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
if (!rend)
 {
     printf("error creating renderer: %s\n", IMG_GetError());
     getchar();
     SDL_DestroyWindow(window);
     SDL_Quit();
 }
image = IMG_Load("spritesheet.png");
texture = SDL_CreateTextureFromSurface(renderer, image);
SDL_SetRenderDrawColor( rend, 0xFF, 0xFF, 0xFF, 0xFF );
TTF_Init();
}

void close()
{
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow( window );
	SDL_Quit();
}
