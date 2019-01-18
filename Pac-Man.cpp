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

class ghost
{
public:
      int x1;
      int x2;
      int y1;
      int y2;
      float vx;
      float vy;
      SDL_Rect png[8];
      SDL_Texture ghost;
      SDL_Rect blue[4];
      SDL_Texture blueghost;
      SDL_Rect eyes[4];
      SDL_Texture ghosteyes;
      void initghost ( std::string path ){
      	SDL_Surface* ghostsurf= IMG_Load( path.c_str() );
      	ghost=SDL_CreateTextureFromSurface( rend, ghostsurf);
		for(int i=0; i<8;i++){
			png[i].x=i*20;
			png[i].y=0;
			png[i].w=20;
			png[i].h=20;
		}
		SDL_FreeSurface( ghostsurf );
      }
      
      void blueinit(std::string path)
      {
      	SDL_Surface* ghostsurf= IMG_Load( path.c_str() );
      	blueghost=SDL_CreateTextureFromSurface( rend, ghostsurf);
		for(int i=0; i<4;i++){
			blue[i].x=i*20;
			blue[i].y=0;
			blue[i].w=20;
			blue[i].h=20;
		}
		SDL_FreeSurface( ghostsurf );
	  }

	void initeyes(std::string path)
      {
      	SDL_Surface* ghostsurf= IMG_Load( path.c_str() );
      	ghosteyes=SDL_CreateTextureFromSurface( rend, ghostsurf);
		for(int i=0; i<4;i++){
			eyes[i].x=i*20;
			eyes[i].y=0;
			eyes[i].w=20;
			eyes[i].h=20;
		}
		SDL_FreeSurface( ghostsurf );
	  }
	  
      void show()
	  {

      }

     

      void changepng(){

      }
};
ghost Inky;
ghost Pinky;
ghost Blinky;
ghost Clyde;


class pacman
{
  public:
  	int x1;
    int x2;
    int y1;
    int y2;
	float vx;
	float vy;
	SDL_Rect pac[8];
    SDL_Texture pacman;
    SDL_Rect dead[11];
    SDL_Texture deadpac;

void initpacman( std::string path ){
	 SDL_Surface* pacsurf= IMG_Load( path.c_str() );
      	pacman=SDL_CreateTextureFromSurface( rend, pacsurf);
		for(int i=0; i<8;i++){
			png[i].x=i*20;
			png[i].y=0;
			png[i].w=20;
			png[i].h=20;
		}
	SDL_FreeSurface( pacsurf );
}

void initdead( std::string path ){
	 SDL_Surface* pacsurf= IMG_Load( path.c_str() );
      	deadpac=SDL_CreateTextureFromSurface( rend, pacsurf);
		for(int i=0; i<11;i++){
			png[i].x=i*20;
			png[i].y=0;
			png[i].w=20;
			png[i].h=20;
		}
	SDL_FreeSurface( pacsurf );
}

void show

 void move(int x1,int x2,int y1,int y2,float vx,float vy){
      if(){
        y1+=vy;
        y2+=vy;
      }
      if(){
      	x1+=vx;
      	x2+=vy;
      }
      }


};
pacman Player;

class fruit
{
 public:
	int x1;
	int x2;
	int y1;
	int y2;
	SDL_Rect fruit[7];
	SDL_Texture food;

	void initfruit( std::string path ){
		SDL_Surface* fruitsurf= IMG_Load( path.c_str() );
      	food=SDL_CreateTextureFromSurface( rend, fruitsurf);
		for(int i=0; i<11;i++){
			png[i].x=i*20;
			png[i].y=0;
			png[i].w=20;
			png[i].h=20;
		}
      SDL_FreeSurface( fruitsurf)
	}

	
	
};
fruit Foody;

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
	init();
	Blinky.initghost("Blinky.png");
	Pinky.initghost("Pinky.png");
	Inky.initghost("Inky.png");
	Clyde.initghost("Clyde.png");
	Blinky.blueinit("Blue Ghosts.png");
	Inky.blueinit("Blue Ghosts.png");
	Pinky.blueinit("Blue Ghosts.png");
	Clyde.blueinit("Blue Ghosts.png");
	Blinky.initeyes("A pair of Eyes.png");
	Inky.initeyes("A pair of Eyes.png");
	Pinky.initeyes("A pair of Eyes.png");
	Clyde.initeyes("A pair of Eyes.png");
	Player.initpacman("");
	Player.initdead("");
	Foody.initfruit("");
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
