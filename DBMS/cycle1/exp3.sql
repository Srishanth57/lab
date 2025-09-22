
-- ========================================================================
-- EXPERIMENT 3: Student Course Management System
-- ========================================================================

-- Create the following tables:
-- • Student (roll no, name, date of birth)
-- • Course (course id, name, fee, duration)

CREATE DATABASE student; 
USE student; 

-- Create student table
CREATE TABLE student (
    roll_no INT PRIMARY KEY,
    name VARCHAR(20),
    date_of_birth DATE
);

-- Create course table
CREATE TABLE course (
    course_id INT PRIMARY KEY,
    name VARCHAR(20),
    fees INT,
    duration VARCHAR(10)
);

-- Create junction table for student-course relationship
CREATE TABLE studentcourse (
    roll_no INT,
    course_id INT,
    PRIMARY KEY (roll_no, course_id),
    FOREIGN KEY (roll_no) REFERENCES student(roll_no),
    FOREIGN KEY (course_id) REFERENCES course(course_id)
);

-- Insert sample data into student table
INSERT INTO student VALUES
    (101, 'Alice', '2004-02-15'),
    (102, 'Bob', '2000-06-10'),
    (103, 'Charlie', '2002-11-20'),
    (104, 'David', '2005-01-25'),
    (105, 'Eva', '1999-08-05');

-- Insert sample data into course table
INSERT INTO course VALUES
    (1, 'B.Tech', 120000, '4 years'),
    (2, 'BCA', 90000, '3 years'),
    (3, 'MBA', 150000, '2 years'),
    (4, 'MCA', 110000, '3 years'),
    (5, 'B.Sc', 80000, '3 years');

-- Insert sample data into studentcourse table
INSERT INTO studentcourse VALUES
    (101, 1), (101, 2),
    (102, 1), (102, 3), (102, 4),
    (103, 2), (103, 3),
    (104, 1), (104, 2), (104, 3), (104, 4),
    (105, 1), (105, 2), (105, 3), (105, 4), (105, 5);

-- Query (a): List the names of all students who are greater than 18 years of age and have opted for the B.Tech course
SELECT s.name 
FROM student s 
JOIN studentcourse sc ON s.roll_no = sc.roll_no 
WHERE sc.course_id = 1 
  AND TIMESTAMPDIFF(YEAR, s.date_of_birth, CURDATE()) > 18;
-- Result:
-- +-------+
-- | name  |
-- +-------+
-- | Alice |
-- | Bob   |
-- | David |
-- | Eva   |
-- +-------+

-- Query (b): List the details of those courses whose fee is greater than that of the B.Tech course
SELECT name, fees 
FROM course 
WHERE fees > (SELECT fees FROM course WHERE name = 'B.Tech');
-- Result:
-- +------+--------+
-- | name | fees   |
-- +------+--------+
-- | MBA  | 150000 |
-- +------+--------+

-- Query (c): List the details of the students who have opted for more than 2 courses
SELECT s.roll_no, s.name, COUNT(*) AS courses_count
FROM student s 
JOIN studentcourse sc ON s.roll_no = sc.roll_no 
GROUP BY s.roll_no, s.name 
HAVING courses_count > 2;
-- Result:
-- +---------+-------+---------------+
-- | roll_no | name  | courses_count |
-- +---------+-------+---------------+
-- |     102 | Bob   |             3 |
-- |     104 | David |             4 |
-- |     105 | Eva   |             5 |
-- +---------+-------+---------------+

-- Query (d): List the details (name, fee, and duration) of:
-- • the course that has been opted by the maximum number of students, and
-- • the course that has been opted by the least number of students

-- Course with maximum students
SELECT c.name, c.fees, c.duration 
FROM course c 
JOIN studentcourse sc ON c.course_id = sc.course_id 
GROUP BY c.course_id 
ORDER BY COUNT(sc.roll_no) DESC 
LIMIT 1;

-- Course with minimum students
SELECT c.name, c.fees, c.duration 
FROM course c 
JOIN studentcourse sc ON c.course_id = sc.course_id 
GROUP BY c.course_id 
ORDER BY COUNT(sc.roll_no) ASC 
LIMIT 1;
-- Results:
-- Maximum:
-- +------+-------+----------+
-- | name | fees  | duration |
-- +------+-------+----------+
-- | BCA  | 90000 | 3 years  |
-- +------+-------+----------+
-- 
-- Minimum:
-- +------+-------+----------+
-- | name | fees  | duration |
-- +------+-------+----------+
-- | B.Sc | 80000 | 3 years  |
-- +------+-------+----------+

-- Query (e): List the details of the student(s) who have opted every course
SELECT s.name, s.roll_no
FROM student s 
JOIN studentcourse sc ON s.roll_no = sc.roll_no 
GROUP BY s.roll_no, s.name 
HAVING COUNT(sc.course_id) = (SELECT COUNT(*) FROM course);
-- Result:
-- +------+---------+
-- | name | roll_no |
-- +------+---------+
-- | Eva  |     105 |
-- +------+---------+

DROP DATABASE student;

