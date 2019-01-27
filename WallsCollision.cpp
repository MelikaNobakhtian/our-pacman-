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

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 800;
SDL_Surface* Surface=NULL;
SDL_Window* window=NULL;
SDL_Renderer* rend=NULL;
bool quit=false;
int count=0;
SDL_Event event;
class pacman;
int i;
int Blocks[55][4]={{20,68,620,78},{20,68,30,282},{20,272,138,282},{128,272,138,356},{20,346,138,356},
{20,400,138,410},{128,400,138,484},{20,474,138,484},{20,484,30,730},{20,720,620,730},
{610,474,620,730},{502,474,620,484},{502,400,512,484},{502,400,620,410},{502,346,620,356},
{502,272,512,356},{502,272,620,282},{610,68,620,282},{310,68,330,164},{74,122,138,164},
{182,122,266,164},{374,122,458,164},{502,122,566,164},{74,208,138,228},{502,208,566,228},
{182,208,202,356},{182,272,266,292},{246,208,394,228},{310,208,330,292},{374,272,458,292},
{438,208,458,356},{246,336,298,346},{342,336,394,346},{246,336,256,420},{384,336,394,420},
{246,410,394,420},{182,400,202,484},{438,400,458,484},{246,464,394,484},{310,464,330,548},
{74,528,138,548},{118,528,138,612},{182,528,266,548},{374,528,458,548},{502,528,566,548},
{502,528,522,612},{20,592,74,612},{566,592,620,612},{74,656,266,676},{182,592,202,676},
{246,592,394,612},{310,592,330,676},{374,656,566,676},{438,592,458,676},{298,338,342,344}};
TTF_Font* font;


class score{
public:
	SDL_Texture* scoretex;
	SDL_Color color={255,255,255};
	int num=0;
	int texH=0;
	int texW=0;
	char scorestring[10];
	SDL_Surface* scoresurf;
	SDL_Rect scorerect={138,28,0,0};

	void showScore(){
		sprintf(scorestring, "%d", num);
		scoresurf=TTF_RenderText_Solid(font,scorestring,color);
		scoretex=SDL_CreateTextureFromSurface(rend,scoresurf);
		SDL_QueryTexture(scoretex,NULL,NULL,&texW, &texH);
		scorerect.h=texH; scorerect.w=texW;
		SDL_RenderCopy(rend,scoretex,NULL,&scorerect);
		SDL_DestroyTexture(scoretex);
		SDL_FreeSurface(scoresurf);
	}
}Score;

class ghost
{
public:
      int x1;
      int x2;
      int y1;
      int y2;
      int time=0;
      float vx;
      float vy;
      bool turnedblue=false;
      bool turnedtoeyes=false;
      bool backtocenter=false;
      SDL_Rect png[8];
      SDL_Texture* ghost;
      SDL_Rect blue[4];
      SDL_Texture* blueghost;
      SDL_Rect eyes[4];
      SDL_Rect ghostpos={x1,y1,44,44};
      SDL_Texture* ghosteyes;
      bool horizontal=true;
      bool vertical=true;
      bool includewhiterect=false;
      int direction;
      void initghost ( std::string path ){
      	SDL_Surface* ghostsurf= IMG_Load( path.c_str() );
      	ghost=SDL_CreateTextureFromSurface( rend, ghostsurf);
		for(int i=0; i<8;i++){
			png[i].x=i*44;
			png[i].y=0;
			png[i].w=44;
			png[i].h=44;
		}
		SDL_FreeSurface( ghostsurf );
      }
      
      void blueinit(std::string path)
      {
      	SDL_Surface* ghostsurf= IMG_Load( path.c_str() );
      	blueghost=SDL_CreateTextureFromSurface( rend, ghostsurf);
		for(int i=0; i<4;i++){
			blue[i].x=i*44;
			blue[i].y=0;
			blue[i].w=44;
			blue[i].h=44;
		}
		SDL_FreeSurface( ghostsurf );
	  }

	void initeyes(std::string path)
      {
      	SDL_Surface* ghostsurf= IMG_Load( path.c_str() );
      	ghosteyes=SDL_CreateTextureFromSurface( rend, ghostsurf);
		for(i=0; i<4;i++){
			eyes[i].x=i*44;
			eyes[i].y=0;
			eyes[i].w=44;
			eyes[i].h=44;
		}
		SDL_FreeSurface( ghostsurf );
	  }
	  
