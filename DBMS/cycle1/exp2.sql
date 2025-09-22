-- ========================================================================
-- EXPERIMENT 2: Library Management System
-- ========================================================================

-- Create the following table for a Library Management System:
-- • Book: consisting of fields — accession no, title, publisher, author, 
--   date of purchase, date of publishing, status
-- The status field can have one of the following values:
-- • issued • present in the Library • reference • cannot be issued

CREATE DATABASE student;
USE student;

-- Create book table
CREATE TABLE book (
    accession_no INT PRIMARY KEY,
    title VARCHAR(30),
    publisher VARCHAR(30),
    author VARCHAR(30),
    date_of_purchase DATE,
    date_of_publishing DATE,
    status VARCHAR(40)
);

-- Insert sample data into book table
INSERT INTO book (accession_no, title, publisher, author, date_of_purchase, date_of_publishing, status) VALUES
    (201, 'Learn SQL', 'TechBooks', 'John Doe', '2025-05-01', '2024-12-01', 'present in the Library'),
    (202, 'Learn SQL', 'TechBooks', 'John Doe', '2025-05-01', '2024-12-01', 'issued'),
    (203, 'Python Basics', 'CodePress', 'Jane Smith', '2023-10-20', '2023-08-01', 'present in the Library'),
    (204, 'Python Basics', 'CodePress', 'Jane Smith', '2023-10-22', '2023-08-01', 'cannot be issued'),
    (205, 'Python Basics', 'CodePress', 'Jane Smith', '2023-11-01', '2023-08-01', 'issued'),
    (206, 'Modern Web Dev', 'WebPress', 'Chris Lee', '2024-01-15', '2023-12-05', 'reference'),
    (207, 'Modern Web Dev', 'WebPress', 'Chris Lee', '2024-01-15', '2023-12-05', 'present in the Library'),
    (208, 'Data Science 101', 'DataBooks', 'Maria Garcia', '2023-09-25', '2023-06-25', 'issued'),
    (209, 'Data Science 101', 'DataBooks', 'Maria Garcia', '2023-09-25', '2023-06-25', 'present in the Library'),
    (210, 'History of AI', 'FuturePub', 'Alan Turing', '2024-10-01', '2022-11-01', 'reference'),
    (221, 'Cloud Computing Basics', 'TechNova', 'Emily Zhang', '2025-01-10', '2024-12-01', 'present in the Library'),
    (222, 'Cloud Computing Basics', 'TechNova', 'Emily Zhang', '2025-01-10', '2024-12-01', 'present in the Library'),
    (223, 'Cloud Computing Basics', 'TechNova', 'Emily Zhang', '2025-01-10', '2024-12-01', 'present in the Library'),
    (224, 'Cloud Computing Basics', 'TechNova', 'Emily Zhang', '2025-01-10', '2024-12-01', 'present in the Library'),
    (225, 'Cloud Computing Basics', 'TechNova', 'Emily Zhang', '2025-01-10', '2024-12-01', 'present in the Library'),
    (226, 'Cloud Computing Basics', 'TechNova', 'Emily Zhang', '2025-01-10', '2024-12-01', 'present in the Library'),
    (227, 'Cloud Computing Basics', 'TechNova', 'Emily Zhang', '2025-01-10', '2024-12-01', 'present in the Library'),
    (228, 'Cloud Computing Basics', 'TechNova', 'Emily Zhang', '2025-01-10', '2024-12-01', 'present in the Library'),
    (229, 'Cloud Computing Basics', 'TechNova', 'Emily Zhang', '2025-01-10', '2024-12-01', 'present in the Library'),
    (230, 'Cloud Computing Basics', 'TechNova', 'Emily Zhang', '2025-01-10', '2024-12-01', 'present in the Library'),
    (211, 'Encyclopedia of Biology', 'EduPress', 'Dr. Emily Brown', '2023-05-10', '2022-11-15', 'reference'),
    (212, 'Encyclopedia of Biology', 'EduPress', 'Dr. Emily Brown', '2023-05-10', '2022-11-15', 'reference'),
    (213, 'History of AI', 'FuturePub', 'Alan Turing', '2023-01-05', '2022-11-01', 'reference'),
    (214, 'Mathematics Handbook', 'SciBooks', 'Isaac Newton', '2024-02-18', '2023-10-12', 'reference'),
    (215, 'Mathematics Handbook', 'SciBooks', 'Isaac Newton', '2024-02-18', '2023-10-12', 'reference');

