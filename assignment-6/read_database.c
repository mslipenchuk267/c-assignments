#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h" 

static int callback_display_result(void *data, int argc, char **argv, char **azColName);
static int callback_write_to_file(void *data, int argc, char **argv, char **azColName);

static int callback_display_result(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}

static int callback_write_to_file(void *data, int argc, char **argv, char **azColName){
	int i;
	char *result;
	FILE *fp;
	
	fp = fopen("testfile", "a");
	for(i = 0; i<argc; i+=2){
		result = (char *)malloc(11);
		strcpy(result,argv[i] ? argv[i] : "NULL");
		strcat(result,"#");
		strcat(result, argv[i++] ? argv[i++] : "NULL");
		strcat(result,"\n");
		fputs(result,fp);
		free(result);
	}
	fclose(fp);
	return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Record";

   /* Open database */
   rc = sqlite3_open("my_database.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "SELECT DISTINCT P.TUID, RR.RESOURCE_ID, A.NAME FROM PERSON_ROLES P " \
			"JOIN RESOURCES_ROLES RR ON P.ROLE_ID = RR.ROLE_ID " \
			"JOIN RESOURCES A ON  A.ID = RR.RESOURCE_ID";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback_display_result, (void*)data, &zErrMsg);
   
	/* Create SQL statement */
	sql = "SELECT DISTINCT P.TUID, RR.RESOURCE_ID FROM PERSON_ROLES P " \
			"JOIN RESOURCES_ROLES RR ON P.ROLE_ID = RR.ROLE_ID";
   
	rc = sqlite3_exec(db, sql, callback_write_to_file, (void*)data, &zErrMsg);
   
	if( rc != SQLITE_OK ) {
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	} else {
	  fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(db);
	return 0;
}