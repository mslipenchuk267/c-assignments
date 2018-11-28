#ifndef DB_HELPER_H_   /* Include guard */
#define DB_HELPER_H_

int create_db(char *filename);  /* Creates table for each #-seperated file file */
int create_tables(char *filename);  /* Creates table for each #-seperated file file */
int populate_tables(char *filename);  /* Creates table for each #-seperated file file */

#endif // DB_HELPER_H_