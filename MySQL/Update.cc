/*

g++ -o Update MySQL/Update.cc $(pkg-config --cflags    --libs sqlite3)

./Update

*/


#include <iostream>
#include <sqlite3.h>

using namespace std;

int main(){
    sqlite3* DB;
	char* messaggeError;
    int Score = 8, Level = 1;
    string Username = "Sandali";
	int exit = sqlite3_open("Registration.db", &DB);
	string SelectALlFromTable_QUERY = "SELECT * FROM Account;";

    string sql( "UPDATE Account SET Score = ");

    sql = sql + to_string(Score) + " , Level = " + to_string(Level) + " WHERE Username = '" + Username + "' ;" ;

    cout<<"\n\nSQL \t"<<sql<<"\n\n";

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		cerr << "\n\n\n> Error UPDATE DATABASE !\n\n\n" << endl;
        cout<<"\n\n"<<messaggeError<<"\n\n";
		sqlite3_free(messaggeError);
	}
	else{
		cout << "Records created Successfully!" << endl;
    }

    sqlite3_close(DB);
}