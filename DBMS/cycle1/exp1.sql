-- ========================================================================
-- EXPERIMENT 1: College and Faculty Management System
-- ========================================================================

-- Create the following two tables:
-- • College: consisting of fields — college code, college name, address
-- • Faculty: consisting of fields — college code, faculty code, faculty name, 
--   qualification, experience (in number of years), department, address. 
--   The field college code is a foreign key referencing the College table.

CREATE DATABASE IF NOT EXISTS student;
USE student;

-- Create college table
CREATE TABLE college (
    college_code VARCHAR(20) PRIMARY KEY,
    college_name VARCHAR(20),
    address VARCHAR(20)
);

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

-- Insert sample data into college table
INSERT INTO college (college_code, college_name, address) VALUES 
    ('errn', 'ut', '6407 Barrows Parkway'),
    ('jlxo', 'tempore', '2222 Kemmer LocksWa'),
    ('mdau', 'blanditiis', '9708 Ebert Coves Apt'),
    ('ptlc', 'eum', '9724 Koss HarborLak'),
    ('ryzf', 'natus', '78364 Blick Hills Ap');

-- Insert sample data into faculty table
INSERT INTO faculty (college_code, faculty_code, faculty_name, qualification, experience, department, address)
VALUES 
    ('errn', 201, 'Dr. Laura', 'PhD', 12, 'Computer Science', '12 Elm St'),
    ('jlxo', 202, 'Prof. Mark', 'M.Tech', 9, 'Electrical', '45 Oak Ave'),
    ('errn', 203, 'Ms. Clara', 'M.Sc', 6, 'Physics', '78 Maple Blvd'),
    ('ptlc', 204, 'Dr. Henry', 'PhD', 15, 'Mathematics', '33 Pine Rd'),
    ('ryzf', 205, 'Mr. Steve', 'MBA', 8, 'Management', '99 Cedar Dr');

-- Query (a): List all faculty members of a specified college whose experience is greater than or equal to 10 years
SELECT * 
FROM faculty 
WHERE college_code = 'errn' 
  AND experience >= 10;
-- Result:
-- +--------------+--------------+--------------+---------------+------------+------------------+-----------+
-- | college_code | faculty_code | faculty_name | qualification | experience | department       | address   |
-- +--------------+--------------+--------------+---------------+------------+------------------+-----------+
-- | errn         |          201 | Dr. Laura    | PhD           |         12 | Computer Science | 12 Elm St |
-- +--------------+--------------+--------------+---------------+------------+------------------+-----------+

-- Query (b): List all faculty members of a specified college who have at least 10 years of experience but do not have an M.Tech degree
SELECT * 
FROM faculty 
WHERE college_code = 'errn' 
  AND experience >= 10  
  AND qualification != 'M.Tech';
-- Result:
-- +--------------+--------------+--------------+---------------+------------+------------------+-----------+
-- | college_code | faculty_code | faculty_name | qualification | experience | department       | address   |
-- +--------------+--------------+--------------+---------------+------------+------------------+-----------+
-- | errn         |          201 | Dr. Laura    | PhD           |         12 | Computer Science | 12 Elm St |
-- +--------------+--------------+--------------+---------------+------------+------------------+-----------+

-- Query (c): List the faculty members of a specified college, department-wise, in non-decreasing order of their seniority
SELECT college_code, faculty_code, faculty_name, department, experience 
FROM faculty 
WHERE college_code = 'errn'
ORDER BY department, experience DESC;
-- Result:
-- +--------------+--------------+--------------+------------------+------------+
-- | college_code | faculty_code | faculty_name | department       | experience |
-- +--------------+--------------+--------------+------------------+------------+
-- | errn         |          201 | Dr. Laura    | Computer Science |         12 |
-- | errn         |          203 | Ms. Clara    | Physics          |          6 |
-- +--------------+--------------+--------------+------------------+------------+

-- Query (d): List the names of colleges having more than a specified number of faculty members
SELECT c.college_name, COUNT(*) AS faculty_members_count  
FROM faculty f 
INNER JOIN college c ON f.college_code = c.college_code 
GROUP BY f.college_code, c.college_name
HAVING faculty_members_count > 1;
-- Result:
-- +--------------+-----------------------+
-- | college_name | faculty_members_count |
-- +--------------+-----------------------+
-- | ut           |                     2 |
-- +--------------+-----------------------+

-- Query (e): List the names of the colleges with the least and the most number of faculty members
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
-- Result:
-- +--------------+---------------+------+
-- | college_name | faculty_count | type |
-- +--------------+---------------+------+
-- | tempore      |             1 | MIN  |
-- | eum          |             1 | MIN  |
-- | natus        |             1 | MIN  |
-- | ut           |             2 | MAX  |
-- +--------------+---------------+------+

DROP DATABASE student;
