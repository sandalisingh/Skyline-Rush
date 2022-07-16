#ifndef Road_h
#define Road_h


#include "TextureManager.h"

class Road;

//------------------------------->>>>>>>>>>  R  O  A  D <<<<<<<<<<-------------------------------------

class Road: public TextureManager{
    protected:
        SDL_Rect destRect;
    
    public:
        
        
        int Leftmost_X; //250
        int Top_Y;   //0
        int Rightmost_X;    //550
        int Bottom_Y;   //640

        int width, length;
        
        Coord pos;

        
        Road(SDL_Renderer *ren);
        //~Road();

        void Update(int);
        bool Render(SDL_Renderer *renderer);

        // friend void Game :: Update_PoliceCarPosition(int i);
        // friend void Game :: Update_UserCarPosition();

};

Road :: Road(SDL_Renderer *ren){
    if(!Load_Image_Texture(TextureManager::ROAD_, ren)){
        cout<<"\n> Road : failed to lad image";
    }

    //Start & End Points of the Road
    Leftmost_X = 200; 
    Top_Y = 0;   
    Rightmost_X = 600;
    Bottom_Y = 640;

    width = (Rightmost_X - Leftmost_X);
    length = 1000;

    pos.set(200,0);
    
    destRect.h = length;
    destRect.w = width;
    destRect.x = Leftmost_X;
    destRect.y = Top_Y;
}

void Road :: Update(int speed){
    destRect.h = length;
    destRect.w = width;
    destRect.x = Leftmost_X;
    destRect.y = pos.y;

    pos.y = pos.y - speed;

    if(pos.y <= -350){
        pos.y = 0;
    }
}

bool Road :: Render(SDL_Renderer *renderer){
    return ( SDL_RenderCopy(renderer, Texture, NULL, &destRect) == 0 );
}

#endif  /* Road_h */
