CREATE DATABASE library;

USE library;

CREATE TABLE books (
    id INT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(255) NOT NULL,
    author VARCHAR(255) NOT NULL,
    year INT NOT NULL
);

INSERT INTO books (title, author, year) VALUES
('A Tale of Two Cities', 'Charles Dickens', 1859),
('The Little Prince', 'Antoine de Saint-Exupéry', 1943),
('The Alchemist ', 'Paulo Coelho', 1988),
('The Philosophers Stone', 'J. K. Rowling', 1997),
('And Then There Were None', 'Agatha Christie', 1939);
