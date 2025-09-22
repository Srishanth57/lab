CREATE DATABASE IF NOT EXISTS student;
USE student;

-- Employee Table
CREATE TABLE employee (
    employee_id     INT PRIMARY KEY AUTO_INCREMENT,
    name            VARCHAR(50) NOT NULL,
    address         VARCHAR(100),
    aadhar_number   BIGINT UNIQUE,
    mobile_number   BIGINT,
    email_id        VARCHAR(50),
    joining_date    DATE,
    salary          DECIMAL(10, 2)
);

-- Residents Table
CREATE TABLE residents (
    resident_id     INT PRIMARY KEY AUTO_INCREMENT,
    name            VARCHAR(50),
    address         VARCHAR(100),
    aadhar_number   BIGINT UNIQUE,
    gender          ENUM('Male', 'Female', 'Other'),
    age             INT,
    mobile_number   BIGINT,
    email_id        VARCHAR(50)
);

-- Companions Table
CREATE TABLE companions (
    companions_id   INT PRIMARY KEY AUTO_INCREMENT,
    resident_id     INT,
    name            VARCHAR(50),
    gender          ENUM('Female', 'Male', 'Other'),
    mobile_number   BIGINT,
    FOREIGN KEY (resident_id) REFERENCES residents(resident_id)
);

-- Rooms Table
CREATE TABLE rooms (
    room_id         INT PRIMARY KEY AUTO_INCREMENT,
    room_type       ENUM('A/C', 'NON A/C'),
    capacity        ENUM('Single Bed', 'Double Bed')
);

-- Bookings Table
CREATE TABLE bookings (
    booking_id      INT PRIMARY KEY AUTO_INCREMENT,
    resident_id     INT,
    room_id         INT,
    booking_date    DATE,
    FOREIGN KEY (resident_id) REFERENCES residents(resident_id),
    FOREIGN KEY (room_id) REFERENCES rooms(room_id)
);

-- Food Items Table
CREATE TABLE food_items (
    food_id         INT PRIMARY KEY AUTO_INCREMENT,
    food_name       VARCHAR(50),
    type            ENUM('Vegetarian', 'Non-Vegetarian'),
    price           DECIMAL(8, 2)
);

-- Food Orders Table
CREATE TABLE food_orders (
    order_id        INT PRIMARY KEY AUTO_INCREMENT,
    room_id         INT,
    resident_id     INT,
    food_id         INT,
    FOREIGN KEY (room_id) REFERENCES rooms(room_id),
    FOREIGN KEY (resident_id) REFERENCES residents(resident_id),
    FOREIGN KEY (food_id) REFERENCES food_items(food_id)
);

