#ifndef MusicPlayer_h
#define MusicPlayer_h

#include "GameWindow.h"

class MusicPlayer;

class MusicPlayer{
    // protected:
    private:

        bool running;

        //The music that will be played
        Mix_Music *Background_Music;

        //The sound effects that will be used
        // Mix_Chunk *CarSound[Total];
        Mix_Chunk *ShortSound;

    public:

        enum SoundEffects{
            Ignition,
            Boom,
            Screech,
            BroomBroom,
            Reverse,
            Nope,
            Background_ROCK,
            Total
        };

        MusicPlayer();
        ~MusicPlayer();

        void Play_ShortSound();
        void STOP_ShortSound();
        void Play_Pause_Background_Music();

        void Play_Bkgrd_Drumbeats();
        void STOP_Bkgrd_Drumbeats();

        bool Load_Sound(int Which_ShortSound);
};

MusicPlayer :: MusicPlayer(){
    running = true;

    //----------------------------------Initialize SDL_mixer----------------------------------
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        //Last argument : minimize lag when playing sounds
        cout<<"\n> SDL_mixer could not initialize! SDL_mixer Error: "<<Mix_GetError();
        running = false;
    }

    Background_Music = NULL;
    ShortSound = NULL;

    // LoadShortSound(Which_ShortSound);
}

bool MusicPlayer :: Load_Sound(int Which_ShortSound){

    switch(Which_ShortSound){
        case Ignition :{
            ShortSound = Mix_LoadWAV( "Music/Ignition.wav" );
        }break;

        case Boom :{
            ShortSound = Mix_LoadWAV( "Music/Boom.wav" );
        }break;

        case Screech :{
            ShortSound = Mix_LoadWAV( "Music/Screech2.wav" );
        }break;

        case BroomBroom :{
            ShortSound = Mix_LoadWAV( "Music/BroomBroom.wav" );
        }break;

        case Reverse :{
            ShortSound = Mix_LoadWAV( "Music/CarReverse.wav" );
        }break;

        case Nope :{
            ShortSound = Mix_LoadWAV( "Music/Nope.wav" );
        }break;

        case Background_ROCK :{
            Background_Music = Mix_LoadMUS( "Music/BackToBasics.wav" );
        }break;
    }

    if( ShortSound == NULL ){
        cout<<"\nFailed to load BOOM sound effect! SDL_mixer Error: "<<Mix_GetError();
        running = false;
    }

    return running;
}

MusicPlayer :: ~MusicPlayer(){
    // //Free the sound effects
    // Mix_FreeChunk( CarSound[Ignition] );
    // CarSound[Ignition] = NULL;

    // Mix_FreeChunk( CarSound[Boom] );
    // CarSound[Boom] = NULL;
    
    // Mix_FreeChunk( CarSound[Screech] );
    // CarSound[Screech] = NULL;
    
    // Mix_FreeChunk( CarSound[BroomBroom] );
    // CarSound[BroomBroom] = NULL;

    // Mix_FreeChunk( CarSound[Reverse] );
    // CarSound[Reverse] = NULL;

    // Mix_FreeChunk( CarSound[Nope] );
    // CarSound[Nope] = NULL;

    Mix_FreeChunk(ShortSound);
    ShortSound = NULL;
    
    //Free the music
    Mix_FreeMusic( Background_Music );
    Background_Music = NULL;

    Mix_Quit();
}

inline void MusicPlayer :: Play_ShortSound(){
    Mix_PlayChannel( -1, ShortSound, 0 );
}

inline void MusicPlayer :: STOP_ShortSound(){
    Mix_PauseMusic();
}

inline void MusicPlayer :: Play_Bkgrd_Drumbeats(){
    Mix_PlayMusic( Background_Music, -1 );
}

inline void MusicPlayer :: STOP_Bkgrd_Drumbeats(){
    //Stop the music
    Mix_HaltMusic();
}

void MusicPlayer :: Play_Pause_Background_Music(){
    if( Mix_PlayingMusic() == 0 ){  //If there is no music playing
        //Play the music
        Mix_PlayMusic( Background_Music, -1 );
    }else{   //If music is being played
        if( Mix_PausedMusic() == 1 ){   //If the music is paused
            Mix_ResumeMusic();  //Resume the music
        }else{   //If the music is playing
            Mix_PauseMusic();//Pause the music
        }
    }
}


#endif /* MusicPlayer */