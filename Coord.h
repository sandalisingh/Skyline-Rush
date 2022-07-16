#ifndef Coord_h
#define Coord_h

#include <iostream>
using namespace std;

int min(int x, int y);  //returns the minimum value among the 2 passed arguments
int max(int x, int y);  //returns the maximum value among the 2 passed arguments

//C L A S S E S--------------
class Coord;

enum state{
    None_State,             //nothing clicked no state nothing none
    
    Username_Input_State,         //username input box clicked
    Password_Input_State,         //password input box clicked
    
    SignIn_SignUp_Pressed_State,  //already have an account take the user to the sign in page, dont take the user to registeration page
    LetsGo_Pressed_State,         //lets go clicked on the registration page, takes the user to the main menu page
    
    PlayGame_Button_Pressed_State,      //play button clicked
    Rules_Button_Pressed_State,          //rules button clicked
    GoToMainMenu_Pressed_State,       //restart game clicked which takes the user to the main menu page
    Quit_Pressed_State,           // ( x ) or quit game pressed

    PlayingGame_State,            //user is playing the car game here
    GameOver_State,
   
    Error_State           
};

//------------------------------->>>>>>>>>>  C  O  O  R  D  <<<<<<<<<<-------------------------------------

class Coord{    
    public:  
        int x, y;  
        
        Coord();    
        Coord(int, int);

        void set(int, int);
};

Coord :: Coord(){
    this->x = 0;
    this->y = 0;
}

Coord :: Coord(int x, int y){
    this->x = x;
    this->y = y;
}

inline void Coord :: set(int x, int y){
    this->x = x;
    this->y = y;
}

inline int min(int x, int y){  //returns the minimum of the passed arguments
    return ( ( x > y ) ? y : x ) ;
}

inline int max(int x, int y){  //returns the maximum of the passed arguments
    return ( ( x > y ) ? x : y ) ;
}

   

#endif  /* Coord_h */