-- Insert Employee Data
INSERT INTO employee (name, address, aadhar_number, mobile_number, email_id, joining_date, salary) VALUES
    ('Rajesh Kumar', '123 MG Road, Kochi', 123456789012, 9876543210, 'rajesh@resort.com', '2022-01-15', 25000.00),
    ('Priya Singh', '456 Beach Road, Kovalam', 234567890123, 8765432109, 'priya@resort.com', '2022-03-20', 22000.00),
    ('Amit Sharma', '789 Hill View, Munnar', 345678901234, 7654321098, 'amit@resort.com', '2021-11-10', 30000.00),
    ('Deepika Nair', '321 Lake Side, Alleppey', 456789012345, 6543210987, 'deepika@resort.com', '2023-01-05', 28000.00),
    ('Rahul Menon', '654 Forest Road, Wayanad', 567890123456, 5432109876, 'rahul@resort.com', '2022-08-12', 24000.00),
    ('Sneha Pillai', '987 Temple Street, Thrissur', 678901234567, 4321098765, 'sneha@resort.com', '2023-02-18', 26000.00),
    ('Vikram Reddy', '147 Metro Station, Bangalore', 789012345678, 3210987654, 'vikram@resort.com', '2021-09-25', 32000.00),
    ('Kavya Menon', '258 Airport Road, Calicut', 890123456789, 2109876543, 'kavya@resort.com', '2022-07-30', 23000.00),
    ('Arjun Nair', '369 Bus Stand, Trivandrum', 901234567890, 1098765432, 'arjun@resort.com', '2023-04-14', 27000.00),
    ('Meera Krishna', '741 Railway Station, Ernakulam', 012345678901, 9087654321, 'meera@resort.com', '2022-12-08', 25500.00),
    ('Suresh Babu', '852 Market Square, Kottayam', 123450987654, 8976543210, 'suresh@resort.com', '2021-06-22', 29000.00),
    ('Anita Varma', '963 College Road, Palakkad', 234561098765, 7865432109, 'anita@resort.com', '2023-03-11', 24500.00),
    ('Ravi Thampi', '159 Hospital Junction, Kollam', 345672109876, 6754321098, 'ravi@resort.com', '2022-10-05', 26500.00),
    ('Lakshmi Devi', '357 School Lane, Kannur', 456783210987, 5643210987, 'lakshmi@resort.com', '2021-12-18', 31000.00),
    ('Mohan Das', '468 Park Avenue, Kasaragod', 567894321098, 4532109876, 'mohan@resort.com', '2023-01-28', 23500.00),
    ('Geetha Kumari', '579 Church Street, Idukki', 678905432109, 3421098765, 'geetha@resort.com', '2022-05-16', 27500.00),
    ('Ramesh Pillai', '680 Stadium Road, Malappuram', 789016543210, 2310987654, 'ramesh@resort.com', '2021-08-09', 28500.00),
    ('Suja Mol', '791 Tower Junction, Pathanamthitta', 890127654321, 1209876543, 'suja@resort.com', '2023-06-21', 22500.00),
    ('Krishna Menon', '802 Bridge Road, Alappuzha', 901238765432, 9198765432, 'krishna@resort.com', '2022-04-03', 30500.00),
    ('Radha Krishnan', '913 Garden View, Thiruvananthapuram', 012349876543, 8187654321, 'radha@resort.com', '2021-10-27', 33000.00);

-- Insert Residents Data
INSERT INTO residents (name, address, aadhar_number, gender, age, mobile_number, email_id) VALUES
    ('Arjun Reddy', '12 Gandhi Street, Chennai', 111222333444, 'Male', 32, 9988776655, 'arjun@gmail.com'),
    ('Sneha Patel', '45 Park Avenue, Mumbai', 222333444555, 'Female', 28, 8877665544, 'sneha@yahoo.com'),
    ('Vikram Singh', '78 Mall Road, Delhi', 333444555666, 'Male', 35, 7766554433, 'vikram@outlook.com'),
    ('Kavya Krishnan', '23 Temple Street, Bangalore', 444555666777, 'Female', 30, 6655443322, 'kavya@gmail.com'),
    ('Ravi Kumar', '56 Beach Road, Goa', 555666777888, 'Male', 27, 5544332211, 'ravi@hotmail.com'),
    ('Meera Shah', '89 Hill Station, Pune', 666777888999, 'Female', 25, 4433221100, 'meera@gmail.com'),
    ('Rohit Sharma', '34 Metro Mall, Hyderabad', 777888999000, 'Male', 29, 3322110099, 'rohit@rediff.com'),
    ('Priyanka Das', '67 Lake View, Kolkata', 888999000111, 'Female', 31, 2211009988, 'priyanka@gmail.com'),
    ('Sachin Tendulkar', '90 Cricket Ground, Pune', 999000111222, 'Male', 45, 1100998877, 'sachin@sports.com'),
    ('Aishwarya Rai', '12 Film City, Mumbai', 000111222333, 'Female', 38, 9900887766, 'aishwarya@bollywood.com'),
    ('Rahul Dravid', '45 Stadium Road, Bangalore', 111222333445, 'Male', 42, 8899776655, 'rahul@cricket.com'),
    ('Deepika Padukone', '78 Studio Lane, Mumbai', 222333444556, 'Female', 34, 7788665544, 'deepika@films.com'),
    ('Virat Kohli', '23 Ground Floor, Delhi', 333444555667, 'Male', 33, 6677554433, 'virat@cricket.in'),
    ('Anushka Sharma', '56 Production House, Mumbai', 444555666778, 'Female', 32, 5566443322, 'anushka@movies.com'),
    ('MS Dhoni', '89 Captain Colony, Ranchi', 555666777889, 'Male', 40, 4455332211, 'dhoni@cricket.org'),
    ('Kareena Kapoor', '34 Star Street, Mumbai', 666777888990, 'Female', 41, 3344221100, 'kareena@films.in'),
    ('Akshay Kumar', '67 Action Avenue, Mumbai', 777888999001, 'Male', 54, 2233110099, 'akshay@action.com'),
    ('Katrina Kaif', '90 Dance Studio, Mumbai', 888999000112, 'Female', 38, 1122009988, 'katrina@dance.com'),
    ('Salman Khan', '12 Tiger House, Mumbai', 999000111223, 'Male', 56, 9911008877, 'salman@being.org'),
    ('Alia Bhatt', '45 Young Star, Mumbai', 000111222334, 'Female', 29, 8800997766, 'alia@newgen.com');

