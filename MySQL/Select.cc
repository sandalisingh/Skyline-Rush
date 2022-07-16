/*

g++ -o Select MySQL/Select.cc $(pkg-config --cflags    --libs sqlite3)

./Select

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


static int callback(void* data, int argc, char** argv, char** azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		cout << azColName[i] << " = " << ( argv[i] ? argv[i] : "NULL" ) << "\n" ;
	}

	cout << endl;

	return 0;
}

int main(int argc, char** argv){
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("Registration.db", &DB);
	string data("CALLBACK FUNCTION");

	string sql("SELECT * FROM Account;");
	if (exit) {
		cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
		return (-1);
	}
	else{
		cout << "Opened Database Successfully!" << endl;
    }
    
	int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);

	if ( rc != SQLITE_OK ) {
		cerr << "Error SELECT" << endl;
	}else {
		cout << "Operation OK!" << endl;
	}

	sqlite3_close(DB);
	return (0);
}
