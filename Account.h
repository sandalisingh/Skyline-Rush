#ifndef Account_h
#define Account_h

#include <iostream>
#include <sqlite3.h>
#include "Register.h"
//#include <string>

using namespace std;

// int callback_Account(void* data, int argc, char** argv, char** azColName);

//------------------------------>>>>>>>>>>> A C C O U N T <<<<<<<<<<<------------------------------------

class Account{
    private:
        
        int Score;  //users highest score ever
        int Level;

        static string SavedPassword, SavedScore, SavedLevel;
               
    
        string Username;
        string Password;

        void clearCredentials();
        void UpdateAccount();   //updates score and level of the logged in account

        bool CheckLogin();

        void newHighScore(int, int);    

        

        bool CreateAccount();

    public:
        Account();
        ~Account();
        static int GetDataFromDatabase(void* data, int argc, char** argv, char** azColName);  //char **arg
        

        friend class RegistrationPage;
};

string Account :: SavedPassword = "";
string Account :: SavedScore = "";
string Account :: SavedLevel = "";

Account :: Account(){
    cout<<"\nAccount()";
    clearCredentials();
}

void Account :: clearCredentials(){
    cout<<"\n\tAccount :: clearCreadentials()";
    Username = "";
    Password = "";
    Score = 0;
    Level = 0;
}

Account :: ~Account(){
    cout<<"\n~ Account()";
    cout<<"\nUSERNAME = "<<Username;
    cout<<"\nPASSWORD = "<<Password;
    cout<<"\nSCORE = "<<Score;
    cout<<"\nLEVEL = "<<Level;
}

void Account :: newHighScore(int CurrentGameScore, int CurrentGameLevel){
    cout<<"\n\tAccount :: newHighScore()";

    bool K;
    if(Score < CurrentGameScore){
        Score = CurrentGameScore;
        K = true;
    }
    if(Level < CurrentGameLevel){
        Level = CurrentGameLevel;
    }
    if( K == true){
        UpdateAccount();
    }   
}

void Account :: UpdateAccount(){
    cout<<"\n\tAccount :: UpdateAccount()";

    sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("Registration.db", &DB);
	string SelectALlFromTable_QUERY = "SELECT * FROM Account;";

    string sql( "UPDATE Account SET Score = ");

    sql =   sql + to_string(Score) + " , Level = " + to_string(Level) 
            + " WHERE Username = '" + Username + "' ;" ;

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		cerr << "\n\n\n> Error UPDATE DATABASE !\n\n\n" << endl;
		sqlite3_free(messaggeError);
	}
	else{
		cout << "Records created Successfully!" << endl;
    }

    sqlite3_close(DB);
}

//------------------------------>>>>>>>>>>> LOGIN INTO EXISTING ACCOUNT <<<<<<<<<<<------------------------------------

int Account :: GetDataFromDatabase(void* data, int argc, char** argv, char** azColName){  //char **arg
    cout<<"\n\tAccount :: GetDataFromDatabase()";

    SavedPassword = argv[1];
    SavedScore = argv[2];
    SavedLevel = argv[3];

    cout<<"\nSAVED PASSWORD = "<<SavedPassword;
    cout<<"\nSAVED Score = "<<SavedScore;
    cout<<"\nSAVED Level = "<<SavedLevel;

    return 0;
}

bool Account :: CheckLogin(){
    cout<<"\n\tAccount :: CheckLogin()";

    sqlite3* DB;
	int exit = sqlite3_open("Registration.db", &DB);

    string SelectALlFromTable_QUERY = "SELECT * FROM Account WHERE Username = '";
    SelectALlFromTable_QUERY = SelectALlFromTable_QUERY + Username + "' ;" ;

    cout<<"\n\nQUERY\t\t"<<SelectALlFromTable_QUERY<<"\n\n";

	// sqlite3_exec(DB, SelectALlFromTable_QUERY.c_str(), callback_Account, NULL, NULL);
    sqlite3_exec(DB, SelectALlFromTable_QUERY.c_str(), GetDataFromDatabase, NULL, NULL);
    sqlite3_close(DB);

    if( Password == SavedPassword ){
        cout<<"\nPASSWORD CORRECT !";

        Score = stoi(SavedScore);
        Level = stoi(SavedLevel);

        return true;
    }else{
        cout<<"\nPASSWORD WRONG !";
        return false;
    }	
}

// int callback_Account(void* data, int argc, char** argv, char** azColName){
// 	// int i;
// 	// fprintf(stderr, "%s: ", (const char*)data);
//
//     // cout<<"\n\n";
// 	// for (i = 0; i < argc; i++) {
// 	// 	cout<<azColName[i]<<" = "<<(argv[i] ? argv[i] : "NULL")<<"\n";
// 	// }
//     // cout<<"\n\n";
//
//     Account :: GetDataFromDatabase(argv);
 //   
// 	return 0;
// }

//------------------------------>>>>>>>>>>> CREATE NEW ACCOUNT <<<<<<<<<<<------------------------------------

bool Account :: CreateAccount(){
    cout<<"\n\tAccount :: CreateAcccount()";

    int success = false;
    sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("Registration.db", &DB);

    string sql(
		"INSERT INTO Account VALUES( '");

    sql = sql + Username + "' , '" + Password + "' , 0 , 0);";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		cerr << "\n\n\nError Insert\n\n\n" << endl;
		sqlite3_free(messaggeError);
        success = false;
	}
	else{
		cout << "Records created Successfully!" << endl;
        success = true;
    }

    sqlite3_close(DB);

    return success;
}

#endif  /* Account_h */

