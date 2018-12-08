#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include "db_helper.h"
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main ( void ){
	create_db("my_database.db");
	return 0;
}
