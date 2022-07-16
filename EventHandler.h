#ifndef EventHandler_h
#define EventHandler_h

#include "GameWindow.h"
#include "Car.h"
#include "Road.h"
#include "MusicPlayer.h"
#include"ResponsiveBox.h"

class EventHandler;

//------------------------------->>>>>>>>>>  E  V E  E  N  T     H  A  N  D  L  E  R <<<<<<<<<<-------------------------------------

class EventHandler {
    protected :
        bool QUIT;
        
        int handleEvents_MainMenuScreen(Button &PlayGame_Button, Button &Rules_Button, Button &Quit_Button);   //1-start 2-rules 3-quit      
        int handleEvents_RulesScreen(Button &GoToMainMenu_Button_InRulesScreen);
        int handleEvents_GameOverScreen(Button &GoToMainMenu_Button_InGameOverScreen);
        
    public:
        EventHandler();

        int handleEvents_PlayGame(User_Car *C, MusicPlayer &MP, MusicPlayer &MP_BackgroundMusic);
};

EventHandler :: EventHandler(){
    cout<<"\nEH()";
    QUIT = false;
}

int EventHandler :: handleEvents_MainMenuScreen(Button &PlayGame_Button, Button &Rules_Button, Button &Quit_Button){
    cout<<"\n\tEH :: MainMenu()";

    SDL_Event event;    
    SDL_WaitEvent(&event);

    switch(event.type){
        case SDL_QUIT:{
            cout<<"\n> EH > MainMenu() : Quit CLICKED !";

            QUIT = true;
            return Quit_Pressed_State;
        }break;
        
        case SDL_MOUSEBUTTONDOWN:{
            if( PlayGame_Button.check_Button_is_Clicked( event ) == true ){
                cout<<"\n> EH > MainMenu() : PlayGame CLICKED !";

                return PlayGame_Button_Pressed_State;
            }else if( Rules_Button.check_Button_is_Clicked( event ) == true ){
                cout<<"\n> EH > MainMenu() : Rules CLICKED !";

                return Rules_Button_Pressed_State;
            }else if( Quit_Button.check_Button_is_Clicked( event ) == true ){
                cout<<"\n> EH > MainMenu() : Quit CLICKED !";

                QUIT = true;
                return Quit_Pressed_State;
            }
        }break;
    } 
    return  None_State;
}

int EventHandler :: handleEvents_PlayGame(User_Car *C, MusicPlayer &MP, MusicPlayer &MP_BackgroundMusic){
    cout<<"\n\tEH :: playGame()";
    
    // MusicPlayer MP;
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT:{
            cout<<"\n> EH > PlayGame() : Quit CLICKED !";

            QUIT = true;
            return Quit_Pressed_State;
        }break;

        case SDL_KEYDOWN:{
            //Select surfaces based on key press
            switch( event.key.keysym.sym ){	//SDL Keysym which contains the information about the key that was pressed. That Keysym contains the SDL Keycode which identifies the key that was pressed.
            
                case SDLK_UP:{
                    C->pos.y = C->pos.y - C->moveStep;
                    MP.Load_Sound(MusicPlayer :: BroomBroom);
                    MP.Play_ShortSound();
                }break;

                case SDLK_DOWN:{
                    C->pos.y = C->pos.y + C->moveStep;
                    MP.Load_Sound(MusicPlayer :: Reverse);
                    MP.Play_ShortSound();
                }break;

                case SDLK_LEFT:{
                    C->pos.x = C->pos.x - C->moveStep;
                    MP.Load_Sound(MusicPlayer :: Screech);
                    MP.Play_ShortSound();
                }break;

                case SDLK_RIGHT:{
                    C->pos.x = C->pos.x + C->moveStep;
                    MP.Load_Sound(MusicPlayer :: Screech);
                    MP.Play_ShortSound();
                }break;

                default: break;
            }

            if(event.key.keysym.sym == SDLK_m){
                MP_BackgroundMusic.Play_Pause_Background_Music();
            }else if(event.key.keysym.sym == SDLK_q){
                return GoToMainMenu_Pressed_State;
            }

        }break;

        default: break;
    }
    return None_State;
}

int EventHandler :: handleEvents_GameOverScreen(Button &GoToMainMenu_Button_InGameOverScreen){
    cout<<"\n\tEH :: GameOver()";
    
    SDL_Event event;
    //SDL_PollEvent(&event);

    SDL_WaitEvent(&event);

    switch(event.type){
        case SDL_QUIT : {
            cout<<"\n> EH > GameOver() : Quit CLICKED !";

            QUIT = true;
            return Quit_Pressed_State;
        }break;

        case SDL_MOUSEBUTTONDOWN:{
            if( GoToMainMenu_Button_InGameOverScreen.check_Button_is_Clicked( event ) == true ){
                cout<<"\n> EH > GameOver() : GoTo MainMenu CLICKED !";

                return GoToMainMenu_Pressed_State;
            }
        }break;

        default: break;
    }
    return None_State;
}

int EventHandler :: handleEvents_RulesScreen(Button &GoToMainMenu_Button_InRulesScreen){
    cout<<"\n\tEH :: Rules()";
    
    SDL_Event event;
    //SDL_PollEvent(&event);

    SDL_WaitEvent(&event);

    switch(event.type){
        case SDL_QUIT : {
            cout<<"\n> EH > Rules() : Quit CLICKED !";

            QUIT = true;
            return Quit_Pressed_State;
        }break;

        case SDL_MOUSEBUTTONDOWN : {
            if( GoToMainMenu_Button_InRulesScreen.check_Button_is_Clicked( event ) == true ){
                cout<<"\n> EH > Rules() : GoTo MainMenu CLICKED !";

                return GoToMainMenu_Pressed_State;
            }
        }break;

        default: break;
    }
    return None_State;
}



#endif /* EventHandler */