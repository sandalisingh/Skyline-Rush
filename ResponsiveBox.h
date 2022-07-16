#ifndef ResponsiveBox_h
#define ResponsiveBox_h

#include "TextureManager.h"
#include "Coord.h"

//------------------------------>>>>>>>>>>>R E S P O N S I V E     B O X<<<<<<<<<<<------------------------------------

class Responsive_Box{
    protected:
        int w, h;
        int top_Y, bottom_Y;
        int left_X, right_X;

    public:
        Responsive_Box(int, int, int, int);

        int get_Right_X();
        int get_Left_X();

        int get_Top_Y();
        int get_Bottom_Y();
};

Responsive_Box :: Responsive_Box(int Left_X, int Right_X, int Top_Y, int Bottom_Y){
    top_Y = Top_Y;
    right_X = Right_X;
    bottom_Y = Bottom_Y;
    left_X = Left_X;

    w = right_X - left_X;
    h = bottom_Y - top_Y;
}

inline int Responsive_Box :: get_Left_X(){
    return left_X;
}

inline int Responsive_Box :: get_Right_X(){
    return right_X;
}

inline int Responsive_Box :: get_Top_Y(){
    return top_Y;
}

inline int Responsive_Box :: get_Bottom_Y(){
    return bottom_Y;
}

//------------------------------>>>>>>>>>>>B U T T O N<<<<<<<<<<<------------------------------------

class Button : public Responsive_Box{
    protected:

    public:
        Button(int,int,int,int);

        bool check_Button_is_Clicked(SDL_Event event);
        // void Clicked();
};

Button :: Button(int Left_X, int Right_X, int Top_Y, int Bottom_Y) : Responsive_Box(Left_X, Right_X, Top_Y, Bottom_Y) {
   
}

bool Button :: check_Button_is_Clicked(SDL_Event event){
    if(
        event.type == SDL_MOUSEBUTTONDOWN
        &&(
            event.motion.x >= left_X
            && event.motion.x <= right_X
            && event.motion.y >= top_Y
            && event.motion.y <= bottom_Y
        )
    ){
        cout<<"\nB > CLICKED !";
        return true;
    }
    return false;
}

//------------------------------>>>>>>>>>>>T E X T    I N P U T    B O X<<<<<<<<<<<------------------------------------

class Text_Input_Box : public Button{
    private:
        

    public:
        string TextInput;

        Text_Input_Box(string defaultText,int,int,int,int);

        // int Text_Length();

        bool clicked_Out_Of_The_Text_Box(SDL_Event event);

        // int HandleInput(char *CurrentPage, SDL_Renderer *renderer);

        string getInput();

        void Render(TextureManager &TM, SDL_Renderer *renderer);
};

bool Text_Input_Box :: clicked_Out_Of_The_Text_Box(SDL_Event event){
    if(
         event.type == SDL_MOUSEBUTTONDOWN
        && !(
            event.motion.x >= left_X
            && event.motion.x <= right_X
            && event.motion.y >= top_Y
            && event.motion.y <= bottom_Y
        )
    ){
        cout<<"\nText_Input_Box > CLICKED out of the box !";

        return true;
    }
    return false;
}

Text_Input_Box :: Text_Input_Box(string defaultText,int Left_X, int Right_X, int Top_Y, int Bottom_Y) : Button(Left_X, Right_X, Top_Y, Bottom_Y) {
    TextInput = defaultText;
}
 
string Text_Input_Box :: getInput(){
    return TextInput;
}

void Text_Input_Box :: Render(TextureManager &TM, SDL_Renderer *renderer){
    SDL_Rect destRect;

    destRect.w = 20 * TextInput.size();
    destRect.h = 0.75 * h;

    destRect.x = ( 800 - ( 20 * TextInput.size())) / 2 ;        //TM.getWidth()
    destRect.y = top_Y + 10;

	// //Render to screen
	// SDL_RenderCopyEx( renderer, Texture, NULL, &destRect, 0.0, NULL, SDL_FLIP_NONE );
    if(SDL_RenderCopy(renderer, TM.Texture, NULL, &destRect) < 0){
        cout<<"\n\n> Load Text Texture : Render Copy! SDL_Error: "<<SDL_GetError()<<"\n\n"; 
    }
}


#endif /* ResponsiveBox.h */