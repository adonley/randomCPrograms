/*
 * Andrew Donley
 * August 12, 2013
 * Program to update a database with the minute time load
 *   deletes entries after 10 minutes.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include"/usr/include/mysql/mysql.h"
#include<sys/time.h>

int main() {
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
   char *server = "localhost";
   char *user = "adonley1";
   char *password = "";
   char *database = "adonley1";
   char load_query[256], load_value[256];
   int fdes[2];
   int pid;
   int i;
   struct timeval tv;
   gettimeofday(&tv,NULL);
   int time_now;

   // Create pipe to communicate
   FILE *fp;
   int status;
   char output[1024];

   fp = popen("uptime","r");
   fgets(output,sizeof(output)-1,fp);
  
   strcpy(load_value, strtok(output," ,"));
   for(i = 0; i < 10; i++) {
     strcpy(load_value,strtok(NULL," ,"));
     //printf("%s\n",load_value);
   }
   // Create the database update
   strcpy(load_query,"INSERT INTO loads (value) VALUES (");
   strcat(load_query,load_value);
   strcat(load_query,");"); 

   conn = mysql_init(NULL);
   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   } 
   /* send SQL query */
   if (mysql_query(conn, load_query)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
  
   // Delete the entries that are old.
   /*strcpy(load_query,"SELECT * FROM loads ORDER BY submission_time DESC limit 10;");
   if (mysql_query(conn, load_query)) {
      fprintf(stderr, "%s \n", mysql_error(conn));
      exit(1);
   }
   
   res = mysql_use_result(conn);
   if(row = mysql_fetch_row(res) != NULL) {
     printf("%s \n", row[0]);
     mysql_free_result(res); */
   strcpy(load_query,"DELETE FROM loads WHERE submission_time < NOW() - 900;");
   if(mysql_query(conn, load_query)) {
     fprintf(stderr, "%s \n", mysql_error(conn));
     exit(1);
   }
     //strcat(load_query,atoi();
     //strcat(load_query,";"); 
   //}
   /*
   time_now = tv.tv_sec - 600;
   strcpy(load_query,"DELETE FROM loads WHERE submission_time < ");
   sprintf(load_value,"%i",time_now);
   strcat(load_query,load_value);
   strcat(load_query," ;");
   printf("%s \n", load_query);
   if (mysql_query(conn,load_query)) {
     fprintf(stderr, "%s\n", mysql_error(conn));
     exit(1);
   }
   //res = mysql_use_result(conn);
    output table name */
   //while ((row = mysql_fetch_row(res)) != NULL)
   //  printf("%s \n", row[0]);
   /* close connection */
   //mysql_free_result(res);
   
   mysql_close(conn);
   pclose(fp);
   return 0;
}
