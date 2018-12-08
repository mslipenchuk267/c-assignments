#ifndef DB_HELPER_H_   // Include guard 
#define DB_HELPER_H_

int create_db(char *dbname);  /* Creates table for each #-seperated file file */
int create_tables(char *dbname);  /* Creates table for each #-seperated file file */
int populate_table_from_file(char *dbname, char *filename, char **sql_command);  /* Read data from extentionless files into tables */
int populate_person_resources(char *filename); /* Use tables to populate person_resources */

#endif // DB_HELPER_H_