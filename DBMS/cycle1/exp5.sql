-- ========================================================================
-- EXPERIMENT 5: Banking System Management
-- ========================================================================

-- Create the following tables:
-- • Branch (branch_id, branch_name, branch_city)
-- • Customer (customer_id, customer_name, customer_city)
-- • Savings (customer_id, branch_id, saving_accno, balance)
-- • Loan (customer_id, branch_id, loan_accno, balance)

CREATE DATABASE student;
USE student;

-- =================================================================
-- TABLE DEFINITIONS
-- =================================================================

-- Create branch table
CREATE TABLE branch (
    branch_id   INT PRIMARY KEY,
    branch_name VARCHAR(20),
    branch_city VARCHAR(20)
);

-- Create customer table
CREATE TABLE customer (
    customer_id   INT PRIMARY KEY,
    customer_name VARCHAR(20),
    customer_city VARCHAR(20)
);

-- Create savings table
CREATE TABLE savings (
    customer_id  INT,
    branch_id    INT,
    saving_accno BIGINT,
    balance      BIGINT,
    FOREIGN KEY (customer_id) REFERENCES customer(customer_id)
);

-- Create loan table
CREATE TABLE loan (
    customer_id INT,
    branch_id   INT,
    loan_accno  BIGINT,
    balance     BIGINT,
    FOREIGN KEY (customer_id) REFERENCES customer(customer_id)
);

-- =================================================================
-- DATA INSERTION
-- =================================================================

-- Insert sample data into branch table
INSERT INTO branch (branch_id, branch_name, branch_city) VALUES
    (1, 'Central', 'New York'),
    (2, 'Westside', 'Los Angeles'),
    (3, 'Downtown', 'Chicago'),
    (4, 'Uptown', 'Houston'),
    (5, 'Midtown', 'Phoenix');

-- Insert sample data into customer table
INSERT INTO customer (customer_id, customer_name, customer_city) VALUES
    (101, 'Alice Smith', 'New York'),
    (102, 'Bob Johnson', 'Los Angeles'),
    (103, 'Charlie Lee', 'Chicago'),
    (104, 'Diana Evans', 'Houston'),
    (105, 'Evan Brown', 'Phoenix'),
    (106, 'Fiona White', 'New York'),
    (107, 'George Black', 'Chicago'),
    (108, 'Random', 'India'),
    (109, 'Test Customer', 'Boston');

-- Insert sample data into savings table
INSERT INTO savings (customer_id, branch_id, saving_accno, balance) VALUES
    (101, 1, 100000001, 5000),
    (102, 2, 100000002, 7500),
    (103, 3, 100000003, 10000),
    (104, 4, 100000004, 2000),
    (105, 5, 100000005, 15000),
    (106, 1, 100000006, 8000),
    (107, 3, 100000007, 12000),
    (108, NULL, NULL, NULL),
    (101, 3, 100000005, 10000);

-- Insert sample data into loan table
INSERT INTO loan (customer_id, branch_id, loan_accno, balance) VALUES
    (101, 1, 200000001, 25000),
    (102, 2, 200000002, 30000),
    (103, 3, 200000003, 10000),
    (104, 4, 200000004, 5000),
    (105, 5, 200000005, 15000),
    (106, 1, 200000006, 7000),
    (107, 3, NULL, NULL),
    (108, 1, 200000008, 10000),
    (109, 1, 300000001, 15000),  
    (109, 2, 300000002, 20000),  
    (109, 3, 300000003, 10000);  

-- =================================================================
-- QUERIES
-- =================================================================

-- Query (a): List the details of customers who live in the same city where they have an account.
SELECT
    c.customer_id,
    c.customer_name,
    c.customer_city
FROM
    customer c
JOIN
    savings s ON c.customer_id = s.customer_id
JOIN
    branch b ON s.branch_id = b.branch_id
WHERE
    c.customer_city = b.branch_city;

-- Result:
/*
+-------------+---------------+---------------+
| customer_id | customer_name | customer_city |
+-------------+---------------+---------------+
|         101 | Alice Smith   | New York      |
|         102 | Bob Johnson   | Los Angeles   |
|         103 | Charlie Lee   | Chicago       |
|         104 | Diana Evans   | Houston       |
|         105 | Evan Brown    | Phoenix       |
|         106 | Fiona White   | New York      |
|         107 | George Black  | Chicago       |
+-------------+---------------+---------------+
*/

-- Query (b): List the customers who have an account in a given branch city.
SELECT DISTINCT
    c.*
FROM
    customer c
JOIN (
    SELECT customer_id FROM savings s JOIN branch b ON s.branch_id = b.branch_id WHERE b.branch_city = 'New York'
    UNION
    SELECT customer_id FROM loan l JOIN branch b ON l.branch_id = b.branch_id WHERE b.branch_city = 'New York'
) AS accounts ON c.customer_id = accounts.customer_id;

