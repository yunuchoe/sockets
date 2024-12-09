README.txt
Act_socket activity

Short explanation of each question

Server:

Very similar to assignment 3's server question (much of the code is the same). 
The clients ask about 1 city and the server searches its system to see if there is a match
If so, return the information of the city, otherwise, indicate that the city was not found.
The clinet will also have that information sent back so that it can be read clientside.
Should work for any number of clients but I tested for for simplicty
clinet.c has Istanbul which is in the database
client2.c has Vienna which is not in the databse


Database:

again much of the base code is the same as in the lecture notes
the .sql simply runs the inital set up and creates the books database with the 5 books I added (top 5 best sellers from wikipedia)
the menu is pretty simple and operates like a fsm
simply put in the number corresponidng to the action/menu you want to go in
    add: the terminal will prompt the new names and then will add that book into the database
    view: simply shows all the books in the database tabularized
    search: searches for any matches in the database with the keyword
    exit: exits the program