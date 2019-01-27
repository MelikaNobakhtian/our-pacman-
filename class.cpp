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
int Blocks[55][4]={{20,68,620,78},{20,68,30,282},{20,272,138,282},{128,272,138,356},{20,346,138,356},
{20,400,138,410},{128,400,138,484},{20,474,138,484},{20,484,30,732},{20,722,620,732},
{610,474,620,732},{502,474,620,484},{502,400,512,484},{502,400,620,410},{502,346,620,356},
{502,272,512,356},{502,272,620,282},{610,68,620,282},{310,68,330,164},{74,122,138,164},
{182,122,266,164},{374,122,458,164},{502,122,566,164},{74,208,138,228},{502,208,566,228},
{182,208,202,356},{182,272,256,292},{246,208,394,228},{310,208,330,292},{374,272,458,292},
{438,208,458,356},{246,336,298,346},{342,336,394,346},{246,336,256,420},{384,336,394,420},
{246,410,394,420},{182,400,202,484},{438,400,458,484},{246,464,394,484},{310,464,330,548},
{74,528,138,548},{118,528,138,612},{182,528,266,548},{374,528,458,548},{502,528,566,548},
{502,528,522,612},{20,592,74,612},{566,592,620,612},{74,656,256,676},{182,592,202,676},
{236,592,384,612},{300,592,320,676},{374,656,566,676},{438,592,458,676},{298,338,342,344}};

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
			pac[i].x=i*20;
			pac[i].y=0;
			pac[i].w=20;
			pac[i].h=20;
		}
	SDL_FreeSurface( pacsurf );
}

void initdead( std::string path ){
	 SDL_Surface* pacsurf= IMG_Load( path.c_str() );
      	deadpac=SDL_CreateTextureFromSurface( rend, pacsurf);
		for(int i=0; i<11;i++){
			dead[i].x=i*20;
			dead[i].y=0;
			dead[i].w=20;
			dead[i].h=20;
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
			fruit[i].x=i*20;
			fruit[i].y=0;
			fruit[i].w=20;
			fruit[i].h=20;
		}
      SDL_FreeSurface( fruitsurf);
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