-- Insert Rooms Data
INSERT INTO rooms (room_type, capacity) VALUES
    ('A/C', 'Single Bed'), ('A/C', 'Double Bed'), ('A/C', 'Double Bed'), ('NON A/C', 'Single Bed'), ('NON A/C', 'Double Bed'),
    ('A/C', 'Single Bed'), ('A/C', 'Double Bed'), ('A/C', 'Double Bed'), ('NON A/C', 'Single Bed'), ('NON A/C', 'Double Bed'),
    ('A/C', 'Single Bed'), ('A/C', 'Single Bed'), ('A/C', 'Double Bed'), ('A/C', 'Double Bed'), ('NON A/C', 'Single Bed'),
    ('NON A/C', 'Single Bed'), ('NON A/C', 'Double Bed'), ('NON A/C', 'Double Bed'), ('A/C', 'Double Bed'), ('A/C', 'Single Bed');

-- Insert Bookings Data
INSERT INTO bookings (resident_id, room_id, booking_date) VALUES
    (1, 1, '2024-01-15'), (1, 2, '2024-06-10'), (2, 3, '2024-02-20'), (3, 6, '2024-03-10'), (3, 7, '2024-07-20'),
    (4, 8, '2024-04-05'), (5, 4, '2024-05-12'), (6, 5, '2024-08-15'), (7, 9, '2024-01-25'), (8, 10, '2024-09-10'),
    (9, 11, '2024-02-14'), (10, 12, '2024-03-22'), (11, 13, '2024-04-18'), (12, 14, '2024-05-30'), (13, 15, '2024-06-25'),
    (14, 16, '2024-07-12'), (15, 17, '2024-08-08'), (16, 18, '2024-09-15'), (17, 19, '2024-10-05'), (18, 20, '2024-11-20');

-- Insert Companions Data
INSERT INTO companions (resident_id, name, gender, mobile_number) VALUES
    (1, 'Sita Reddy', 'Female', 9988776656), (1, 'Ram Reddy', 'Male', 9988776657), (1, 'Lakshman Reddy', 'Male', 9988776658), (1, 'Bharath Reddy', 'Male', 9988776659),
    (2, 'Raj Patel', 'Male', 8877665545), (2, 'Priya Patel', 'Female', 8877665546), (3, 'Sunita Singh', 'Female', 7766554434), (3, 'Anita Singh', 'Female', 7766554435),
    (3, 'Rohit Singh', 'Male', 7766554436), (4, 'Suresh Krishnan', 'Male', 6655443323), (4, 'Ramesh Krishnan', 'Male', 6655443324), (5, 'Geeta Kumar', 'Female', 5544332212),
    (6, 'Amit Shah', 'Male', 4433221101), (7, 'Neha Sharma', 'Female', 3322110090), (7, 'Karan Sharma', 'Male', 3322110091), (8, 'Sohan Das', 'Male', 2211009989),
    (9, 'Anjali Tendulkar', 'Female', 1100998878), (10, 'Abhishek Bachchan', 'Male', 9900887767), (11, 'Vijeta Dravid', 'Female', 8899776656), (12, 'Ranveer Singh', 'Male', 7788665545);

