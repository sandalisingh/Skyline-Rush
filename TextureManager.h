#ifndef TextureManager_h
#define TextureManager_h


#include </opt/homebrew/include/SDL2/SDL.h>
#include </opt/homebrew/include/SDL2/SDL_ttf.h>
#include </opt/homebrew/include/SDL2/SDL_image.h>

#include "Coord.h"

class TextureManager;

//------------------------------->>>>>>>>>>  T  E  X  T  U  R  E      M  A  N  A  G  E  R  <<<<<<<<<<-------------------------------------

class TextureManager{
    private:
        int w, h;

    public:
        enum PicName{
            NONE,
            CAR_0,
            CAR_1,
            CAR_2,
            CAR_3,
            CAR_4,
            ROAD_,
            REGISTRATION_PAGE_,
            LOGIN_PAGE_,
            MENU_PAGE_,
            RULES_PAGE_,
            GAMEOVER_PAGE_,
            TOTAL
        };

        int getWidth();
        int getHeight();

        SDL_Texture* Texture;

        bool Load_Image_Texture(int Which_Image, SDL_Renderer *ren);

        bool Load_Text_Texture(const char *text, SDL_Renderer *ren, SDL_Color);

        bool printText(string text, int x, int y, SDL_Renderer *ren, SDL_Color, bool ReloadTexture);

        bool loadMedia(SDL_Renderer *ren);

        //Renders texture at given point
		// void render( int x, int y , SDL_Renderer *renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void free();

        TextureManager();   //initialises TTF and IMG
        ~TextureManager();  //destroys texture, quits img and ttf
};

TextureManager :: TextureManager(){
    //success = true;

    //----------------------------------Initialize the TTF engine--------------------------------------
    if( TTF_Init() < 0){    //returns -1 on error
        cout<<"\n> TTF! SDL_Error: "<<SDL_GetError();
        //success = false;
    }

    //----------------------------------Initialize PNG loading--------------------------------------
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
        cout<<"\n> SDL_image could not initialize! Error: "<<IMG_GetError();
        //success = false;
    }

    Texture = NULL;

}

bool TextureManager :: Load_Image_Texture(int Which_Image, SDL_Renderer *ren){
    free();

    string Pic;

    switch(Which_Image){
        case CAR_0 :{
            Pic = "Pictures/car.png";
        }break;

        case CAR_1 :{
            Pic = "Pictures/car1.png";
        }break;

        case CAR_2 :{
            Pic = "Pictures/car2.png";
        }break;

        case CAR_3 :{
            Pic = "Pictures/car3.png";
        }break; 

        case CAR_4 :{
            Pic = "Pictures/car4.png";
        }break;

        case ROAD_ :{
            Pic = "Pictures/road.png";
        }break;

        case REGISTRATION_PAGE_ :{
            Pic = "Pictures/Register.png";
        }break;

        case LOGIN_PAGE_ :{
            Pic = "Pictures/Login.png";
        }break;

        case MENU_PAGE_ :{
            Pic = "Pictures/start.png";
        }break;

        case RULES_PAGE_ :{
            Pic = "Pictures/Rules.png";
        }break;

        case GAMEOVER_PAGE_ :{
            Pic = "Pictures/end.png";
        }break;
    }

    SDL_Surface *tempSurface = IMG_Load(Pic.c_str());
    
    if(tempSurface == NULL){
        cout<<"\n\n> Img failed to load to surface SDL_Error: "<<SDL_GetError()<<"\n\n";
        return false;

    }else{
        Texture = SDL_CreateTextureFromSurface(ren, tempSurface);

        if(Texture == NULL){     //returns null on failure
            cout<<"\n\n> CreateTextureFromSurface texture SDL_Error: "<<SDL_GetError()<<"\n\n";
            //return false;

        }else{
            //Get image dimensions
			w = tempSurface->w;
			h = tempSurface->h;
        }
    }
    
    SDL_FreeSurface(tempSurface);
    tempSurface = NULL;
 
    return (Texture != NULL);
}

bool TextureManager :: Load_Text_Texture(const char *text, SDL_Renderer *ren, SDL_Color Color){
    TTF_Font *font = TTF_OpenFont("Font.ttf",1000);
    // SDL_Color textColor = {255,255,255,255};        //white 
    
    
    SDL_Surface *tempSurface = TTF_RenderText_Solid(font, text, Color);
    
    if(tempSurface == NULL){
        // cout<<"\n\n> Text couldnt be rendered on the surface! SDL_Error: "<<SDL_GetError()<<"\n\n"; 
        return false; 
    }else{
        //cout<<"\n\tText rendered on the surface";

        Texture = SDL_CreateTextureFromSurface(ren, tempSurface);

        if(Texture == NULL){     //returns null on failure
            // cout<<"\n\n> Text Texture couldnt be created! SDL_Error: "<<SDL_GetError()<<"\n\n";  
            //return false;
        }else{
            //Get image dimensions
			w = tempSurface->w;
			h = tempSurface->h;
        }
    }
    
    SDL_FreeSurface(tempSurface);
    tempSurface = NULL;

    return (Texture != NULL);
}

bool TextureManager :: printText(string text, int x, int y, SDL_Renderer *renderer, SDL_Color Color, bool ReloadTexture){
    const char *Txt = text.c_str();

    if( ReloadTexture == true || Texture == NULL){  //if i ask to load the texture or the there is no texture to begin with
        int success = Load_Text_Texture(Txt, renderer, Color);
        if( success == false){
            return false;
        }
    }
    
    int Txt_lt = text.size();

    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w =   16*Txt_lt;
    dest.h =   28;     //25;

    if(SDL_RenderCopy(renderer, Texture, NULL, &dest) < 0){
        cout<<"\n\n> Load Text Texture : Render Copy! SDL_Error: "<<SDL_GetError()<<"\n\n";  
        return false;
    }
    return true;
}

bool TextureManager :: loadMedia(SDL_Renderer *renderer){
    //Copy a portion of the texture to the current rendering target
    if( SDL_RenderCopy( renderer, Texture, NULL, NULL) < 0){
        cout<<"\n\n> Render Copy! SDL_Error: "<<SDL_GetError()<<"\n\n";  
        return false;
    }
    return true;
}

int TextureManager :: getWidth(){
    return w;
}

int TextureManager :: getHeight(){
    return h;
}

TextureManager :: ~TextureManager(){
    //cout<<"\n~ Texture Manager";  //called a lot      //-----------LOOK INTO IT

    //Free loaded image
	free();

    //Quit SDL subsystems
	IMG_Quit();
    TTF_Quit();
}

void TextureManager :: free(){
    //Free texture if it exists
	if( Texture != NULL )
	{
		SDL_DestroyTexture( Texture );
		Texture = NULL;
	}
}




#endif  /* TextureManager_h */