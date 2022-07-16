#ifndef Car_h
#define Car_h

#include "TextureManager.h"
#include "GameWindow.h"

class Car;
class User_Car;
class Incoming_Car;

//------------------------------->>>>>>>>>>  C  A  R <<<<<<<<<<-------------------------------------

class Car {
    protected:
        SDL_Rect destRect;
        TextureManager TM;

    public:
        int moveStep;
        
        //CAR DIMENSIONS
        int H;
        int W;
    
        Coord pos;

        Car(int Which_Image, SDL_Renderer *ren);
        virtual void Render(SDL_Renderer *ren) = 0;
};

Car :: Car(int Which_Image, SDL_Renderer *ren){    //creates texture of the car image 
    cout<<"\nCar()";

    TM.Load_Image_Texture(Which_Image, ren);

    //CAR DIMENSIONS
    H = 160;
    W = 85;
}

//------------------------------->>>>>>>>>>  U  S  E  R      C  A  R <<<<<<<<<<-------------------------------------

class User_Car: public Car{
    public:
        

        User_Car(SDL_Renderer *renderer);
        void Render(SDL_Renderer*);
};

User_Car :: User_Car(SDL_Renderer * ren) : Car(TM.CAR_0, ren){
    cout<<"\nUser_Car()";

    moveStep = 30;

    pos.set(( (GameWindow::SCREEN_WIDTH)/2 ) - (W/2) , (GameWindow::SCREEN_HEIGHT) - H);
}

void User_Car:: Render(SDL_Renderer *ren){
    cout<<"\n\tUser_Car :: Render()";

    destRect.x = pos.x;
    destRect.y = pos.y;
    destRect.w = W;
    destRect.h = H;

    SDL_RenderCopyEx(ren, TM.Texture, NULL, &destRect, 0.0, NULL, SDL_FLIP_VERTICAL);  //srcRect = NULL will be rendering the whole texture of the whole car
}

//------------------------------->>>>>>>>>>  P  O  L  I  C  E     C  A  R <<<<<<<<<<-------------------------------------

class Incoming_Car: public Car{
    public:
        // int moveStep;

        Incoming_Car(SDL_Renderer *renderer, int Which_Image);
        void Render(SDL_Renderer*);
};

Incoming_Car :: Incoming_Car(SDL_Renderer * ren, int Which_Image) : Car(Which_Image, ren){
    cout<<"\nIncoming_Car()";

    pos.x = 0;
    pos.y = (GameWindow::SCREEN_HEIGHT);

    moveStep = 2;   //5 tha change kra tha collision aur keep distance check krne ke liye baad m thik krna h
    //NOT 3
}

void Incoming_Car :: Render(SDL_Renderer *ren){
    cout<<"\n\tIncoming_Car :: Render()";

    destRect.x = pos.x;
    destRect.y = pos.y;
    destRect.w = W;
    destRect.h = H;

    SDL_RenderCopy(ren, TM.Texture, NULL, &destRect);  //srcRect = NULL will be rendering the whole texture of the whole car
}


#endif /* Car_h */