-- Insert Food Items Data
INSERT INTO food_items (food_name, type, price) VALUES
    ('Vegetable Biryani', 'Vegetarian', 250.00), ('Chicken Biryani', 'Non-Vegetarian', 350.00), ('Paneer Butter Masala', 'Vegetarian', 180.00), ('Fish Curry', 'Non-Vegetarian', 300.00),
    ('Dal Tadka', 'Vegetarian', 120.00), ('Mutton Curry', 'Non-Vegetarian', 400.00), ('Mixed Vegetable Curry', 'Vegetarian', 150.00), ('Chicken Tikka', 'Non-Vegetarian', 320.00),
    ('Curd Rice', 'Vegetarian', 80.00), ('Prawn Masala', 'Non-Vegetarian', 380.00), ('Palak Paneer', 'Vegetarian', 200.00), ('Butter Chicken', 'Non-Vegetarian', 360.00),
    ('Aloo Gobi', 'Vegetarian', 140.00), ('Lamb Curry', 'Non-Vegetarian', 420.00), ('Rajma Rice', 'Vegetarian', 160.00), ('Fish Fry', 'Non-Vegetarian', 280.00),
    ('Sambar Rice', 'Vegetarian', 100.00), ('Chicken Curry', 'Non-Vegetarian', 330.00), ('Jeera Rice', 'Vegetarian', 90.00), ('Egg Curry', 'Non-Vegetarian', 220.00);

-- Insert Food Orders Data
INSERT INTO food_orders (room_id, resident_id, food_id) VALUES
    (1, 1, 2), (1, 1, 4), (2, 1, 1), (3, 2, 2), (3, 2, 3), (6, 3, 1), (7, 3, 6), (8, 4, 2), (8, 4, 5), (4, 5, 1),
    (4, 5, 7), (5, 6, 8), (5, 6, 9), (9, 7, 10), (10, 8, 11), (11, 9, 12), (12, 10, 13), (13, 11, 14), (14, 12, 15), (15, 13, 16);

/*
Question 6(a): Print the details of the residents who have more than three companions in a single booking.
*/
SELECT r.resident_id, r.name, COUNT(DISTINCT c.companions_id) AS no_of_companions
FROM residents r
INNER JOIN companions c ON c.resident_id = r.resident_id
INNER JOIN bookings b ON b.resident_id = r.resident_id
GROUP BY r.resident_id
HAVING no_of_companions > 3;

/*
Result:
+-------------+-------------+------------------+
| resident_id | name        | no_of_companions |
+-------------+-------------+------------------+
|      1      | Arjun Reddy |        4         |
+-------------+-------------+------------------+
*/



/*
Question 6(b): Print the details of the residents along with the number of companions for bookings after '2024-05-01'.
*/
SELECT r.*, COUNT(DISTINCT c.companions_id) AS no_of_companions
FROM residents r
INNER JOIN companions c ON c.resident_id = r.resident_id
INNER JOIN bookings b ON b.resident_id = r.resident_id
WHERE b.booking_date > '2024-05-01'
GROUP BY r.resident_id;

/*
Result:
+-------------+------------------+---------------------------+---------------+--------+-----+---------------+--------------------+------------------+
| resident_id | name             | address                   | aadhar_number | gender | age | mobile_number | email_id           | no_of_companions |
+-------------+------------------+---------------------------+---------------+--------+-----+---------------+--------------------+------------------+
|      1      | Arjun Reddy      | 12 Gandhi Street, Chennai | 111222333444  | Male   | 32  | 9988776655    | arjun@gmail.com    |        4         |
|      3      | Vikram Singh     | 78 Mall Road, Delhi       | 333444555666  | Male   | 35  | 7766554433    | vikram@outlook.com|        3         |
|      5      | Ravi Kumar       | 56 Beach Road, Goa        | 555666777888  | Male   | 27  | 5544332211    | ravi@hotmail.com   |        1         |
|      6      | Meera Shah       | 89 Hill Station, Pune     | 666777888999  | Female | 25  | 4433221100    | meera@gmail.com    |        1         |
|      8      | Priyanka Das     | 67 Lake View, Kolkata     | 888999000111  | Female | 31  | 2211009988    | priyanka@gmail.com |        1         |
|     12      | Deepika Padukone | 78 Studio Lane, Mumbai    | 222333444556  | Female | 34  | 7788665544    | deepika@films.com  |        1         |
+-------------+------------------+---------------------------+---------------+--------+-----+---------------+--------------------+------------------+
*/



