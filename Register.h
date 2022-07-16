#ifndef Register_h
#define Register_h

#include "EventHandler.h"
#include "TextureManager.h"
#include "ResponsiveBox.h"
#include "Account.h"


//------------------------------>>>>>>>>>>> R E G I S T R A T I O N      P A G E <<<<<<<<<<<------------------------------------

class RegistrationPage {
    private:

        Text_Input_Box Username_InputBox, Password_InputBox;
        Button SignIn_SignUp_Button, LetsGo_Button;

        SDL_Renderer *renderer;

        TextureManager TM_Username, TM_Password, TM_Background;

        //string inputText;
        bool Reload_Username_Texture, Reload_Password_Texture;
        bool Is_It_LoginPage; //false:Register true:Login
        Account A;
        
        int Page();   //User is already registered

        int handleEvents_Login();
        int HandleInput(Text_Input_Box &TIB, int InputWich);

        void Render();
        void RenderText();
        
              
    public:
        
        RegistrationPage(SDL_Renderer *ren);

        int SignUp_OR_SignIn();        
        void GetStatus(int, int); 
};

RegistrationPage :: RegistrationPage(SDL_Renderer *ren) 
    : renderer(ren), 
    Username_InputBox("", 206, 610, 356, 406 ), 
    Password_InputBox("", 206, 610, 456, 506 ),
    
    SignIn_SignUp_Button( 600, 765, 10, 50 ),
    
    LetsGo_Button( 530, 720, 540, 585 )
{
    Reload_Username_Texture = false;
    Reload_Password_Texture = false;

    Is_It_LoginPage = false;   //first page to open up is registration page

    //cout<<"\nRegistarationPage()";
}

void RegistrationPage :: GetStatus(int CurrentGameScore, int CurrentGameLevel){
    A.newHighScore(CurrentGameScore, CurrentGameLevel);
}

int RegistrationPage :: SignUp_OR_SignIn(){
    MusicPlayer MP;
    MP.Load_Sound(MusicPlayer :: Nope);

    int GoTo_MainMenu = false;

    for(int i = 0; ( i < 10 ) && ( GoTo_MainMenu != true ) && GameWindow::running() ; i++){   
        // cout<<"\n\n------------REGISTRATION PAGE-------------\n\n";

        int R_option = Page();
        switch ( R_option ){
            case Quit_Pressed_State : {
                // cout<<"\n> RP > SignUp_OR_SignIn() : Quit_Pressed !\n";
                return Quit_Pressed_State;
            }break;

            case SignIn_SignUp_Pressed_State : {
                // cout<<"\n> RP > SignUp_OR_SignIn() : SignIn_SignUp_Pressed !\n";
                Is_It_LoginPage = ( !Is_It_LoginPage );
            }break;

            case LetsGo_Pressed_State : {
                if(Is_It_LoginPage == true){
                    if(A.CheckLogin() == false){        //its login page so check whether the entered credentials match with the database
                        cout<<"\n> RP > SignUp_OR_SignIn() : Login Failed !\n";
                        MP.Play_ShortSound();
                        
                    }else{
                        cout<<"\n> RP > SignUp_OR_SignIn() : Login Sucessful !\n";
                        GoTo_MainMenu = true;

                        return LetsGo_Pressed_State;                                            //LOGIN SUCCESSFUL
                    }
                }else{
                    if(A.CreateAccount() == false){        //its registration page so check whether the entered username the primary key is unique and doesnt give an SDL not OK
                        cout<<"\n> RP > SignUp_OR_SignIn() : Registration Failed !\n";
                        MP.Play_ShortSound();
                        
                    }else{
                        cout<<"\n> RP > SignUp_OR_SignIn() : Registration Sucessful !\n";
                        GoTo_MainMenu = true;

                        return LetsGo_Pressed_State;                                            //LOGIN SUCCESSFUL
                    }
                }
            }break;
        }
    }
    return Error_State;
}

int RegistrationPage :: Page(){
    //cout<<"\n\tRegistarationPage :: Login()";
    A.clearCredentials();
    EventHandler EH;
    int CurrentPage;
    
    const int FPS = 60;
    const int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime; 

    if( Is_It_LoginPage == true){
        CurrentPage = TM_Background.LOGIN_PAGE_;
    }else{
        CurrentPage = TM_Background.REGISTRATION_PAGE_ ;
    }

    if( !TM_Background.Load_Image_Texture(CurrentPage, renderer) ){
        return Error_State;
    }
    
    while( GameWindow::running() ) {
        frameStart = SDL_GetTicks();

        int option = handleEvents_Login();
        // if( option == Username_Input_State ){
        //     cout<<"\n> RP > Page() : Username_Input_State !";
        //     A.Username = Username_InputBox.getInput();
        // }else if( option == Password_Input_State ){
        //     cout<<"\n> RP > Page() : Password_Input_State !";
        //     A.Password = Password_InputBox.getInput();
        // }else if( option != None_State ){
        if( (option != None_State)  &&  (option != Username_Input_State)  &&  (option != Password_Input_State) ){
            // cout<<"\n> RP > Page() : NOT NONE !";
            return option;
        }

        Render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
        // cout<<"\nUSERNAME = "<<A.Username;
        // cout<<"\nPASSWORD = "<<A.Password;
    }

    return LetsGo_Pressed_State;
}

