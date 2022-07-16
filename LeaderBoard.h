#ifndef LeaderBoard_h
#define LeaderBoard_h

#include <sqlite3.h>
#include "TextureManager.h"

class LeaderBoard{
	public:
		LeaderBoard();
		bool Data_Collected;
		void CollectData();
		bool DisplayData(SDL_Renderer *renderer);
		static int callback_LB(void* data, int argc, char** argv, char** azColName);
};

string *UsernameDESC = new string[3];
string *ScoreDESC = new string[3];
int K = 0;

LeaderBoard :: LeaderBoard(){
	Data_Collected = false;
}

int LeaderBoard :: callback_LB(void* data, int argc, char** argv, char** azColName){
	int i;
	// fprintf(stderr, "%s: ", (const char*)data);

	// for (i = 0; i < argc; i++) {
	// 	cout << azColName[i] << " = " << ( argv[i] ? argv[i] : "NULL" ) << "\n" ;
	// }

	// cout << endl;

	UsernameDESC[K] = argv[0];
	ScoreDESC[K] = argv[1];
	K++;

	cout<<"\n> callback_LB : USERNAME = "<<UsernameDESC[i]<<" SCORE = "<<ScoreDESC[i];

	return 0;
}

// int main(int argc, char** argv){
void LeaderBoard :: CollectData(){
	// Data_Collected = false;

	sqlite3* DB;
    char* messaggeError;
	int exit = 0;
	exit = sqlite3_open("Registration.db", &DB);
	string data("CALLBACK FUNCTION");

	string sql("SELECT Username , Score FROM Account ORDER BY Score DESC LIMIT 3;");
	if (exit) {
		cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
		//return (-1);
		return ;
	}
	else{
		cout << "Opened Database Successfully!" << endl;
    }
    
	exit = sqlite3_exec(DB, sql.c_str(), callback_LB, (void*)data.c_str(), &messaggeError);
	if (exit != SQLITE_OK) {
		cerr << "\n\n\n> Error !\n\n\n" << endl;
        cout<<"\n\n"<<messaggeError<<"\n\n";
		sqlite3_free(messaggeError);
	}
	else{
		cout << "\nSuccessful !" << endl;
		Data_Collected = true;
    }

	sqlite3_close(DB);

	cout<<"\n> LB > CollectData() : ";
	for(K = 0; K < 3; K++){
		cout<<"\nUSERNAME = "<<UsernameDESC[K]<<" SCORE = "<<ScoreDESC[K];
	}

	
	// return (0);
}

bool LeaderBoard :: DisplayData(SDL_Renderer *renderer){
	// CollectData();

	TextureManager T_UsernameDESC, T_ScoreDESC;
	string text;
    SDL_Color Color = { 0 , 0 , 0 ,255};        //black

	int LeadeBoard_Display_Y = 530;
    for(int i = 0; i < 3; i++ ){
        text = UsernameDESC[i];  
		
        if(!T_UsernameDESC.printText(text, 227, LeadeBoard_Display_Y, renderer, Color, true)){
            return false;
        }     
    
        text = ScoreDESC[i];  
        if(!T_ScoreDESC.printText(text, 507, LeadeBoard_Display_Y, renderer, Color, true)){
            return false;
        } 
        
        LeadeBoard_Display_Y += 35;
    }  

	return true;
}


#endif