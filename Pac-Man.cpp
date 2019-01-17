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
bool quit=false;
SDL_Event event;

void init(){
	
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	
	window= SDL_CreateWindow("Pac-Man", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
	 
}

//SDL_Texture* loadTexture( std::string path )
//{
//    SDL_Texture* newTexture = NULL;
//    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
//    SDL_Texture* newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
//    SDL_FreeSurface( loadedSurface );
//    return newTexture;
//}

void close()
{
	
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow( window );
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	srand(time(0));
	init();//
	while(!quit){
		while(SDL_PollEvent(&event)!=0){
			if( event.type == SDL_QUIT )
			{
				quit = true;
				return;
			}
		}
	}
	close();
}
