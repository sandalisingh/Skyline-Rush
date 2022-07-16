#ifndef Game_h
#define Game_h

#include "EventHandler.h"
#include "PlayGame.h"
#include "Register.h"
#include "ResponsiveBox.h"
#include "LeaderBoard.h"

class Game;

//------------------------------->>>>>>>>>>  G  A  M  E <<<<<<<<<<-------------------------------------

class Game : public EventHandler, public GameWindow{

    private:
        bool ERROR;
        int FinalScore, FinalLevel;

        Button 
                PlayGame_Button, 
                Rules_Button, 
                Quit_Button, 
                GoToMainMenu_Button_InRulesScreen,
                GoToMainMenu_Button_InGameOverScreen
                ;

        LeaderBoard LB;
        
        int MainMenu_Screen();    //displays the start screen
        int GameOver_Screen(int);  //displays the gameover screen
        int Rules_Screen();
        bool Print_ScoreAndLevel_OnGameOverScreen();


    public:
        
        Game(); //CONSTRUCTOR
        void Run(); //runs the whole game(start, play, gameover)
      
};

//GAME CLASS CONSTRUCTOR
Game :: Game() : 
    PlayGame_Button( 190, 600, 252, 334 ), 
    Rules_Button( 190, 600, 356, 436 ), 
    Quit_Button( 190, 600, 458, 538 ), 
    GoToMainMenu_Button_InRulesScreen( 600, 765, 10, 50 ),
    GoToMainMenu_Button_InGameOverScreen( 600, 765, 10, 50 )
{
    cout<<"\nG()";

    ERROR = false;
    FinalLevel = 0;
    FinalScore = 0;
}

//S T A R T    S C R E E N------------------------------------------------

int Game :: MainMenu_Screen(){
    cout<<"\n\tG :: MainMenu()";

    TextureManager T;

    //Load media
    if( !T.Load_Image_Texture(T.MENU_PAGE_, renderer) ){
        cout<<"\n> Failed to load media!\n";
        ERROR = true;
        return Error_State;
    }else{	
        //While application is running

        //Event handler
        SDL_Event e;
        while( !QUIT && !ERROR && running()){
            
            //Main loop flag
            int option = handleEvents_MainMenuScreen(PlayGame_Button, Rules_Button, Quit_Button);
            if(option == Quit_Pressed_State){
                // cout<<"\n> Game > MainMenu_Screen() : Quit CLICKED !";

                QUIT = true;
                return option;
            }else if( option != None_State){
                // cout<<"\n> Game > MainMenu_Screen() : Not None!";

                return option;
            }
        
            SDL_RenderClear( renderer );
            SDL_RenderCopy( renderer, T.Texture, NULL, NULL);	
            SDL_RenderPresent( renderer );
        }
    }

    return None_State;
}

//E N D    S C R E E N----------------------------------------------

int Game :: GameOver_Screen(int score){
    cout<<"\n\tG :: GameOver()";
    
    LB.CollectData();
    
    TextureManager T;
    //Load media
    if( !T.Load_Image_Texture(T.GAMEOVER_PAGE_, renderer) ){
        cout<<"\n> Failed to load media!\n";
        ERROR = true;
        return Error_State;
    }else{

        //While application is running
        SDL_UpdateWindowSurface(window);

        //Event handler
        SDL_Event e;
        
        while( !QUIT && !ERROR && running() ){
            
            //Main loop flag
            int option = handleEvents_GameOverScreen( GoToMainMenu_Button_InGameOverScreen );
            if(option == Quit_Pressed_State){
                // cout<<"\n> Game > GameOver_Screen() : Quit CLICKED !";
                QUIT = true;
                return option;
            }
            if(option != None_State){
                // cout<<"\n> Game > GameOver_Screen() : Not None !";
                return option;
            }
        
            SDL_RenderClear( renderer );
            SDL_RenderCopy( renderer, T.Texture, NULL, NULL);
            Print_ScoreAndLevel_OnGameOverScreen();	
            SDL_RenderPresent( renderer );
        }
    }
    return None_State;
}


