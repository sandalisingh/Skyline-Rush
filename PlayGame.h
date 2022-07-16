#ifndef PlayGame_h
#define PlayGame_h

#include "EventHandler.h"
#include "MusicPlayer.h"
#include "CircularQueue_ArrayImplementation.h"

class PlayGame;

//------------------------------->>>>>>>>>>  P  L  A  Y    G  A  M  E  <<<<<<<<<<-------------------------------------

class PlayGame {
    CQ IC_CQ;

    bool collision;

    bool quit;

    int speed;  //speed of the road //3

    int NoOfPoliceCar;  //
    
    int CurrentScore;  //acc to the game clock
    int CurrentLevel;  //acc to score  //total 4

    int startTime;  //starting time of the computor clock when a frame starts

    enum Level{
        NoZero,
        level1,
        level2,
        level3,
        level4,
        TotalLevels
    };


    private:
        SDL_Renderer *renderer;
        Road R;
        User_Car C;

        // MusicPlayer MP_Ignition;
        MusicPlayer MP_BackgroundRockMusic, MP_StartIgnition, MP_CarShortSounds;
        
        void Update();  //updates car road position 

        void Update_Score();
        void Update_Level();    //updates the level of the game
        void Update_IncomingCarPosition();
        void Update_UserCarPosition();  //keeps the user car on road

        void Render();  //renders the game screen

        bool Print_ScoreAndLevel();//displays the level and score

    public:

        PlayGame(SDL_Renderer *renderer);
        ~PlayGame();

        int targetScore[5] = { -1, 20, 40, 70, 100};   //score to move to next level   //20 40 70 700
        int Playing_CarGame(int &GameScore, int &GameLevel);  //returns the score of the game after collision else returns -1

        friend class Road;
    
};

PlayGame :: PlayGame(SDL_Renderer *ren) : renderer(ren) ,R(ren), C(ren) {


    MP_BackgroundRockMusic.Load_Sound(MusicPlayer :: Background_ROCK);

    // cout<<"\nPlayGame()  ---------CONSTRUCTOR------- beg";
    collision = false;

    NoOfPoliceCar = 4;
    
    IC_CQ.Enqueue(new Incoming_Car(renderer, TextureManager::CAR_0));
    IC_CQ.Enqueue(new Incoming_Car(renderer, TextureManager::CAR_1));
    IC_CQ.Enqueue(new Incoming_Car(renderer, TextureManager::CAR_2));
    IC_CQ.Enqueue(new Incoming_Car(renderer, TextureManager::CAR_3));
    IC_CQ.Enqueue(new Incoming_Car(renderer, TextureManager::CAR_4));

    
    speed = 3;
    
    //initialising score and level of game to 0
    CurrentScore = 0;
    CurrentLevel = level1;

    quit = false;

    //recording the time at which game begins
    startTime = clock();    //returns the approx processor time that is consumed by the program
    

    // cout<<"\nPlayGame() ---------CONSTRUCTOR------- ends";   
}

PlayGame :: ~PlayGame(){
}

int PlayGame :: Playing_CarGame(int &GameScore, int &GameLevel){
    MP_StartIgnition.Load_Sound(MusicPlayer :: Ignition);
    MP_StartIgnition.Play_ShortSound();

    // cout<<"\n\t\tPlaying_CarGame() begs";

    EventHandler EH;
    const int FPS = 60; //60 frames per second

    //frameDelay is the time spend per frame in miliseconds
    const int frameDelay = 1000/FPS;    //spend 16 and 2/3rd milliseconds per frame ( 1000ms / 60 frames )

    Uint32 frameStart;
    int frameTime; 

    
    // MP_BackgroundMusic.Bkgrd_Drumbeats();
    MP_BackgroundRockMusic.Play_Bkgrd_Drumbeats();

    //while( running() && !endGame && !quit) {
    while(!quit && GameWindow::running()) {
    // while(!quit && running()) {
        // cout<<"\n\n\n\n<< QUIT = "<<quit<<" RUNNING = "<<GameWindow::running()<<"\n\n\n\n";

        frameStart = SDL_GetTicks();

        int option = EH.handleEvents_PlayGame(&C, MP_CarShortSounds, MP_BackgroundRockMusic);
        if( option == Quit_Pressed_State){
            quit = true;
            return Quit_Pressed_State;
        }else if(option == GoToMainMenu_Pressed_State){
            return GoToMainMenu_Pressed_State;
        }

        // Update();
        // Render();

        if(CurrentScore == targetScore[level4]){
            // cout<<"\n<< Last Level Ended !";
            GameLevel = CurrentLevel;
            GameScore = CurrentScore;

            return GameOver_State;
        }
    
        if(IC_CQ.CheckCollision(C) == true){
            GameLevel = CurrentLevel;
            GameScore = CurrentScore;

            collision = true;

            MP_BackgroundRockMusic.STOP_Bkgrd_Drumbeats();
            // MP_CarShortSounds.Load_Sound(MusicPlayer :: Boom);
            // MP_CarShortSounds.Play_ShortSound();

            cout<<"\n\n------------>>>>>>>>C O L L I S I O N<<<<<<---------\n\n";
            collision = true;

            return GameOver_State;
        }

        Update();
        Render();
        
        

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }

        // cout<<"\n\n\n\n<< ~ QUIT = "<<quit<<" RUNNING = "<<GameWindow::running()<<"\n\n\n\n";
    }

    // cout<<"\n\t\tPlaying_CarGame() ends";
    return None_State;
}

