
-- Create and use database
CREATE DATABASE student;
USE student;

-- Create college table
CREATE TABLE college (
    college_code VARCHAR(20) PRIMARY KEY,
    college_name VARCHAR(20),
    address VARCHAR(20)
);

-- Insert sample data into college table
INSERT INTO college (college_code, college_name, address) VALUES 
    ('errn', 'ut', '6407 Barrows Parkway'),
    ('jlxo', 'tempore', '2222 Kemmer LocksWa'),
    ('mdau', 'blanditiis', '9708 Ebert Coves Apt'),
    ('ptlc', 'eum', '9724 Koss HarborLak'),
    ('ryzf', 'natus', '78364 Blick Hills Ap');

-- Create faculty table
CREATE TABLE faculty (
    college_code VARCHAR(20),
    faculty_code INT,
    faculty_name VARCHAR(20),
    qualification VARCHAR(20),
    experience INT,
    department VARCHAR(20),
    address VARCHAR(20),
    FOREIGN KEY (college_code) REFERENCES college(college_code)
);

-- Insert sample data into faculty table
INSERT INTO faculty (college_code, faculty_code, faculty_name, qualification, experience, department, address)
VALUES 
    ('errn', 201, 'Dr. Laura', 'PhD', 12, 'Computer Science', '12 Elm St'),
    ('jlxo', 202, 'Prof. Mark', 'M.Tech', 9, 'Electrical', '45 Oak Ave'),
    ('errn', 203, 'Ms. Clara', 'M.Sc', 6, 'Physics', '78 Maple Blvd'),
    ('ptlc', 204, 'Dr. Henry', 'PhD', 15, 'Mathematics', '33 Pine Rd'),
    ('ryzf', 205, 'Mr. Steve', 'MBA', 8, 'Management', '99 Cedar Dr');

-- Query (a): List faculty members of a specified college with experience >= 10 years
SELECT * 
FROM faculty 
WHERE college_code = 'errn' 
  AND experience >= 10;
/*
Result:
+--------------+--------------+--------------+---------------+------------+------------------+-----------+
| college_code | faculty_code | faculty_name | qualification | experience | department       | address   |
+--------------+--------------+--------------+---------------+------------+------------------+-----------+
| errn         |          201 | Dr. Laura    | PhD           |         12 | Computer Science | 12 Elm St |
+--------------+--------------+--------------+---------------+------------+------------------+-----------+
*/

-- Query (b): List faculty with experience >= 10 years but no M.Tech degree
SELECT * 
FROM faculty 
WHERE college_code = 'errn' 
  AND experience >= 10  
  AND qualification != 'M.Tech';
/*
Result:
+--------------+--------------+--------------+---------------+------------+------------------+-----------+
| college_code | faculty_code | faculty_name | qualification | experience | department       | address   |
+--------------+--------------+--------------+---------------+------------+------------------+-----------+
| errn         |          201 | Dr. Laura    | PhD           |         12 | Computer Science | 12 Elm St |
+--------------+--------------+--------------+---------------+------------+------------------+-----------+
*/

-- Query (c): List faculty members department-wise in order of seniority
SELECT college_code, faculty_code, faculty_name, department, experience 
FROM faculty 
WHERE college_code = 'errn'
ORDER BY department, experience DESC;
/*
Result:
+--------------+--------------+--------------+------------------+------------+
| college_code | faculty_code | faculty_name | department       | experience |
+--------------+--------------+--------------+------------------+------------+
| errn         |          201 | Dr. Laura    | Computer Science |         12 |
| errn         |          203 | Ms. Clara    | Physics          |          6 |
+--------------+--------------+--------------+------------------+------------+
*/

-- Query (d): List colleges with more than specified number of faculty members
SELECT c.college_name, COUNT(*) AS faculty_members_count  
FROM faculty f 
INNER JOIN college c ON f.college_code = c.college_code 
GROUP BY f.college_code, c.college_name
HAVING faculty_members_count > 1;
/*
Result:
+--------------+-----------------------+
| college_name | faculty_members_count |
+--------------+-----------------------+
| ut           |                     2 |
+--------------+-----------------------+
*/

-- Query (e): List colleges with least and most number of faculty members
CREATE VIEW collegeFacultyCount AS 
SELECT c.college_name, COUNT(*) AS faculty_count 
FROM college c 
INNER JOIN faculty f ON c.college_code = f.college_code 
GROUP BY c.college_name;

SELECT college_name, faculty_count, 'MIN' AS type 
FROM collegeFacultyCount 
WHERE faculty_count = (SELECT MIN(faculty_count) FROM collegeFacultyCount)  
UNION ALL  
SELECT college_name, faculty_count, 'MAX' AS type 
FROM collegeFacultyCount 
WHERE faculty_count = (SELECT MAX(faculty_count) FROM collegeFacultyCount);
/*
Result:
+--------------+---------------+------+
| college_name | faculty_count | type |
+--------------+---------------+------+
| tempore      |             1 | MIN  |
| eum          |             1 | MIN  |
| natus        |             1 | MIN  |
| ut           |             2 | MAX  |
+--------------+---------------+------+
*/

-- Drop database
DROP DATABASE student;


