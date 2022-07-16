/*

g++ -o Insertion_Deletion MySQL/Insertion_Deletion.cc $(pkg-config --cflags    --libs sqlite3)

./Insertion_Deletion

*/


// INSERTION DELETION

#include <iostream>
#include <sqlite3.h>
#include <string>

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

int main(int argc, char** argv){
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("Registration.db", &DB);
	string SelectALlFromTable_QUERY = "SELECT * FROM Account;";

	// cout << "STATE OF TABLE BEFORE INSERT" << endl;

	// sqlite3_exec(DB, SelectALlFromTable_QUERY.c_str(), callback, NULL, NULL);

	// string sql(
    //             "INSERT INTO Account VALUES( 'DefaultUsername' , 'DefaultPassword' , -1 , 0);"
	// 		    "INSERT INTO Account VALUES( 'Sandali' , 'Singh' , -1 , 0);"
    //             "INSERT INTO Account VALUES( 'Fin' , 'SandaliSingh' , -1 , 0);"
	// 			"INSERT INTO Account VALUES( 'ImaginaryDragon' , 'SandaliSingh' , -1 , 0);"
	// 			"INSERT INTO Account VALUES( 'Selena' , 'SandaliSingh' , -1 , 0);"
	// 			"INSERT INTO Account VALUES( 'Gigi' , 'SandaliSingh' , -1 , 0);"
	// 			"INSERT INTO Account VALUES( 'Diljit' , 'SandaliSingh' , -1 , 0);"
	// 			"INSERT INTO Account VALUES( 'Jass Manak' , 'SandaliSingh' , -1 , 0);"
    //         );

	string sql(
		"INSERT INTO Account VALUES( 'Sandali' , 'DILJITDOSANJ' , -10 , -10);"
	);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		cerr << "\n\n\nError Insert\n\n\n" << endl;
		sqlite3_free(messaggeError);
	}
	else{
		cout << "Records created Successfully!" << endl;
    }

	cout << "STATE OF TABLE AFTER INSERT" << endl;

	sqlite3_exec(DB, SelectALlFromTable_QUERY.c_str(), callback, NULL, NULL);

	// sql = "DELETE FROM Account WHERE Username = 'Sandali' ;";
	// exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

	// if (exit != SQLITE_OK) {
	// 	cerr << "Error DELETE" << endl;
	// 	sqlite3_free(messaggeError);	//deallocate memory to avoid memory leaks
	// }else{
	// 	cout << "Record deleted Successfully!" << endl;
    // }

	// cout << "STATE OF TABLE AFTER DELETE OF ELEMENT" << endl;
	// sqlite3_exec(DB, SelectALlFromTable_QUERY.c_str(), callback, NULL, NULL);

	sqlite3_close(DB);
	return (0);
}