int RegistrationPage :: handleEvents_Login(){
    //cout<<"\n\thandleEvents_Login()";
    SDL_Event event;
    SDL_WaitEvent(&event);    
    switch( event.type ) {
        //---------------------------------------------------------- ( X )    clicked
        case SDL_QUIT : {   //User requests quit
            // cout<<"\n> RP > handleEvents_Login() : Quit CLICKED !";
            return Quit_Pressed_State;
        }break;

        case SDL_MOUSEBUTTONDOWN : {
            //------------------------------------------- L O G I N  /  B A C K     clicked
            if( SignIn_SignUp_Button.check_Button_is_Clicked(event) == true ){
                // cout<<"\n> RP > handleEvents_Login() : ChangePage CLICKED !";
                return SignIn_SignUp_Pressed_State;
            }           
            //-------------------------------------------------- L E T S    G O     clicked           
            else if( LetsGo_Button.check_Button_is_Clicked(event) == true ){
                // cout<<"\n> RP > handleEvents_Login() : LetsGo CLICKED !";
                return LetsGo_Pressed_State;
            
            }//-------------------------------------------------- Username box clicked 
            else if( Username_InputBox.check_Button_is_Clicked(event) == true ){
                // cout<<"\n> RP > handleEvents_Login() : UsernameInputBOX CLICKED !";

                SDL_StartTextInput();
                HandleInput(Username_InputBox, Username_Input_State);
                A.Username = Username_InputBox.getInput();
                SDL_StopTextInput();

                return Username_Input_State;
            }
            //---------------------------------------------------- Password box clicked 
            else if( Password_InputBox.check_Button_is_Clicked(event) == true ){
                // cout<<"\n> RP > handleEvents_Login() : PasswordInputBOX CLICKED !";

                SDL_StartTextInput();
                HandleInput(Password_InputBox, Password_Input_State);
                A.Password = Password_InputBox.getInput();
                SDL_StopTextInput();

                return Password_Input_State;
            }
        }break;
    }

    // cout<<"\n> RP > handleEvents_Login() : None !";
    return None_State;
}

int RegistrationPage :: HandleInput(Text_Input_Box &TIB, int InputWhich){
    // cout<<"\nText_Input_Box :: HandleInput()";

    SDL_Event event;
    // if(check_Button_is_Clicked(event)){
    while(true){
        SDL_WaitEvent( &event );
            
        switch(event.type){
            //-----------------------------------------------------------Clicked outside the text input box
            case SDL_MOUSEBUTTONDOWN:{
                if( TIB.clicked_Out_Of_The_Text_Box( event ) ){
                    // cout<<"\n> RP > HandleInput() : CLICKED out of the text box----";
                    return None_State;
                }
            }
            //-----------------------------------------------------------( X )
            case SDL_QUIT : {
                // cout<<"\n> RP > HandleInput() : Quit CLICKED !";
                return Quit_Pressed_State;
            }break;
            //-----------------------------------------------------------Special key input
            case SDL_KEYDOWN : {
                //Handle backspace
                if( event.key.keysym.sym == SDLK_BACKSPACE && TIB.TextInput.size() > 0 ){
                    // cout<<"\n> RP > HandleInput() : Backspace CLICKED !";

                    //lop off character
                    TIB.TextInput.pop_back();
                    //Reload_InputText_Texture = true;
                }
                //Handle copy
                else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL ){
                    // cout<<"\n> RP > HandleInput() : Ctrl C CLICKED !";

                    SDL_SetClipboardText( TIB.TextInput.c_str() );
                }
                //Handle paste
                else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ){
                    // cout<<"\n> RP > HandleInput() : Ctrl V CLICKED !";

                    TIB.TextInput = SDL_GetClipboardText();
                    // Reload_InputText_Texture = true;
                }
            }break;
            //-----------------------------------------------------------Text input event
            case SDL_TEXTINPUT : {
                //Not copy or pasting
                if( 
                    !( 
                        SDL_GetModState() & KMOD_CTRL && 
                        ( 
                            event.text.text[ 0 ] == 'c' 
                            || event.text.text[ 0 ] == 'C' 
                            || event.text.text[ 0 ] == 'v' 
                            || event.text.text[ 0 ] == 'V' 
                        ) 
                    ) 
                ){
                    // cout<<"\n> RP > HandleInput() : Character input !";
                    //Append character
                    TIB.TextInput += event.text.text;
                    // Reload_InputText_Texture = true;
                    // cout<<"\n\t\tHandleInput() : Input   =   "<<TIB.TextInput;
                }
            }break;
            // default: cout<<"\nHandleInput() : Default!";
        }

        if(InputWhich == Username_Input_State){
            A.Username = TIB.TextInput;
        }else if(InputWhich == Password_Input_State){
            A.Password = TIB.TextInput;
        }

        Render();
    }
    // cout<<"\n> RP > HandleInput() : None !";

    return None_State;
}

void RegistrationPage :: RenderText(){
    // cout<<"\n\t\tRenderText()";
    SDL_Color Black_Text_Color = { 0, 0, 0, 0xFF };    //black

    if( A.Username != "" ){//Text is not empty
        TM_Username.Load_Text_Texture( A.Username.c_str(), renderer, Black_Text_Color );//Render new text
    }else{
        TM_Username.Load_Text_Texture( " ", renderer, Black_Text_Color );//Render new text
    }
    TM_Username.Load_Text_Texture( A.Username.c_str(), renderer, Black_Text_Color );//Render new text
    
    Username_InputBox.Render( TM_Username, renderer );

    if( A.Password != "" ){//Text is not empty
        TM_Password.Load_Text_Texture( A.Password.c_str(), renderer, Black_Text_Color );//Render new text
    }else{
        TM_Password.Load_Text_Texture( " ", renderer, Black_Text_Color );//Render new text
    }
    
    Password_InputBox.Render( TM_Password, renderer );

    // cout<<"\n\t\t~ RenderText()";
}

void RegistrationPage :: Render(){
    SDL_RenderClear( renderer );

    TM_Background.loadMedia(renderer);
    RenderText();

    SDL_RenderPresent( renderer );
}

#endif
