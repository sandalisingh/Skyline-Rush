/*

g++ -o TopThree MySQL/TopThree.cc $(pkg-config --cflags    --libs sqlite3)

./TopThree

*/


#include <iostream>
#include <sqlite3.h>

using namespace std;


            // typedef int (*sqlite3_callback)(
            // void*,    /* Data provided in the 4th argument of sqlite3_exec() */
            // int,      /* The number of columns in row */
            // char**,   /* An array of strings representing fields in the row */
            // char**    /* An array of strings representing column names */
            // );

class LeaderBoard{
	public:
		// LeaderBoard();
		// static string *UsernameDESC;
		// static string *ScoreDESC;
		// static int i;
		void CollectData();
		void DisplayData();
};

string *UsernameDESC = new string[3];
string *ScoreDESC = new string[3];
int i = 0;

static int callback_LB(void* data, int argc, char** argv, char** azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		cout << azColName[i] << " = " << ( argv[i] ? argv[i] : "NULL" ) << "\n" ;
	}

	cout << endl;

	UsernameDESC[i] = argv[0];
	ScoreDESC[i] = argv[1];
	i++;

	return 0;
}

// int main(int argc, char** argv){
void LeaderBoard :: CollectData(){
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
    }

	sqlite3_close(DB);
	// return (0);
}

void LeaderBoard :: DisplayData(){
	CollectData();
	for(i = 0; i < 3; i++){
		cout<<"\nUSERNAME = "<<UsernameDESC[i]<<" SCORE = "<<ScoreDESC[i];
	}
}

int main(){
	LeaderBoard LB;
	LB.DisplayData();

	return 0;
}



// #include <iostream>
// #include <sqlite3.h>
// #include <string>
// //#include "TextureManager.h"

// using namespace std;

// int callback_LeaderBoard(void* data, int argc, char** argv, char** azColName);

// class LeaderBoard{

	

// 	public:
// 		static string* UsernameDesc;
// 		static string* ScoreDesc;
// 		static int i;

// 		// LeaderBoard();
// 		void CollectData();

// 		static void GetData( char* Username, char* Score );
// };

// int LeaderBoard :: i = 0;
// string* LeaderBoard :: UsernameDesc = NULL;
// string* LeaderBoard :: ScoreDesc = NULL;

// int callback_LeaderBoard(void* data, int argc, char** argv, char** azColName){
// 	int i;
// 	fprintf(stderr, "%s: ", (const char*)data);

// 	for (i = 0; i < argc; i++) {
// 		cout << azColName[i] << " = " << ( argv[i] ? argv[i] : "NULL" ) << "\n" ;
// 	}

// 	cout << endl;

// 	LeaderBoard :: UsernameDesc[i] = argv[0];
// 	LeaderBoard :: ScoreDesc[i] = argv[1];
// 	i++;

// 	// LeaderBoard :: GetData( argv[0], argv[1]);  

// 	return 0;
// }

// // void LeaderBoard :: GetData( char* Username, char* Score){
// // 	UsernameDesc[i] = Username;
// // 	ScoreDesc[i] = Score;
// // 	i++;

// // 	cout<<"\nGetData :: i = "<<i<<" Username = "<<UsernameDesc[i]<<"\nScore = "<<ScoreDesc[i];
	
// // }

// void LeaderBoard :: CollectData() {
// 	cout<<"\n\n\n---------------->>>> LEADERBOARD <<<<-------------------\n\n\n";

// 	sqlite3* DB;
//     char* messaggeError;
// 	int exit = 0;
// 	exit = sqlite3_open("Registration.db", &DB);
// 	string data("CALLBACK FUNCTION");

// 	string sql("SELECT Username , Score FROM Account ORDER BY Score DESC LIMIT 3;");
// 	if (exit) {
// 		cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
// 		// return (-1);
// 	}
// 	else{
// 		cout << "Opened Database Successfully!" << endl;
//     }
    
// 	exit = sqlite3_exec(DB, sql.c_str(), callback_LeaderBoard, (void*)data.c_str(), &messaggeError);
// 	if (exit != SQLITE_OK) {
// 		cerr << "\n\n\n> Error UPDATE DATABASE !\n\n\n" << endl;
//         cout<<"\n\n"<<messaggeError<<"\n\n";
// 		sqlite3_free(messaggeError);
// 	}
// 	else{
// 		cout << "Records created Successfully!" << endl;
//     }

// 	sqlite3_close(DB);
// 	// return true ;

// 	// cout<<"\n\n\n---------------->>>> LEADERBOARD <<<<-------------------\n\n\n";
// 	// for(int i = 0; i < 3; i++){
// 	// 	cout<<"\nUsername = "<<UsernameDesc[i]<<"\nScore = "<<ScoreDesc[i];
// 	// }

// 	// cout<<"\n\n\n---------------->>>> ~ LEADERBOARD <<<<-------------------\n\n\n";
// }

// int main(){
// 	LeaderBoard LB;
// 	LB.CollectData();
	
// 	cout<<"\n\n\n---------------->>>> LEADERBOARD <<<<-------------------\n\n\n";
// 	for(int i = 0; i < 3; i++){
// 		cout<<"\nUsername = "<<LeaderBoard::UsernameDesc[i]<<"\nScore = "<<LeaderBoard::ScoreDesc[i];
// 	}

// 	return 0;
// }