      void show(int x, int y)
	  {
		if(turnedblue){
			time++;
			x1=x;
			y1=y;
			x1+=vx;
      		y1-=vy;
      		if(x<615 && x>25)
      			ghostCollision();
      		if(direction%2){
      			direction--;
			  }else{
			  	direction++;
			  }
			ghostpos.x=x1; ghostpos.y=y1;
			if(ghostpos.x>640) x1=-44;
			else if(ghostpos.x<-44) x1=640;
			if(time>450) {
				turnedblue=false;
				time=0;
				count=0;
			}
			else if(time<400){
				SDL_RenderCopy(rend,blueghost,&blue[direction%2],&ghostpos);
			}
			else if(time%4==0 || time%4==1){
				SDL_RenderCopy(rend,blueghost,&blue[direction%2],&ghostpos);
			}else{
				SDL_RenderCopy(rend,blueghost,&blue[direction%2+2],&ghostpos);
			}	
		}
		else if(turnedtoeyes){
			x1=x;
			y1=y;
      		x1+=vx;
	      	y1-=vy;
    	  		ghosteyeCollision();
			ghostpos.x=x1; ghostpos.y=y1;
			if(ghostpos.x>640) x1=-44;
			else if(ghostpos.x<-44) x1=640;
			SDL_RenderCopy(rend,ghosteyes,&eyes[direction/2],&ghostpos);
		}
		else if(backtocenter){
			time++;
			if(y<354){
				vx=0;
				vy=-2;
				changepng();
			}else if(y==354){
				y+=2;
				vy=0;
				vx=2;
				changepng();
			}
			if(x==256) {
				vx*=-1;
				changepng();
			}
			else if(x==384) {
				vx*=-1;
				changepng();
			}
			x1=x;
			y1=y;
			x1+=vx;
			y1-=vy;
			ghostpos.x=x1; ghostpos.y=y1;
			if(time>100){
				backtocenter=false;
				includewhiterect=false;
				time=0;
			}
			SDL_RenderCopy(rend,ghosteyes,&eyes[direction/2],&ghostpos);
			
		}else if(!includewhiterect){
			if(x<298) {
				vy=0;
				vx=2;
				changepng();
			}
			else if(x>298) {
				vy=0;
				vx=-2;
				changepng();
			}
			else if(x==298 && y!=292) {
				vx=0;
				vy=2;
				changepng();
			}
			else{
				if(rand()%2){
					vx=2;
				}
				else{
					vx=-2;
				}
				vy=0;
				changepng();
				includewhiterect=true;
			}
			x1=x;
			y1=y;
			x1+=vx;
			y1-=vy;
			ghostpos.x=x1; ghostpos.y=y1;
			if(direction%2){
	  			direction--;
	  		}else{
	  			direction++;
	  		}
	  		SDL_RenderCopy(rend,ghost,&png[direction],&ghostpos);
		}
		else{
	  		x1=x;
			y1=y;
	  		x1+=vx;
	  		y1-=vy;
	  		if(x<615 && x>25)
	  			ghostCollision();
	  		if(direction%2){
	  			direction--;
	  		}else{
	  			direction++;
	  		}
	  		ghostpos.x=x1; ghostpos.y=y1;
	  		if(ghostpos.x>640) x1=-44;
	  		else if(ghostpos.x<-44) x1=640;
	  		SDL_RenderCopy(rend,ghost,&png[direction],&ghostpos);
		  }
		
      }
	void changepng(){
		if(vx>0) direction=6;
		else if(vx<0) direction=4;
		else if(vy<0) direction=2;
		else direction=0;
      }

