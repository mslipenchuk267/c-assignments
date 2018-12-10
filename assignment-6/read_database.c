#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h" 

static int callback2(void *data, int argc, char **argv, char **azColName);

static int callback(void *data, int argc, char **argv, char **azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for(i = 0; i<argc; i++){
	  printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

static int callback2(void *data, int argc, char **argv, char **azColName){
	int i;
	char result[] = " ";
	FILE *fp;
	fp = fopen("person_resources", "w+");
	//fprintf(fp, "This is testing for fprintf...\n");
	fputs("This is testing for fputs...\n", fp);
	fclose(fp);

	fprintf(stderr, "%s: ", (const char*)data);
	
	for(i = 0; i<argc; i+=2){
		strcpt(result,argv[i] ? argv[i] : "NULL");
		strcat(result,"#");
		strcat(result,argv[i++] ? argv[i++] : "NULL");
		fputs(result, fp);
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}


int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("my_database.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
   /* Create SQL statement */
   sql = "SELECT DISTINCT P.TUID, RR.RESOURCE_ID, A.NAME FROM PERSON_ROLES P " \
			"JOIN RESOURCES_ROLES RR ON P.ROLE_ID = RR.ROLE_ID " \
			"JOIN RESOURCES A ON  A.ID = RR.RESOURCE_ID";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback2, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   return 0;
}