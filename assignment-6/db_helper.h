#ifndef DB_HELPER_H_   // Include guard 
#define DB_HELPER_H_

int create_db(char *dbname);  /* Creates table for each #-seperated file file */
int create_tables(char *dbname);  /* Creates table for each #-seperated file file */
int populate_table_from_file(char *dbname, char *filename, char *sql_command);  /* Read data from extentionless files into tables */
int populate_person_resources(char *dbname); /* Populate person_resources and display all data to user */
static int callback_log(void *data, int argc, char **argv, char **azColName);
static int callback_display_result(void *data, int argc, char **argv, char **azColName);
static int callback_write_to_file(void *data, int argc, char **argv, char **azColName);

#endif // DB_HELPER_H_