    void ghostCollision(){
	bool up=false,down=false,right=false,left=false;
	int n;
	if(includewhiterect) n=55;
	else n=54;
	for(i=0; i<n; i++){
			if(x1+44==Blocks[i][0] && ((y1+1>=Blocks[i][1] && y1+1<=Blocks[i][3]) || (y1+43>=Blocks[i][1] && y1+43<=Blocks[i][3]) || (Blocks[i][1]>y1 && Blocks[i][1]<y1+44)) ){
				right=true;
			}
			if(x1==Blocks[i][2] && ((y1+1>=Blocks[i][1] && y1+1<=Blocks[i][3]) || (y1+43>=Blocks[i][1] && y1+43<=Blocks[i][3]) || (Blocks[i][1]>y1 && Blocks[i][1]<y1+44)) ){
				left=true;
			}
			if(y1+44==Blocks[i][1] && ((x1+1>=Blocks[i][0] && x1+1<=Blocks[i][2]) || (x1+43>=Blocks[i][0] && x1+43<=Blocks[i][2]) || (Blocks[i][0]>x1 && Blocks[i][0]<x1+44)) ){
				down=true;
			}
			if(y1==Blocks[i][3] && ((x1+1>=Blocks[i][0] && x1+1<=Blocks[i][2]) || (x1+43>=Blocks[i][0] && x1+43<=Blocks[i][2]) || (Blocks[i][0]>x1 && Blocks[i][0]<x1+44)) ){
				up=true;
			}
	}
	if(vx!=0){
		if((right && vx>0) || (left && vx<0)){
			vx=0;
			if(rand()%2){
				if(down) vy=2;
				else vy=-2;
				changepng();
			}
			else{
				if(up) vy=-2;
				else vy=2;
				changepng();
			}
		}
		else if((!right && vx>0) || (!left && vx<0)){
			switch(rand()%3){
				case 0: if(!down){
					vx=0;
					vy=-2;
					changepng();
					break;
				}
				case 1: if(!up){
					vx=0;
					vy=2;
					changepng();
					break;
				}
			}
		}
	}else{
		if((down && vy<0) || (up && vy>0)){
			vy=0;
			if(rand()%2){
				if(left) vx=2;
				else vx=-2;
				changepng();
			}
			else{
				if(right) vx=-2;
				else vx=2;
				changepng();
			}
		}
		else if((!down && vy<0) || (!up && vy>0)){
			switch(rand()%3){
				case 0: if(!left){
					vy=0;
					vx=-2;
					changepng();
					break;
				}
				case 1: if(!right){
					vy=0;
					vx=2;
					changepng();
					break;
				}
			}
		}
	}
} 
	void ghosteyeCollision(){
		bool up=false,down=false,right=false,left=false;
		if(ghostpos.x==298 && ghostpos.y==292){
			backtocenter=true;
			turnedtoeyes=false;
			return;
		}
	for(i=0; i<54; i++){
			if(x1+44==Blocks[i][0] && ((y1+1>=Blocks[i][1] && y1+1<=Blocks[i][3]) || (y1+43>=Blocks[i][1] && y1+43<=Blocks[i][3]) || (Blocks[i][1]>y1 && Blocks[i][1]<y1+44)) ){
				right=true;
			}
			if(x1==Blocks[i][2] && ((y1+1>=Blocks[i][1] && y1+1<=Blocks[i][3]) || (y1+43>=Blocks[i][1] && y1+43<=Blocks[i][3]) || (Blocks[i][1]>y1 && Blocks[i][1]<y1+44)) ){
				left=true;
			}
			if(y1+44==Blocks[i][1] && ((x1+1>=Blocks[i][0] && x1+1<=Blocks[i][2]) || (x1+43>=Blocks[i][0] && x1+43<=Blocks[i][2]) || (Blocks[i][0]>x1 && Blocks[i][0]<x1+44)) ){
				down=true;
			}
			if(y1==Blocks[i][3] && ((x1+1>=Blocks[i][0] && x1+1<=Blocks[i][2]) || (x1+43>=Blocks[i][0] && x1+43<=Blocks[i][2]) || (Blocks[i][0]>x1 && Blocks[i][0]<x1+44)) ){
				up=true;
			}
	}
	if(vx!=0){
		if((right && vx>0) || (left && vx<0)){
			vx=0;
			if(ghostpos.y>292 && !up) vy=2;
			else if(ghostpos.y<292 && !down) vy=-2;
			else if (up) vy=-2;
			else vy=2;
			changepng();
		}
		else if((!right && vx>0) || (!left && vx<0)){
			if(ghostpos.y>292 && !up) {
				if((vx<0 && ghostpos.x<298) || (vx>0 && ghostpos.x>298)){
					vx=0;
					vy=2;
				}
			}else if(ghostpos.y<292 && !down) {
				if((vx<0 && ghostpos.x<298) || (vx>0 && ghostpos.x>298)){
					vx=0;
					vy=-2;
				}
			}
			changepng();
	}}else{
		if((down && vy<0) || (up && vy>0)){
			vy=0;
			if(ghostpos.x>298 && !left) vx=-2;
			else if(ghostpos.x<298 && !right) vx=2;
			else if (left) vy=2;
			else vy=-2;
		}
		else if((!down && vy<0) || (!up && vy>0)){
			if(ghostpos.x>298 && !left) {
				if((vy<0 && ghostpos.y>292) || (vy>0 && ghostpos.y<292)){
					vy=0;
					vx=-2;
				}
			}else if(ghostpos.x<298 && !right) {
				if((vy<0 && ghostpos.y>292) || (vy>0 && ghostpos.y<292)){
					vy=0;
					vx=2;
				}
		}
	}
	changepng();
	}
}
    

      void ghostpacmanCollision();
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
    float vx=0;
    float vy=0;
    SDL_Rect pac[9];
    SDL_Texture* pacman;
    SDL_Rect dead[11];
    SDL_Texture* deadpac;
    SDL_Rect Pacmanpos={x1,y1,44,44};
    int pacdirection;

void initpacman( std::string path ){
	 SDL_Surface* pacsurf= IMG_Load( path.c_str() );
      	pacman=SDL_CreateTextureFromSurface( rend, pacsurf);
		for(i=0; i<8;i++){
			pac[i].x=(i%2)*44;
			pac[i].y=(i/2)*44;
			pac[i].w=44;
			pac[i].h=44;
		}
	pac[8].x=88; pac[8].y=0; pac[8].w=44; pac[8].h=44;
	SDL_FreeSurface( pacsurf );
}

void initdead( std::string path ){
	 SDL_Surface* pacsurf= IMG_Load( path.c_str() );
      	deadpac=SDL_CreateTextureFromSurface( rend, pacsurf);
		for(int i=0; i<11;i++){
			dead[i].x=i*48;
			dead[i].y=0;
			dead[i].w=48;
			dead[i].h=48;
		}
	SDL_FreeSurface( pacsurf );
}

bool pacshow(int x, int y){
	x1=x;
	y1=y;
	PacmanWallCollision(vx,vy);
	x1+=vx;
	y1-=vy;
	if(vx || vy){
		if(pacdirection%2){
	  		pacdirection--;
	  	}else{
	  		pacdirection++;
	  	}
	}else if(pacdirection%2){
		pacdirection--;
	}
 	Pacmanpos.x=x1; Pacmanpos.y=y1;
 	if(Pacmanpos.x>640) {
 		x1=-44;
 	}
 	else if(Pacmanpos.x<-44) x1=640;
	SDL_RenderCopy(rend,pacman,&pac[pacdirection],&Pacmanpos);
}

