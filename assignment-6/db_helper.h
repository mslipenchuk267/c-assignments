#ifndef DB_HELPER_H_   // Include guard 
#define DB_HELPER_H_

int create_db(char **filename);  /* Creates table for each #-seperated file file */
int create_tables(char *filename);  /* Creates table for each #-seperated file file */
int populate_given_table(char *filename, char *sql_command);  /* Read data from extentionless files into tables */
int populate_person_resources(char *filename); /* Use tables to populate person_resources */
int tokenIsNumber(char *token); /* Check if token from line is number */

#endif // DB_HELPER_H_