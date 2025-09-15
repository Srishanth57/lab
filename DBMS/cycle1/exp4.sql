
-- Create and use database
CREATE DATABASE student; 
USE student; 

-- Create book table
CREATE TABLE book (
    accession_no INT PRIMARY KEY,
    title VARCHAR(20),
    publisher VARCHAR(30),
    year INT,
    date_of_purchase DATE,
    status VARCHAR(30)
);

-- Create member table
CREATE TABLE member (
    member_id INT PRIMARY KEY,
    name VARCHAR(30),
    number_of_books_issued INT,
    max_limit INT
);

-- Create books_issue table
CREATE TABLE books_issue (
    accession_no INT,
    member_id INT,
    date_of_issue DATE,
    PRIMARY KEY (accession_no, member_id, date_of_issue),
    FOREIGN KEY (accession_no) REFERENCES book(accession_no),
    FOREIGN KEY (member_id) REFERENCES member(member_id)
);

-- Insert sample data into book table
INSERT INTO book VALUES
    (1001, 'C++ Primer', 'Pearson', 2018, '2021-03-15', 'Issued'),
    (1002, 'Java Basics', 'McGraw-Hill', 2019, '2021-05-20', 'Issued'),
    (1003, 'Python Crash', 'O\'Reilly', 2020, '2022-01-10', 'Issued'),
    (1004, 'DBMS Concepts', 'Pearson', 2017, '2020-08-05', 'Issued'),
    (1005, 'Operating Systems', 'Tata McGraw', 2016, '2019-12-12', 'Issued'),
    (1006, 'Discrete Math', 'Cengage', 2021, '2023-07-25', 'Issued'),
    (1007, 'AI Basics', 'Springer', 2022, '2024-01-30', 'Issued'),
    (1008, 'Networking', 'Wiley', 2020, '2022-10-18', 'Issued'),
    (1009, 'System Software', 'Pearson', 2020, '2024-10-18', 'Not Issued');

-- Insert sample data into member table
INSERT INTO member VALUES
    (201, 'Ananya Sharma', 3, 3),
    (202, 'Ravi Kumar', 2, 4),
    (203, 'Megha Jain', 0, 2),
    (204, 'Sunil Verma', 3, 5),
    (205, 'Priya Singh', 1, 3);

-- Insert sample data into books_issue table
INSERT INTO books_issue VALUES
    (1002, 201, '2025-08-01'),
    (1005, 201, '2025-08-11'),
    (1006, 201, '2025-08-12'),
    (1008, 201, '2025-08-13'),
    (1004, 202, '2025-07-20'),
    (1003, 202, '2025-07-22'),
    (1001, 204, '2025-08-05'),
    (1007, 204, '2025-08-08'),
    (1003, 204, '2025-08-09'),
    (1006, 205, '2025-08-10');

-- Query (a): List books that are due (issued more than 15 days ago)
SELECT b.title, bi.date_of_issue 
FROM book b 
JOIN books_issue bi ON b.accession_no = bi.accession_no 
WHERE bi.date_of_issue < DATE_SUB(CURDATE(), INTERVAL 15 DAY);
/*
Result:
+-------------------+---------------+
| title             | date_of_issue |
+-------------------+---------------+
| C++ Primer        | 2025-08-05    |
| Java Basics       | 2025-08-01    |
| Python Crash      | 2025-08-09    |
| Python Crash      | 2025-07-22    |
| DBMS Concepts     | 2025-07-20    |
| Operating Systems | 2025-08-11    |
| Discrete Math     | 2025-08-10    |
| Discrete Math     | 2025-08-12    |
| AI Basics         | 2025-08-08    |
| Networking        | 2025-08-13    |
+-------------------+---------------+
*/

-- Query (b): Members who cannot be issued any more books
SELECT * 
FROM member 
WHERE number_of_books_issued = max_limit;
/*
Result:
+-----------+---------------+------------------------+-----------+
| member_id | name          | number_of_books_issued | max_limit |
+-----------+---------------+------------------------+-----------+
|       201 | Ananya Sharma |                      3 |         3 |
+-----------+---------------+------------------------+-----------+
*/

-- Query (c): Book issued to maximum and minimum number of members
(SELECT b.accession_no, b.title, COUNT(DISTINCT bi.member_id) AS max_min_members 
 FROM book b 
 JOIN books_issue bi ON b.accession_no = bi.accession_no 
 GROUP BY b.accession_no, b.title 
 ORDER BY max_min_members DESC 
 LIMIT 1)
UNION
(SELECT b.accession_no, b.title, COUNT(DISTINCT bi.member_id) AS max_min_members 
 FROM book b 
 JOIN books_issue bi ON b.accession_no = bi.accession_no 
 GROUP BY b.accession_no, b.title
 ORDER BY max_min_members ASC 
 LIMIT 1);
/*
Result:
+--------------+--------------+-----------------+
| accession_no | title        | max_min_members |
+--------------+--------------+-----------------+
|         1003 | Python Crash |               2 |
|         1001 | C++ Primer   |               1 |
+--------------+--------------+-----------------+
*/

-- Query (d): Books issued to every member and books not issued to any member
-- Books issued to every member
SELECT b.accession_no, b.title, b.status, COUNT(DISTINCT bi.member_id) AS total_members_count
FROM book b
JOIN books_issue bi ON b.accession_no = bi.accession_no
WHERE b.status = 'Issued'
GROUP BY b.accession_no, b.title, b.status
HAVING COUNT(DISTINCT bi.member_id) = (SELECT COUNT(*) FROM member)

UNION

-- Books not issued to any member
SELECT b.accession_no, b.title, b.status, 0 AS total_members_count
FROM book b
WHERE b.status = 'Not Issued';
/*
Result:
+--------------+-----------------+------------+---------------------+
| accession_no | title           | status     | total_members_count |
+--------------+-----------------+------------+---------------------+
|         1009 | System Software | Not Issued |                   0 |
+--------------+-----------------+------------+---------------------+
*/

-- Drop database
DROP DATABASE student;