 void move(int x1,int x2,int y1,int y2,float vx,float vy){
      //if(){
        //y1+=vy;
        //y2+=vy;
      //}
      /*if(){
      	x1+=vx;
      	x2+=vy;
      }*/
      }

 bool PacmanWallCollision(int v1, int v2){
    bool up=false,down=false,right=false,left=false;
	for(i=0; i<54; i++){
		if(v1!=0){
			if(x1+44==Blocks[i][0] && ((y1+1>=Blocks[i][1] && y1+1<=Blocks[i][3]) || (y1+43>=Blocks[i][1] && y1+43<=Blocks[i][3]) || (Blocks[i][1]>y1 && Blocks[i][1]<y1+44)) ){
				right=true;
			}
			else if(x1==Blocks[i][2] && ((y1+1>=Blocks[i][1] && y1+1<=Blocks[i][3]) || (y1+43>=Blocks[i][1] && y1+43<=Blocks[i][3]) || (Blocks[i][1]>y1 && Blocks[i][1]<y1+44)) ){
				left=true;
			}
		}
		else{
			if(y1+44==Blocks[i][1] && ((x1+1>=Blocks[i][0] && x1+1<=Blocks[i][2]) || (x1+43>=Blocks[i][0] && x1+43<=Blocks[i][2]) || (Blocks[i][0]>x1 && Blocks[i][0]<x1+44)) ){
				down=true;
			}
			else if(y1==Blocks[i][3] && ((x1+1>=Blocks[i][0] && x1+1<=Blocks[i][2]) || (x1+43>=Blocks[i][0] && x1+43<=Blocks[i][2]) || (Blocks[i][0]>x1 && Blocks[i][0]<x1+44)) ){
				up=true;
			}
		}
	} 
	if(v1==vx && v2==vy){
		if(vx>0 && right) vx=0;
	else if(vx<0 && left) vx=0;
	else if(vy>0 && up) vy=0;
	else if(vy<0 && down) vy=0;
	return true;
	}
	else {
		if((v1>0 && right) || (v1<0 && left) || (v2>0 && up) || (v2<0 && down)) return false;
		else return true;
	}
}

	void showdead();


};
pacman Player;

void ghost::ghostpacmanCollision(){
      	if(turnedblue){
      		if( SDL_HasIntersection( &ghostpos , &Player.Pacmanpos )){
		count++;
		Score.num+=pow(2,count)*100;
		time=0;
		turnedtoeyes=true;
		turnedblue=false;
		}
	} else if(!turnedtoeyes && SDL_HasIntersection( &ghostpos,&Player.Pacmanpos) ){
		Player.showdead();
		}
}

class fruit
{
 public:
	int x1;
	int x2;
	int y1;
	int y2;
	SDL_Texture* food;
	SDL_Rect fruitpos={x1,y1,44,44};
	bool appeared=false;
	int timetoappear= 150;
	int timetogo=345;

	void initfruit( std::string path ){
		SDL_Surface* fruitsurf= IMG_Load( path.c_str() );
      	food=SDL_CreateTextureFromSurface( rend, fruitsurf);
      SDL_FreeSurface( fruitsurf);
	}

	void showfruit(int x, int y){
		x1=x;
		y1=y;
		fruitpos.x=x1; fruitpos.y=y1;
		SDL_RenderCopy(rend,food,NULL,&fruitpos);
	}

	void fruitCollision(){
		if( SDL_HasIntersection( &fruitpos , &Player.Pacmanpos )){
			appeared=false;
			switch(rand()%5){
				case 0: Score.num+=100;
				break;
				case 1: Score.num+=300;
				break;
				case 2: Score.num+=500;
				break;
				case 3: Score.num+=700;
				break;
				default: Score.num+=1000;
			}
		}
	}
	
};
fruit Foody;

class dot{
	
	public:
	int x1;
	int y1;
	int w;
	int h;
	bool turnedtouch[300]={false};
    SDL_Rect dotpos={x1,y1,w,h};
    int dots[300][2];

