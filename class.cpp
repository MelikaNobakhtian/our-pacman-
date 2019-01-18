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
          SDL_FreeSurface( fruitsurf );
	}

	
	
};


