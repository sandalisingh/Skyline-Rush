/*

g++ -o Create_Database_Table MySQL/Create_Database_Table.cc $(pkg-config --cflags    --libs sqlite3)

./Create_Database_Table

*/

//CREATING DATABASE & TABLE

#include <iostream>
#include <sqlite3.h>

using namespace std;
  
static int callback(void* data, int argc, char** argv, char** azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}
  
int main(){
    
    sqlite3* DB;
    
    string sql = "CREATE TABLE Account("
                      "Username         CHAR(20)    PRIMARY KEY     NOT NULL        , "
                      "Password         CHAR(20)                    NOT NULL        , "
                      "Score            INT                         NOT NULL        ,"
                      "Level            INT                         NOT NULL        );";

    // string sql = "DROP TABLE Account";
    
    int exit = 0;  
    exit = sqlite3_open("Registration.db", &DB);        // - sqlite3_open(const char *filename, sqlite3 **ppDb)
    //If the database doesn’t exist yet, it is going to be created 
    //in the same directory where the process was executed.
    
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    //- sqlite3_exec(sqlite3*, const char *sql, sqlite_callback, void *data, char **errmsg)
  
    if (exit != SQLITE_OK) {
        cerr << "Error" << endl;
        sqlite3_free(messaggeError);
    }
    else{
        cout << "Successful" << endl;
    }

    string SelectALlFromTable_QUERY = "SELECT * FROM Account;";
    sqlite3_exec(DB, SelectALlFromTable_QUERY.c_str(), callback, NULL, NULL);
    
    sqlite3_close(DB);      //  - sqlite3_close(sqlite3 *ppDb)
    //closes the connection
    
    return (0);
}