	void initdots(){
	
for(i=1;i<27;i+=2){
	if(i==13)continue;
	dots[i-1][0]=30+((i+1)*11+(i-1)/2*21)-3;
	dots[i-1][1]=78+19;
}
for(i=27;i<53;i+=2){
	dots[i-1][0]=30+((i-26+1)*11+(i-27)/2*21)-3;
	dots[i-1][1]=78+105;
}
for(i=53;i<79;i+=2){
	if(i==59 || i==65 || i==71) continue;
	dots[i-1][0]=30+((i-51)*11+(i-53)/2*21)-3;
	dots[i-1][1]=78+170;
}
for(i=79; i<105; i+=2){
	if(i==91)continue;
	dots[i-1][0]=30+((i-77)*11+(i-79)/2*21)-3;
	dots[i-1][1]=503;
}
for(i=105;i<131;i+=2){
	if(i==111 || i==117 || i==123) continue;
	dots[i-1][0]=30+((i-103)*11+(i-105)/2*21)-3;
	dots[i-1][1]=631;
}
for(i=131;i<157;i+=2){
	dots[i-1][0]=30+((i-130+1)*11+(i-131)/2*21)-3;
	dots[i-1][1]=697;
}
for(i=157;i<183;i+=2){
	if(i==161 || i==179) continue;
	dots[i-1][0]=30+((i-156+1)*11+(i-157)/2*21)-3;
	dots[i-1][1]=567;
}
for(i=2;i<28;i+=2){
	if(i==14)continue;
	dots[i-1][0]=30+((i)*11+(i)/2*21)-2;
	dots[i-1][1]=78+20;
}
for(i=28;i<54;i+=2){
	dots[i-1][0]=30+((i-26)*11+(i-26)/2*21)-2;
	dots[i-1][1]=78+106;
}
for(i=54;i<80;i+=2){
	if(i==60 || i==66 || i==72) continue;
	dots[i-1][0]=30+((i-52)*11+(i-52)/2*21)-2;
	dots[i-1][1]=78+171;
}
for(i=80; i<106; i+=2){
	if(i==92)continue;
	dots[i-1][0]=30+((i-78)*11+(i-78)/2*21)-2;
	dots[i-1][1]=504;
}
for(i=106;i<132;i+=2){
	if(i==112 || i==118 || i==124) continue;
	dots[i-1][0]=30+((i-104)*11+(i-104)/2*21)-2;
	dots[i-1][1]=632;
}
for(i=132;i<158;i+=2){
	dots[i-1][0]=30+((i-130)*11+(i-130)/2*21)-2;
	dots[i-1][1]=698;
}
for(i=158;i<184;i+=2){
	if(i==160 || i==178) continue;
	dots[i-1][0]=30+((i-156)*11+(i-156)/2*21)-2;
	dots[i-1][1]=568;
}
dots[12][0]=49; dots[12][1]=140;
dots[58][0]=350; dots[58][1]=140;
dots[64][0]=477; dots[64][1]=140;


dots[70][0]=157; dots[70][1]=117;
dots[90][0]=285; dots[90][1]=117;
dots[110][0]=585; dots[110][1]=117;


dots[13][0]=158; dots[13][1]=140;
dots[59][0]=286; dots[59][1]=140;
dots[65][0]=586; dots[65][1]=140;


dots[71][0]=50; dots[71][1]=118;
dots[91][0]=351; dots[91][1]=118;
dots[111][0]=478; dots[111][1]=118;


dots[182][0]=285;dots[182][1]=161;
dots[184][0]=585;dots[184][1]=161;
dots[186][0]=157;dots[186][1]=161;


dots[183][0]=50;dots[183][1]=162;
dots[185][0]=351;dots[185][1]=162;
dots[187][0]=478;dots[187][1]=162;


dots[189][0]=50;dots[189][1]=225;
dots[191][0]=50;dots[191][1]=205;

dots[193][0]=478;dots[193][1]=225;
dots[195][0]=478;dots[195][1]=205;

dots[197][0]=586;dots[197][1]=225;
dots[199][0]=586;dots[199][1]=205;

dots[201][0]=158;dots[201][1]=225;
dots[203][0]=158;dots[203][1]=205;

dots[205][0]=222;dots[205][1]=225;
dots[207][0]=222;dots[207][1]=205;

dots[209][0]=415;dots[209][1]=225;
dots[211][0]=415;dots[211][1]=205;

for(i=189;i<207;i+=2){
	if(i==203)continue;
	dots[i-1][1]=78+170+((i-188+1)*11+(i-189)/2*21)-3;
	dots[i-1][0]=477;
}
for(i=214;i<230;i+=2){
	if(i==224 )continue;
	dots[i-1][1]=78+170+((i-212)*11+(i-212)/2*21)-2;
	dots[i-1][0]=478;
}

for(i=207;i<225;i+=2){
	if(i==221)continue;
	dots[i-1][1]=78+170+((i-206+1)*11+(i-207)/2*21)-3;
	dots[i-1][0]=157;
}
for(i=230;i<246;i+=2){
	if(i==240 )continue;
	dots[i-1][1]=78+170+((i-228)*11+(i-228)/2*21)-2;
	dots[i-1][0]=158;
}
dots[245][0]=50;dots[245][1]=524;
dots[247][0]=50;dots[247][1]=547;
dots[249][0]=587;dots[249][1]=524;
dots[251][0]=587;dots[251][1]=547;

dots[253][0]=286;dots[253][1]=524;
dots[255][0]=286;dots[255][1]=547;
dots[257][0]=351;dots[257][1]=524;
dots[259][0]=351;dots[259][1]=547;

dots[261][0]=50;dots[261][1]=652;
dots[263][0]=50;dots[263][1]=675;
dots[265][0]=587;dots[265][1]=652;
dots[267][0]=587;dots[267][1]=675;

dots[269][0]=286;dots[269][1]=652;
dots[271][0]=286;dots[271][1]=675;
dots[273][0]=351;dots[273][1]=652;
dots[275][0]=351;dots[275][1]=675;

dots[269][0]=93;dots[269][1]=588;
dots[271][0]=93;dots[271][1]=611;

dots[273][0]=221;dots[273][1]=588;
dots[275][0]=221;dots[275][1]=611;

dots[277][0]=415;dots[277][1]=588;
dots[279][0]=415;dots[279][1]=611;

dots[281][0]=544;dots[281][1]=588;
dots[283][0]=544;dots[283][1]=611;

dots[285][0]=286;dots[285][1]=652;
dots[287][0]=286;dots[287][1]=675;

dots[289][0]=351;dots[289][1]=652;
dots[291][0]=351;dots[291][1]=675;
}

void showDots(){
	int eaten=0;
	for(i=0;i<224;i+=2 ){
		if(!turnedtouch[i]){
			if(i==202 || i==220 || i==156 || i==12) continue;
				boxRGBA(rend,dots[i][0],dots[i][1],dots[i][0]+5,dots[i][1]+5,249, 218, 197,255);
			}
			else eaten++;
		}	

		for(i=1;i<293;i+=2 ){
			if(!turnedtouch[i]){
				if(i==223 || i==239 || i==65 || i==181) continue;
				boxRGBA(rend,dots[i][0],dots[i][1],dots[i][0]+4,dots[i][1]+4,249, 218, 197,255);
			}
			else eaten++;
		}
		if(!turnedtouch[12])
			filledCircleRGBA(rend,dots[12][0]+3,dots[12][1]+3,11,249, 218, 197,255);
		else eaten++;
		if(!turnedtouch[156])
			filledCircleRGBA(rend,dots[156][0]+3,dots[156][1]+3,11,249, 218, 197,255);
		else eaten++;
		if(!turnedtouch[65])
			filledCircleRGBA(rend,dots[65][0]+2,dots[65][1]+2,11,249, 218, 197,255);
		else eaten++;
		if(!turnedtouch[181])
			filledCircleRGBA(rend,dots[181][0]+2,dots[181][1]+2,11,249, 218, 197,255);
		else eaten++;

	if(eaten==254) quit=true;
}

void dotpacmanCollision(){
	SDL_Rect pacmannn={Player.Pacmanpos.x+11,Player.Pacmanpos.y+11,22,22};
	dotpos.w=5;
	dotpos.h=5;
	for(i=0;i<224;i+=2 ){
			if(!turnedtouch[i]){
				if(i==202 || i==220 || i==156 || i==12) continue;
				dotpos.x=dots[i][0];
				dotpos.y=dots[i][1];
				if(SDL_HasIntersection(&dotpos,&pacmannn)){
					Score.num+=10;
					turnedtouch[i]=true;
				}
			}
		}
	dotpos.w=4;
	dotpos.h=4;
	for(i=1;i<293;i+=2 ){
			if(!turnedtouch[i]){
				if(i==223 || i==239 || i==65 || i==181) continue;
				dotpos.x=dots[i][0];
				dotpos.y=dots[i][1];
				if(SDL_HasIntersection(&dotpos,&pacmannn)){
					Score.num+=10;
					turnedtouch[i]=true;
				}
			}
		}
	dotpos.h=22; dotpos.y=22;
	if(!turnedtouch[12]){
		dotpos.x=dots[12][0]-8;
		dotpos.y=dots[12][1]-8;
		if(SDL_HasIntersection(&dotpos,&pacmannn)){
			turnedtouch[12]=true;
			if(!Clyde.turnedtoeyes && !Clyde.backtocenter){
				Clyde.time=0;
				Clyde.turnedblue=true;
			}
			if(!Blinky.turnedtoeyes && !Blinky.backtocenter){
				Blinky.time=0;
				Blinky.turnedblue=true;
			}
			if(!Inky.turnedtoeyes && !Inky.backtocenter){
				Inky.time=0;
				Inky.turnedblue=true;
			}
			if(!Pinky.turnedtoeyes && !Pinky.backtocenter){
				Pinky.time=0;
				Pinky.turnedblue=true;
			}
		}
	}
	if(!turnedtouch[156]){
		dotpos.x=dots[156][0]-8;
		dotpos.y=dots[156][1]-8;
		if(SDL_HasIntersection(&dotpos,&pacmannn)){
			turnedtouch[156]=true;
			if(!Clyde.turnedtoeyes && !Clyde.backtocenter){
				Clyde.time=0;
				Clyde.turnedblue=true;
			}
			if(!Blinky.turnedtoeyes && !Blinky.backtocenter){
				Blinky.time=0;
				Blinky.turnedblue=true;
			}
			if(!Inky.turnedtoeyes && !Inky.backtocenter){
				Inky.time=0;
				Inky.turnedblue=true;
			}
			if(!Pinky.turnedtoeyes && !Pinky.backtocenter){
				Pinky.time=0;
				Pinky.turnedblue=true;
			}
		}
	}
	if(!turnedtouch[65]){
		dotpos.x=dots[65][0]-9;
		dotpos.y=dots[65][1]-9;
		if(SDL_HasIntersection(&dotpos,&pacmannn)){
			turnedtouch[65]=true;
			if(!Clyde.turnedtoeyes && !Clyde.backtocenter){
				Clyde.time=0;
				Clyde.turnedblue=true;
			}
			if(!Blinky.turnedtoeyes && !Blinky.backtocenter){
				Blinky.time=0;
				Blinky.turnedblue=true;
			}
			if(!Inky.turnedtoeyes && !Inky.backtocenter){
				Inky.time=0;
				Inky.turnedblue=true;
			}
			if(!Pinky.turnedtoeyes && !Pinky.backtocenter){
				Pinky.time=0;
				Pinky.turnedblue=true;
			}
		}
	}
	if(!turnedtouch[181]){
		dotpos.x=dots[181][0]-9;
		dotpos.y=dots[181][1]-9;
		if(SDL_HasIntersection(&dotpos,&pacmannn)){
			turnedtouch[181]=true;
			if(!Clyde.turnedtoeyes && !Clyde.backtocenter){
				Clyde.time=0;
				Clyde.turnedblue=true;
			}
			if(!Blinky.turnedtoeyes && !Blinky.backtocenter){
				Blinky.time=0;
				Blinky.turnedblue=true;
			}
			if(!Inky.turnedtoeyes && !Inky.backtocenter){
				Inky.time=0;
				Inky.turnedblue=true;
			}
			if(!Pinky.turnedtoeyes && !Pinky.backtocenter){
				Pinky.time=0;
				Pinky.turnedblue=true;
			}
		}
	}
}
};
dot Dot;



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