-- Query (a): List the total number of copies of each book in the library
SELECT title, COUNT(*) AS book_copies 
FROM book 
GROUP BY title;
-- Result:
-- +-------------------------+-------------+
-- | title                   | book_copies |
-- +-------------------------+-------------+
-- | Learn SQL               |           2 |
-- | Python Basics           |           3 |
-- | Modern Web Dev          |           2 |
-- | Data Science 101        |           2 |
-- | History of AI           |           2 |
-- | Encyclopedia of Biology |           2 |
-- | Mathematics Handbook    |           2 |
-- | Cloud Computing Basics  |          10 |
-- +-------------------------+-------------+

-- Query (b): List the total number of reference copies for each book in the library
SELECT title, COUNT(*) AS reference_copy_count 
FROM book 
WHERE status = 'reference' 
GROUP BY title;
-- Result:
-- +-------------------------+----------------------+
-- | title                   | reference_copy_count |
-- +-------------------------+----------------------+
-- | Modern Web Dev          |                    1 |
-- | History of AI           |                    2 |
-- | Encyclopedia of Biology |                    2 |
-- | Mathematics Handbook    |                    2 |
-- +-------------------------+----------------------+

-- Query (c): For each book in the library, obtain: the total number of issued copies, 
-- the number of copies currently available in the library, and the number of reference copies
SELECT title, 
       SUM(CASE WHEN status = 'issued' THEN 1 ELSE 0 END) AS issued_copies,
       SUM(CASE WHEN status = 'present in the Library' THEN 1 ELSE 0 END) AS avail_copies,
       SUM(CASE WHEN status = 'reference' THEN 1 ELSE 0 END) AS reference_copies
FROM book 
GROUP BY title;
-- Result:
-- +-------------------------+---------------+--------------+------------------+
-- | title                   | issued_copies | avail_copies | reference_copies |
-- +-------------------------+---------------+--------------+------------------+
-- | Learn SQL               |             1 |            1 |                0 |
-- | Python Basics           |             1 |            1 |                0 |
-- | Modern Web Dev          |             0 |            1 |                1 |
-- | Data Science 101        |             1 |            1 |                0 |
-- | History of AI           |             0 |            0 |                2 |
-- | Encyclopedia of Biology |             0 |            0 |                2 |
-- | Mathematics Handbook    |             0 |            0 |                2 |
-- | Cloud Computing Basics  |             0 |           10 |                0 |
-- +-------------------------+---------------+--------------+------------------+

-- Query (d): List the details of all books whose status is set to "cannot be issued" publisherwise
SELECT * 
FROM book 
WHERE status = 'cannot be issued' 
ORDER BY publisher ASC;
-- Result:
-- +--------------+---------------+-----------+------------+------------------+--------------------+------------------+
-- | accession_no | title         | publisher | author     | date_of_purchase | date_of_publishing | status           |
-- +--------------+---------------+-----------+------------+------------------+--------------------+------------------+
-- |          204 | Python Basics | CodePress | Jane Smith | 2023-10-22       | 2023-08-01         | cannot be issued |
-- +--------------+---------------+-----------+------------+------------------+--------------------+------------------+

-- Query (e): List the details of all books that are categorized as new arrivals 
-- (i.e., books purchased within the last 6 months)
SELECT * 
FROM book 
WHERE date_of_purchase >= DATE_SUB(CURRENT_DATE, INTERVAL 6 MONTH);
-- Result:
-- +--------------+-----------+-----------+----------+------------------+--------------------+------------------------+
-- | accession_no | title     | publisher | author   | date_of_purchase | date_of_publishing | status                 |
-- +--------------+-----------+-----------+----------+------------------+--------------------+------------------------+
-- |          201 | Learn SQL | TechBooks | John Doe | 2025-05-01       | 2024-12-01         | present in the Library |
-- |          202 | Learn SQL | TechBooks | John Doe | 2025-05-01       | 2024-12-01         | issued                 |
-- +--------------+-----------+-----------+----------+------------------+--------------------+------------------------+

-- Query (f): List the details of each famous book. A book is considered famous if:
-- • it was purchased within 1 year of its publishing date, and
-- • it has more than 10 total copies in the library
SELECT title, COUNT(*) AS count_of_famous_book_copies 
FROM book 
WHERE date_of_purchase <= DATE_ADD(date_of_publishing, INTERVAL 12 MONTH)
GROUP BY title 
HAVING count_of_famous_book_copies >= 10;
-- Result:
-- +------------------------+-----------------------------+
-- | title                  | count_of_famous_book_copies |
-- +------------------------+-----------------------------+
-- | Cloud Computing Basics |                          10 |
-- +------------------------+-----------------------------+

DROP DATABASE student;

