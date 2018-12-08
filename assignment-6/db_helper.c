#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sqlite3.h" 
#include "db_helper.h"

/* Prints out all Entries */
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int create_db(char* filename) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open(filename, &db);

	if( rc ) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return 0;
	} else {
		fprintf(stderr, "Opened database successfully\n");
	}
	sqlite3_close(db);
	return 0;
}
