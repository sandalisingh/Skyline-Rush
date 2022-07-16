#ifndef GameWindow_h
#define GameWindow_h

#include "TextureManager.h"
#include </opt/homebrew/include/SDL2/SDL_mixer.h>

class GameWindow;
//------------------------------->>>>>>>>>>  G  A  M  E     W  I  N  D  O  W  <<<<<<<<<<-------------------------------------

class GameWindow{
    private:
        static bool isRunning;
        // bool isRunning;

    public:
        GameWindow();
        ~GameWindow();
    
        //SCREEN DIMENSIONS
        const static int SCREEN_WIDTH;  //800
        const static int SCREEN_HEIGHT;     //640

        SDL_Window *window;
        SDL_Renderer *renderer;

        static bool running();
        // bool running();

        // friend class PlayGame;
};

bool GameWindow :: isRunning = true;

const int GameWindow :: SCREEN_WIDTH = 800;  
const int GameWindow :: SCREEN_HEIGHT = 640; 

GameWindow :: GameWindow() {
    isRunning = true;

    //----------------------------------INITIALISING SDL---------------------------------------

    if(SDL_Init(SDL_INIT_EVERYTHING  | SDL_INIT_AUDIO) == 0){ //successfully initialised SDL
        //Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
			cout<<"> Warning: Linear texture filtering not enabled!";
		}

        //----------------------------------creating sdl window---------------------------------------
        window = SDL_CreateWindow("Car Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if(window){
            //----------------------------------creating sdl renderer---------------------------------------
            renderer = SDL_CreateRenderer(window, -1, 0);
            if(renderer){
                //----------------------------------coloring renderer black---------------------------------------
                if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) < 0){     //black bkgrd
                    cout<<"\n> Renderer color unable to set black";
                }  

            }else{
                cout<<"\n> Renderer NOT created";
                isRunning = false;
            }
        }else{
            cout<<"\n> Window NOT created";
            isRunning = false;
        }
    }else{
        cout<<"\n> SDL NOT initialised";
        isRunning = false;
    }

}

inline bool GameWindow :: running(){
    return isRunning;
}

GameWindow :: ~GameWindow(){
    // cout<<"\n~ Game Window";

    //Destroy renderer	
	SDL_DestroyRenderer( renderer );
    renderer = NULL;

    //Destroy window	
	SDL_DestroyWindow( window );
	window = NULL;
	
	//Quit SDL subsystems
	SDL_Quit();
}


#endif  /* GameWindow.h */