/*
Question 6(c): Print the details of the residents who reserved more than two AC rooms in at least two different bookings.
*/
SELECT DISTINCT r.*
FROM residents r
JOIN bookings b ON b.resident_id = r.resident_id
JOIN rooms rm ON rm.room_id = b.room_id
WHERE rm.room_type = 'A/C'
  AND r.resident_id IN (
    SELECT b2.resident_id
    FROM rooms rm2
    JOIN bookings b2 ON rm2.room_id = b2.room_id
    WHERE rm2.room_type = 'A/C'
    GROUP BY b2.resident_id
    HAVING COUNT(DISTINCT b2.booking_id) >= 2
       AND COUNT(*) > 2
  );

/*
Result:
Empty set (no residents matched)
*/



/*
Question 6(d): Print the details of the food item ordered by the maximum number of residents and the food item ordered by the minimum number of residents.
*/

/* Most ordered food item: */
SELECT fi.*, COUNT(DISTINCT fo.resident_id) AS resident_count
FROM food_items fi
INNER JOIN food_orders fo ON fo.food_id = fi.food_id
GROUP BY fi.food_id, fi.food_name, fi.type, fi.price
ORDER BY resident_count DESC
LIMIT 1;

/*
Result (maximum):
+---------+-------------------+------------+--------+----------------+
| food_id | food_name         | type       | price  | resident_count |
+---------+-------------------+------------+--------+----------------+
|    1    | Vegetable Biryani | Vegetarian | 250.00 |       3        |
+---------+-------------------+------------+--------+----------------+
*/

/* Least ordered food item: */
SELECT fi.*, COUNT(DISTINCT fo.resident_id) AS resident_count
FROM food_items fi
INNER JOIN food_orders fo ON fo.food_id = fi.food_id
GROUP BY fi.food_id, fi.food_name, fi.type, fi.price
ORDER BY resident_count ASC
LIMIT 1;

/*
Result (minimum):
+---------+-----------+----------------+--------+----------------+
| food_id | food_name | type           | price  | resident_count |
+---------+-----------+----------------+--------+----------------+
|   16    | Fish Fry  | Non-Vegetarian | 280.00 |       1        |
+---------+-----------+----------------+--------+----------------+
*/



/*
Question 6(e): Print the details of food items in non-decreasing order of preference in a specific period.
Preference = number of orders for item - (price / 1000)
*/
SELECT fi.*, COUNT(fo.order_id) AS total_orders, 
       (COUNT(fo.order_id) - (fi.price / 1000)) AS preference_score
FROM food_items fi
JOIN food_orders fo ON fo.food_id = fi.food_id
GROUP BY fo.order_id
ORDER BY preference_score DESC;

/*
Sample Result:
+---------+-----------------------+----------------+--------+--------------+------------------+
| food_id | food_name             | type           | price  | total_orders | preference_score |
+---------+-----------------------+----------------+--------+--------------+------------------+
|    9    | Curd Rice             | Vegetarian     |  80.00 |      1       |      0.92        |
|    5    | Dal Tadka             | Vegetarian     | 120.00 |      1       |      0.88        |
|   13    | Aloo Gobi             | Vegetarian     | 140.00 |      1       |      0.86        |
|   ...   | ...                   | ...            |  ...   |    ...       |      ...         |
+---------+-----------------------+----------------+--------+--------------+------------------+
*/




DROP DATABASE student;