-- Result:
/*
+-------------+---------------+---------------+
| customer_id | customer_name | customer_city |
+-------------+---------------+---------------+
|         101 | Alice Smith   | New York      |
|         106 | Fiona White   | New York      |
|         108 | Random        | India         |
+-------------+---------------+---------------+
*/

-- Query (c): List the customers who have accounts in more than one branch.
SELECT
    c.customer_id,
    c.customer_name,
    c.customer_city
FROM
    customer c
WHERE
    c.customer_id IN (
        SELECT
            customer_id
        FROM (
            SELECT customer_id, branch_id FROM savings WHERE branch_id IS NOT NULL
            UNION
            SELECT customer_id, branch_id FROM loan WHERE branch_id IS NOT NULL
        ) AS all_accounts
        GROUP BY
            customer_id
        HAVING
            COUNT(DISTINCT branch_id) > 1
    );

-- Result:
/*
+-------------+---------------+---------------+
| customer_id | customer_name | customer_city |
+-------------+---------------+---------------+
|         101 | Alice Smith   | New York      |
|         109 | Test Customer | Boston        |
+-------------+---------------+---------------+
*/

-- Query (d-i): List the details of customers who do not have a savings account but have a loan.
SELECT
    c.customer_id,
    c.customer_name,
    c.customer_city
FROM
    customer c
INNER JOIN
    loan l ON c.customer_id = l.customer_id
LEFT JOIN
    savings s ON c.customer_id = s.customer_id
WHERE
    s.customer_id IS NULL;

-- Result:
/*
+-------------+---------------+---------------+
| customer_id | customer_name | customer_city |
+-------------+---------------+---------------+
|         109 | Test Customer | Boston        |
+-------------+---------------+---------------+
*/

-- Query (d-ii): List the details of customers who do not have a loan but have a savings account.
SELECT
    c.customer_id,
    c.customer_name,
    c.customer_city
FROM
    customer c
JOIN
    savings s ON c.customer_id = s.customer_id
LEFT JOIN
    loan l ON c.customer_id = l.customer_id
WHERE
    l.customer_id IS NULL AND s.branch_id IS NOT NULL;

-- Result:
/*
-- Empty set
*/

-- Query (d-iii): List the details of customers who have both a loan and a savings account.
SELECT DISTINCT
    c.customer_id,
    c.customer_name,
    c.customer_city
FROM
    customer c
JOIN
    savings s ON c.customer_id = s.customer_id
JOIN
    loan l ON c.customer_id = l.customer_id
WHERE
    s.branch_id IS NOT NULL AND l.loan_accno IS NOT NULL;

-- Result:
/*
+-------------+---------------+---------------+
| customer_id | customer_name | customer_city |
+-------------+---------------+---------------+
|         101 | Alice Smith   | New York      |
|         102 | Bob Johnson   | Los Angeles   |
|         103 | Charlie Lee   | Chicago       |
|         104 | Diana Evans   | Houston       |
|         105 | Evan Brown    | Phoenix       |
|         106 | Fiona White   | New York      |
+-------------+---------------+---------------+
*/

-- Query (e): List the names of customers who have no savings account at all but have loans in more than two branches.
SELECT c.customer_name
FROM customer c
WHERE c.customer_id NOT IN (
    SELECT DISTINCT customer_id 
    FROM savings 
    WHERE customer_id IS NOT NULL 
      AND branch_id IS NOT NULL
)
AND c.customer_id IN (
    SELECT customer_id
    FROM loan
    WHERE branch_id IS NOT NULL
    GROUP BY customer_id
    HAVING COUNT(DISTINCT branch_id) > 2
);

-- Result:
/*
+---------------+
| customer_name |
+---------------+
| Test Customer |
+---------------+
*/

-- Query (f-i): For each branch, produce a list showing the total number of customers.
SELECT 
    b.* , 
    COUNT(allcustomers.customer_id) AS total_customers 
FROM 
    branch b 
LEFT JOIN (
    SELECT branch_id , customer_id FROM savings s WHERE branch_id IS NOT NULL 
    UNION 
    SELECT branch_id ,customer_id FROM loan l WHERE branch_id IS NOT NULL 
) AS allcustomers ON allcustomers.branch_id = b.branch_id 
GROUP BY 
    b.branch_id;
-- Result:
/*
+-----------+-------------+-------------+-----------------+
| branch_id | branch_name | branch_city | total_customers |
+-----------+-------------+-------------+-----------------+
|         1 | Central     | New York    |               5 |
|         2 | Westside    | Los Angeles |               3 |
|         3 | Downtown    | Chicago     |               5 |
|         4 | Uptown      | Houston     |               1 |
|         5 | Midtown     | Phoenix     |               1 |
+-----------+-------------+-------------+-----------------+
*/

