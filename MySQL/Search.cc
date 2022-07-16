/*

g++ -o Search MySQL/Search.cc $(pkg-config --cflags    --libs sqlite3)

./Search

*/


// INSERTION DELETION

#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

string SavedPassword, SavedScore, SavedLevel;

void getdata(char **arg){
    SavedPassword = arg[1];
    SavedScore = arg[2];
    SavedLevel = arg[3];

    cout<<"\nSAVED PASSWORD = "<<SavedPassword;
    cout<<"\nSAVED Score = "<<SavedScore;
    cout<<"\nSAVED Level = "<<SavedLevel;
}

static int callback(void* data, int argc, char** argv, char** azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

    // SavedPassword = argv[1];
    // cout<<"\nSAVED PASSWORD = "<<SavedPassword;
    // SavedScore = argv[2];
    // cout<<"\nSAVED Score = "<<SavedScore;
    // SavedLevel = argv[3];
    // cout<<"\nSAVED Level = "<<SavedLevel;

    getdata(argv);

	printf("\n");
	return 0;
}

int main(int argc, char** argv){
	sqlite3* DB;
	char* messaggeError;
    string Username;
    cout<<"\nENTER USERNAME = ";
    cin>>Username;

	int exit = sqlite3_open("Registration.db", &DB);

    // string sql("SELECT * FROM Account;");

	string SelectALlFromTable_QUERY = "SELECT * FROM Account WHERE Username = '";
    SelectALlFromTable_QUERY = SelectALlFromTable_QUERY + Username + "' ;" ;

    cout<<"\n\nQUERY\t\t"<<SelectALlFromTable_QUERY<<"\n\n";


	sqlite3_exec(DB, SelectALlFromTable_QUERY.c_str(), callback, NULL, NULL);

	
    cout<<"\nENTER PASSWORD = ";
    string InputPassword;
    cin>>InputPassword;

    if( InputPassword == SavedPassword ){
        cout<<"\nPASSWORD CORRECT !";
    }else{
        cout<<"\nPASSWORD WRONG !";
    }

	
	sqlite3_close(DB);
	return (0);
}
