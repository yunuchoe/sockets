#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {

    MYSQL *conn; // MySQL connection handle
    MYSQL_RES *res; // Result set for queries
    MYSQL_ROW row; // Row in the result set

    // MySQL server details
    const char *server = "127.0.0.1";

    // Use IP or "localhost"
    const char *user = "root"; // MySQL username
    const char *password = "root";

    // MySQL password
    const char *database = "library";

    // Name of the database
    // Initialize MySQL connection
    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection failed: %s\n",
        mysql_error(conn));
        return EXIT_FAILURE;
    }

    printf("Connected to the MySQL database successfully.\n");

    // Run a query
    const char *query = "SELECT * FROM books;";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Store the result set
    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Failed to retrieve result set: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE; 
    }

    // my new stuff
    int status = 1; // used for the menu to ensure it runs until this value changes
    int input = 0; // the value to keep track of which menu state we are in
    int main_menu = 1; // main menu toggle

    while(status == 1){ // loop until broken
    
        if(input == 0){
            // print the menu
            printf("\nLibrary Database Menu\n");
            printf("[1] Add a new book\n");
            printf("[2] View all books\n");
            printf("[3] Search for a book by title\n");
            printf("[4] Exit\n");
            if (scanf("%d", &input) != 1){ // check that an int was given
                input = -1; // forces invalid input which will end program
            }
        }else if(input == 1){ // perfrom the add function
            // store the title
            char title[255];
            printf("\nTitle of new book: ");
            while (getchar() != '\n' && getchar() != EOF); // clear buffer
            fgets(title, sizeof(title), stdin); // get the string from the user
            title[strcspn(title, "\n")] = '\0'; // remove the newline from fgets

            // store the name
            char author[255];
            printf("Author of new book: ");
            fgets(author, sizeof(author), stdin); // get the string from the user
            author[strcspn(author, "\n")] = '\0'; // remove the newline from fgets

            // store the year
            int year;
            printf("Year of publication: ");
            scanf("%d", &year);
            //getchar(); // consume newline character

            char query[255*4]; // buffer for search
            strcpy(query, "INSERT INTO books (title, author, year) VALUES ('");
            strcat(query, title);  // Append the title
            strcat(query, "', '");
            strcat(query, author); // Append the author
            strcat(query, "', ");
            char yearS[5]; // buffer for year as type string
            snprintf(yearS, 5, "%d", year); // Convert year to string
            strcat(query, yearS); // Append the year
            strcat(query, ");");

            // Run a query
            if (mysql_query(conn, query)) {
                fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
                continue;
            }

            input = 0; // clear to main menu
        }else if(input == 2){ // perfrom the view function
            // Run a query
            if (mysql_query(conn, query)) {
                fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
                continue;
            }

            // Store the result set
            res = mysql_store_result(conn);
            if (res == NULL) {
                fprintf(stderr, "Failed to retrieve result set: %s\n", mysql_error(conn));
                continue; 
            }

            // print the database
            printf("\n%-3s %-26s %-30s %-3s\n", "ID", "Title", "Author", "Year");
            while ((row = mysql_fetch_row(res)) != NULL) { 
                printf("%-3s %-26s %-30s %-3s\n", row[0], row[1], row[2], row[3]);
            }
            
            mysql_free_result(res); // free memory
            input = 0; // clear to main menu
        }else if(input == 3){ // perform the search function
            printf("\nTitle to search: ");
            char title[255]; // buffer for title
            while (getchar() != '\n' && getchar() != EOF); // clear buffer
            fgets(title, sizeof(title), stdin); // get the string from the user
            title[strcspn(title, "\n")] = '\0'; // remove the newline from fgets

            char query[255*2]; // buffer for search
            strcpy(query, "SELECT * FROM books WHERE title LIKE '%"); // look  into books with placeholder name
            strcat(query, title); // append the name
            strcat(query, "%'"); // need % at the end
            
            // Run a query
            if (mysql_query(conn, query)) {
                fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
                continue;
            }

            // Store the result set
            res = mysql_store_result(conn);
            if (res == NULL) {
                fprintf(stderr, "Failed to retrieve result set: %s\n", mysql_error(conn));
                continue; 
            }

            // printf the results
            printf("\n%-3s %-26s %-30s %-3s\n", "ID", "Title", "Author", "Year");
            while ((row = mysql_fetch_row(res)) != NULL) { 
                printf("%-3s %-26s %-30s %-3s\n", row[0], row[1], row[2], row[3]);
            }
    
            mysql_free_result(res); // free memory
            input = 0; // clear to main menu
        }else if(input == 4){ // exit this loop. the rest of the program will do the exit functions
            status = 0;
        }else{ // if none of the 4 options were selected, force an exit and error message
            printf("ERROR: Invalid input\n");
            status = -1;
        }
    }

    // Close connection
    mysql_close(conn);
    printf("Connection closed.\n");
    return EXIT_SUCCESS;
}