void pacman::showdead(){
		for(int j=0;j<12;j++){
		SDL_Delay(50);
		SDL_SetRenderDrawColor( rend, 0, 0, 0, 0xFF );
		SDL_RenderClear( rend );
		for(int i=0;i<54;i++){
					boxRGBA(rend,Blocks[i][0],Blocks[i][1],Blocks[i][2],Blocks[i][3],0,0,255,255);
				}
		boxRGBA(rend,Blocks[54][0],Blocks[54][1],Blocks[54][2],Blocks[54][3],255,255,255,255);
		if(Foody.appeared){
			Foody.showfruit(298,420);
			Foody.fruitCollision();
		} 
		Dot.showDots();
		Pinky.show(Pinky.x1,Pinky.y1);
		Inky.show(Inky.x1,Inky.y1);
		Blinky.show(Blinky.x1,Blinky.y1);
		Clyde.show(Clyde.x1,Clyde.y1);
		Score.showScore();
		SDL_RenderCopy(rend,deadpac,&dead[j],&Pacmanpos);
		SDL_RenderPresent( rend );
		}
		quit=true;
	}


void close()
{
	SDL_DestroyTexture(Blinky.ghosteyes);
	SDL_DestroyTexture(Blinky.ghost);
	SDL_DestroyTexture(Blinky.blueghost);
	SDL_DestroyTexture(Inky.ghosteyes);
	SDL_DestroyTexture(Inky.ghost);
	SDL_DestroyTexture(Inky.blueghost);
	SDL_DestroyTexture(Pinky.ghosteyes);
	SDL_DestroyTexture(Pinky.ghost);
	SDL_DestroyTexture(Pinky.blueghost);
	SDL_DestroyTexture(Clyde.ghosteyes);
	SDL_DestroyTexture(Clyde.ghost);
	SDL_DestroyTexture(Clyde.blueghost);
	SDL_DestroyTexture(Player.pacman);
	SDL_DestroyTexture(Player.deadpac);
	SDL_DestroyTexture(Foody.food);
	SDL_DestroyTexture(Score.scoretex);
	TTF_CloseFont(font);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow( window );
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

void StartMenu(){
	bool ready=true;
	int readytime=0;
	SDL_Surface* readysurf= IMG_Load("ready.png");
    SDL_Texture* readytex=SDL_CreateTextureFromSurface( rend, readysurf);
    SDL_Rect readyrect={258,433,130,20};
    SDL_FreeSurface( readysurf);
	while(ready){
		while(SDL_PollEvent(&event)!=0){
			if( event.type == SDL_QUIT )
			{
				quit = true;
				return ;
			}
		}
		readytime++;
		SDL_Delay(50);
		SDL_SetRenderDrawColor( rend, 0, 0, 0, 0xFF );
		SDL_RenderClear( rend );
		for(int i=0;i<54;i++){
					boxRGBA(rend,Blocks[i][0],Blocks[i][1],Blocks[i][2],Blocks[i][3],0,0,255,255);
				}
		boxRGBA(rend,Blocks[54][0],Blocks[54][1],Blocks[54][2],Blocks[54][3],255,255,255,255);
		Score.showScore();
		Dot.showDots();
		SDL_RenderCopy(rend,Player.pacman,&Player.pac[Player.pacdirection],&Player.Pacmanpos);
		SDL_RenderCopy(rend,Clyde.ghost,&Clyde.png[Clyde.direction],&Clyde.ghostpos);
		SDL_RenderCopy(rend,Blinky.ghost,&Blinky.png[Blinky.direction],&Blinky.ghostpos);
		SDL_RenderCopy(rend,Inky.ghost,&Inky.png[Inky.direction],&Inky.ghostpos);
		SDL_RenderCopy(rend,Pinky.ghost,&Pinky.png[Pinky.direction],&Pinky.ghostpos);
		SDL_RenderCopy(rend,readytex,NULL,&readyrect);
		SDL_RenderPresent( rend );
		if(readytime>50) ready=false;
	}
}

int main( int argc, char* args[] )
{

	srand(time(0));
	init();
	font=TTF_OpenFont("emulogic.ttf",20);
	if(!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
}
	Blinky.initghost("Blinky.png");
	Pinky.initghost("Pinky.png");
	Inky.initghost("Inky.png");
	Clyde.initghost("Clyde.png");
	Blinky.blueinit("Blue Ghosts.png");
	Inky.blueinit("Blue Ghosts.png");
	Pinky.blueinit("Blue Ghosts.png");
	Clyde.blueinit("Blue Ghosts.png");
	Blinky.initeyes("Eyes.png");
	Inky.initeyes("Eyes.png");
	Pinky.initeyes("Eyes.png");
	Clyde.initeyes("Eyes.png");
	Player.initpacman("Pacman.png");
	Foody.initfruit("Cherry.png");
	Player.initdead("Pacman Dying.png");
	Dot.initdots();
	Pinky.direction=1;
	Blinky.direction=3;
	Inky.direction=5;
	Clyde.direction=6;
	Player.pacdirection=2;
	Blinky.x1=298; Blinky.y1=292; Blinky.vx=2;Blinky.vy=0;
	Pinky.x1=254;Pinky.y1=356;Pinky.vx=0; Pinky.vy=-2;
	Inky.x1=298;Inky.y1=356;Inky.vx=-2; Inky.vy=0;
	Clyde.x1=342;Clyde.y1=356;Clyde.vx=0; Clyde.vy=2;
	Player.x1=298; Player.y1=548;
	Blinky.ghostpos.x=298; Blinky.ghostpos.y=292;
	Pinky.ghostpos.x=254;Pinky.ghostpos.y=356;
	Inky.ghostpos.x=298;Inky.ghostpos.y=356;
	Clyde.ghostpos.x=342;Clyde.ghostpos.y=356;
	Player.Pacmanpos.x=298; Player.Pacmanpos.y=548;
	Blinky.includewhiterect=true;
	Score.num=0;
	StartMenu();
	while(!quit){
		while(SDL_PollEvent(&event)!=0){
			if( event.type == SDL_QUIT )
			{
				quit = true;
				return 0;
			}
			else if(event.type==SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                	case SDLK_LEFT:
                	if(Player.PacmanWallCollision(-2,0)){
                		Player.vy=0;
                		Player.vx=-2;
                		if(Player.pacdirection!=0 && Player.pacdirection!=1)
                			Player.pacdirection=0;
                	}
                	break;
                	case SDLK_RIGHT:
                	if(Player.PacmanWallCollision(2,0)){
                		Player.vy=0;
                		Player.vx=2;
                		if(Player.pacdirection!=2 && Player.pacdirection!=3)
                			Player.pacdirection=2;
                	}
                	break;
                	case SDLK_UP:
                	if(Player.PacmanWallCollision(0,2)){
                		Player.vy=2;
                		Player.vx=0;
                		if(Player.pacdirection!=4 && Player.pacdirection!=5)
                			Player.pacdirection=4;
                	}
                	break;
                	case SDLK_DOWN:
                	if(Player.PacmanWallCollision(0,-2)){
                		Player.vy=-2;
                		Player.vx=0;
                		if(Player.pacdirection!=6 && Player.pacdirection!=7)
                			Player.pacdirection=6;
                	}
                	break;
                }
            }
		}
		
		SDL_Delay(50);
		if(Foody.appeared){
			if(rand()%500==Foody.timetogo){
				Foody.appeared=false;
			}
		}else{
			if(rand()%500==Foody.timetoappear){
				Foody.appeared=true;
			}
		}
		SDL_SetRenderDrawColor( rend, 0, 0, 0, 0xFF );
		SDL_RenderClear( rend );
		for(int i=0;i<54;i++){
					boxRGBA(rend,Blocks[i][0],Blocks[i][1],Blocks[i][2],Blocks[i][3],0,0,255,255);
				}
		boxRGBA(rend,Blocks[54][0],Blocks[54][1],Blocks[54][2],Blocks[54][3],255,255,255,255);
		if(Foody.appeared){
			Foody.showfruit(298,420);
			Foody.fruitCollision();
		}
		Dot.dotpacmanCollision();
		Dot.showDots();
		Player.pacshow(Player.x1,Player.y1);
		Pinky.show(Pinky.x1,Pinky.y1);
		Inky.show(Inky.x1,Inky.y1);
		Blinky.show(Blinky.x1,Blinky.y1);
		Clyde.show(Clyde.x1,Clyde.y1);
		Pinky.ghostpacmanCollision();
		Blinky.ghostpacmanCollision();
		Inky.ghostpacmanCollision();
		Clyde.ghostpacmanCollision();
		Score.showScore();
		SDL_RenderPresent( rend );
	}

	close();
	return 0;
}