-- Query (f-ii): For each branch, produce a list showing the total number of customers with only a loan.
SELECT b.*, COUNT(l.customer_id) AS customers_with_only_loan
FROM branch b
LEFT JOIN loan l ON b.branch_id = l.branch_id
WHERE l.customer_id NOT IN (SELECT customer_id FROM savings s WHERE s.branch_id = b.branch_id)
GROUP BY b.branch_id, b.branch_name, b.branch_city;

-- Result:
/*
+-----------+-------------+-------------+--------------------------+
| branch_id | branch_name | branch_city | customers_with_only_loan |
+-----------+-------------+-------------+--------------------------+
|         1 | Central     | New York    |                        2 |
|         2 | Westside    | Los Angeles |                        1 |
|         3 | Downtown    | Chicago     |                        1 |
|         4 | Uptown      | Houston     |                        0 |
|         5 | Midtown     | Phoenix     |                        0 |
+-----------+-------------+-------------+--------------------------+
*/

-- Query (f-iii): For each branch, produce a list showing the total number of customers with only a savings account.
SELECT b.*, COUNT(s.customer_id) AS customers_with_only_savings
FROM branch b
LEFT JOIN savings s ON b.branch_id = s.branch_id
WHERE s.customer_id NOT IN (SELECT customer_id FROM loan l WHERE l.branch_id = b.branch_id)
GROUP BY b.branch_id, b.branch_name, b.branch_city;
-- Result:
/*
-- Empty set
*/

-- Query (f-iv): For each branch, produce a list showing the total number of customers with both loan and savings accounts.
SELECT 
    b.*, 
    COUNT(DISTINCT both_acc_customers.customer_id ) AS customer_count  
FROM 
    branch b 
INNER JOIN ( 
    SELECT DISTINCT(s.customer_id) , s.branch_id 
    FROM savings s 
    JOIN loan l ON s.customer_id = l.customer_id 
    WHERE s.branch_id IS NOT NULL 
) AS both_acc_customers ON both_acc_customers.branch_id = b.branch_id 
GROUP BY 
    b.branch_id;
-- Result:
/*
+-----------+-------------+-------------+----------------+
| branch_id | branch_name | branch_city | customer_count |
+-----------+-------------+-------------+----------------+
|         1 | Central     | New York    |              2 |
|         2 | Westside    | Los Angeles |              1 |
|         3 | Downtown    | Chicago     |              3 |
|         4 | Uptown      | Houston     |              1 |
|         5 | Midtown     | Phoenix     |              1 |
+-----------+-------------+-------------+----------------+
*/

-- Query (g): Find the details of the branch that has issued the maximum total amount of loan.
SELECT 
    b.*,    
    SUM(l.balance) AS total_amount_loan     
FROM 
    branch b      
INNER JOIN 
    loan l ON l.branch_id = b.branch_id      
WHERE 
    l.balance IS NOT NULL      
GROUP BY 
    b.branch_id 
ORDER BY 
    total_amount_loan DESC 
LIMIT 1;

-- Result:
/*
+-----------+-------------+-------------+-------------------+
| branch_id | branch_name | branch_city | total_amount_loan |
+-----------+-------------+-------------+-------------------+
|         1 | Central     | New York    |             57000 |
+-----------+-------------+-------------+-------------------+
*/

-- Query (h): Find the details of the branch that has not issued any loan at all.
SELECT 
    b.branch_id, 
    b.branch_name, 
    b.branch_city 
FROM 
    branch b 
WHERE 
    b.branch_id NOT IN (SELECT DISTINCT branch_id FROM loan WHERE branch_id IS NOT NULL);
-- Result:
/*
-- Empty set
*/

-- Query (i): For each customer, produce a list showing the total savings balance and loan balance for all branches.
SELECT       
    c.customer_id, 
    c.customer_name,      
    SUM(l.balance) AS loan_balance,      
    SUM(s.balance) AS savings_balance 
FROM 
    customer c 
LEFT JOIN 
    loan l ON l.customer_id = c.customer_id 
LEFT JOIN 
    savings s ON s.customer_id = c.customer_id 
GROUP BY 
    c.customer_id, c.customer_name;

-- Result:
/*
+-------------+---------------+--------------+-----------------+
| customer_id | customer_name | loan_balance | savings_balance |
+-------------+---------------+--------------+-----------------+
|         101 | Alice Smith   |        25000 |           15000 |
|         102 | Bob Johnson   |        30000 |            7500 |
|         103 | Charlie Lee   |        10000 |           10000 |
|         104 | Diana Evans   |         5000 |            2000 |
|         105 | Evan Brown    |        15000 |           15000 |
|         106 | Fiona White   |         7000 |            8000 |
|         107 | George Black  |         NULL |           12000 |
|         108 | Random        |        10000 |            NULL |
|         109 | Test Customer |        45000 |            NULL |
+-------------+---------------+--------------+-----------------+
*/

DROP DATABASE student;