bool Game :: Print_ScoreAndLevel_OnGameOverScreen(){
    cout<<"\n\tG :: Print Score & Level on GameOver()";
    
    // LeaderBoard LB;
    TextureManager T_Score, T_ScoreNo, T_Level, T_LevelNo;
    string text;
    SDL_Color Color = {255,255,255,255};        //white 
   
    text = to_string(FinalScore);  
    //text = string(buffer);
    if(!T_ScoreNo.printText(text, 710, 350, renderer, Color, true)){
        return false;
    }     
   
    text = to_string(FinalLevel); 
    if(!T_LevelNo.printText(text, 710, 390, renderer, Color, true)){
        return false;
    } 

    LB.DisplayData(renderer);

    return true;
}

//R U L E S    S C R E E N----------------------------------------------

int Game :: Rules_Screen(){
    cout<<"\n\tG :: Rules()";
    
    TextureManager T;
    
    if( !T.Load_Image_Texture(T.RULES_PAGE_, renderer) ){
        cout<<"\n> Failed to load media!\n";
        ERROR = true;
        return ERROR;
    }else{	
        //While application is running

        //Event handler
        SDL_Event e;
        
        while( !QUIT && !ERROR && running()){
            
            //Main loop flag
            int option = handleEvents_RulesScreen( GoToMainMenu_Button_InRulesScreen );
            if(option == Quit_Pressed_State){
                // cout<<"\n> Game > Rules_Screen() : Quit CLICKED !";

                QUIT = true;
                return option;
            }else if(option != None_State){
                // cout<<"\n> Game > Rules_Screen() : Not None !";
                return option;
            }
        
            SDL_RenderClear( renderer );
            SDL_RenderCopy( renderer, T.Texture, NULL, NULL);	
            SDL_RenderPresent( renderer );
        }
    }
    return None_State;
}

//R U N    G A M E-----------------------------

void Game :: Run(){   
    MusicPlayer MP_Crash;

    cout<<"\n\tG :: Run()";

    RegistrationPage RP(renderer);
    int option = RP.SignUp_OR_SignIn();
    if( option == Quit_Pressed_State || option == Error_State){
        cout<<"\n> Game > Run() : Quit CLICKED !";
        QUIT = true;
        return;
    }
    
    // cout<<"\n\n------------GAME RUN-------------\n\n";

    //cout<<"\n\n-----------------------R U N N I N G-------------------------\n\n";
    srand(time(NULL));

    while( !QUIT && !ERROR && running()){    //if restart is false dont run again
        int option = MainMenu_Screen();
        switch(option){
            case PlayGame_Button_Pressed_State:{    //---------------------PLAYING CAR GAME
                // cout<<"\n> Game > Run() : PlayGame CLICKED !";

                PlayGame PG(renderer);
                int score, level;
                int option = PG.Playing_CarGame(FinalScore, FinalLevel);
                if(option == Quit_Pressed_State){
                    // cout<<"\n> Game > Run() : Quit CLICKED !";

                    QUIT = true;
                    return;
                }else if(option == GameOver_State){

                    // MP_BackgroundRockMusic.STOP_Bkgrd_Drumbeats();
                    MP_Crash.Load_Sound(MusicPlayer :: Boom);
                    MP_Crash.Play_ShortSound();

                    //FinalScore = option;
                    RP.GetStatus(FinalScore, FinalLevel);
                }else if( option == GoToMainMenu_Pressed_State ){
                    break;
                }
                GameOver_Screen(FinalScore);
            }break;

            case Rules_Button_Pressed_State:{    //--------------------------RULES
                // cout<<"\n> Game > Run() : Rules_Button CLICKED !";

                Rules_Screen();
            }break;

            case Quit_Pressed_State :{     //--------------------------QUIT
                // cout<<"\n> Game > Run() : Quit CLICKED !";
                QUIT = true;
                return;
            }

            case Error_State : {
                cout<<"\n\n-- E R R O R ! --\n\n";
                return;
            }
        }
    }

   
}


#endif /* Game_h */