//D I S P L A Y S   S C O R E   &   L E V E L----------------------------

bool PlayGame :: Print_ScoreAndLevel(){
    // cout<<"\n\t\tPrint Score & level() begs";

    TextureManager T_Score, T_ScoreNo, T_Level, T_LevelNo;
    string text;
    SDL_Color Color = {255,255,255,255};        //white 
    //char buffer[100];
   
    text = "SCORE  ";
    if(!T_Score.printText(text, 610, 20, renderer, Color, true)){
        return false;
    }    
    
    
    //SDL_itoa(score, buffer, 10);     //converts the integer(score) acc to base10 to string(buffer)
    text = to_string(CurrentScore);  
    //text = string(buffer);
    if(!T_ScoreNo.printText(text, 750, 20, renderer, Color, true)){
        return false;
    }     
   

    text = "LEVEL  ";
    if(!T_Level.printText(text, 610, 40, renderer, Color, true)){
        return false;
    }      
    

    //SDL_itoa(level+1,buffer,10);    //converts the integer(level+1) acc to base10 to string(buffer)
    //text = string(buffer);
    text = to_string(CurrentLevel); 
    if(!T_LevelNo.printText(text, 750, 40, renderer, Color, true)){
        return false;
    }        
    return true;
}

//U P D A T I O N---------------------------------

void PlayGame :: Update_Level(){
    // cout<<"\n\t\tUpdate LEVEL() begs";

   if(CurrentLevel != level4){  //it is not the last level
        if(CurrentScore == targetScore[CurrentLevel]){
            CurrentLevel++;
            //cout<<"\n\tLevel increased";

            speed += 1;
            C.moveStep += 10;
        }
   }else{
       cout<<"\nLevels Completed !!";
   }
//    cout<<"\n\t\tUpdate LEVEL() ends";
}

inline void PlayGame :: Update_Score(){
    //cout<<"\n\tUpdates score";
    CurrentScore = ((clock() - startTime) / (double) CLOCKS_PER_SEC);  //yields the number of seconds 
    
}

void PlayGame :: Update_IncomingCarPosition(){   
    if(IC_CQ.Peek()->pos.y >= R.Bottom_Y){
        IC_CQ.Peek()->pos.x = R.Leftmost_X + ( rand() % (R.Rightmost_X - R.Leftmost_X - IC_CQ.Peek()->W) );
        IC_CQ.Peek()->pos.y = (-IC_CQ.Peek()->H);
    }

    if(IC_CQ.Peek()->pos.y == IC_CQ.Peek()->H){
        IC_CQ.TraverseToNext();
    }

    IC_CQ.Increement_Y();
}

void PlayGame :: Update_UserCarPosition(){
    // cout<<"\n\t\tUpdate CAR POS begs";

    //if lestmost edge of car is less than the leftmost edge of road
    C.pos.x = ( max( C.pos.x , R.Leftmost_X ) );

    //if bottom of car is less than bottom most edge of the road
    C.pos.y = ( min( C.pos.y, R.Bottom_Y - C.H ) );

    //if rightmost edge of car is greater than the rightmost edge of road
    C.pos.x = ( min( C.pos.x  , R.Rightmost_X - C.W) );

    //if top of car is greater than top edge of road
    C.pos.y = ( max( C.pos.y , R.Top_Y ) );

    // for(int i = 0; i < NoOfPoliceCar; i++){
    //     if(C.pos.y + C.H)
    // }
    // cout<<"\n\t\tUpdate CAR POS ends";
}

void PlayGame :: Update(){
    // cout<<"\n\tUpdate() beg";
    Update_Score();
    Update_Level();

    for(int i = 0; i < NoOfPoliceCar; i++){    //numcar=5
        Update_IncomingCarPosition();
    }

    R.Update(speed);

    // if(IC_CQ.CheckCollision(C)){
    //     MP_BackgroundRockMusic.STOP_Bkgrd_Drumbeats();
    //     MP_CarShortSounds.Load_Sound(MusicPlayer :: Boom);
    //     MP_CarShortSounds.Play_ShortSound();

    //     cout<<"\n\n------------>>>>>>>>C O L L I S I O N<<<<<<---------\n\n";
    //     collision = true;
    //     return;
    // }
    
    Update_UserCarPosition();
    
    if(IC_CQ.KeepDistance(C) == true){
        MP_CarShortSounds.Load_Sound(MusicPlayer :: Screech);
        MP_CarShortSounds.Play_ShortSound();
    }

    // cout<<"\n\tUpdate() ends";
    
}

//R E N D E R-------------------------------

void PlayGame :: Render(){
    // cout<<"\n\tRender() beg";
    SDL_RenderClear(renderer);
    
    R.Render(renderer);    //-----------road
    C.Render(renderer);    //-----------usercar
    
    // Coord p0;
    
    // for(int i = 0; i < NoOfPoliceCar; i++){    //numCar = 5
    //     if(
    //         P[i]->pos.y + C.H >= R.Top_Y 
    //         && P[i]->pos.y <= R.Bottom_Y 
    //     ){
    //         P[i]->Render(renderer);
    //     }
    // }
    IC_CQ.Render(renderer);
    
    Print_ScoreAndLevel();  //-------level & score
    
    SDL_RenderPresent(renderer);

    // cout<<"\n\tRender() ends";
}

#endif /* PlayGame_h */