CREATE TABLE employee (
    empid INT PRIMARY KEY,
    empname VARCHAR(100),
    joining_date DATE,
    relieving_date DATE,
    salary DECIMAL(10,2)
);
INSERT INTO employee (empid, empname, joining_date, relieving_date, salary) VALUES
(1, 'Alice Johnson', '2010-03-15', '2020-03-14', 50000),
(2, 'Bob Smith', '2012-07-01', '2018-06-30', 60000),
(3, 'Carol Williams', '2015-01-10', '2022-01-09', 55000),
(4, 'David Brown', '2008-11-25', '2016-11-24', 72000),
(5, 'Eva Davis', '2011-05-30', '2019-05-29', 48000),
(6, 'Frank Miller', '2013-09-15', NULL, 65000),
(7, 'Grace Wilson', '2014-12-01', '2020-11-30', 59000),
(8, 'Henry Moore', '2009-06-20', '2015-06-19', 71000),
(9, 'Isabel Taylor', '2016-02-15', NULL, 53000),
(10, 'Jack Anderson', '2010-08-01', '2021-07-31', 67000),
(11, 'Karen Thomas', '2007-04-10', '2013-04-09', 58000),
(12, 'Larry Jackson', '2012-10-05', '2019-10-04', 56000),
(13, 'Mona White', '2013-03-25', NULL, 60000),
(14, 'Nathan Harris', '2006-06-12', '2016-06-11', 69000),
(15, 'Olivia Martin', '2011-01-15', '2018-01-14', 54000),
(16, 'Paul Thompson', '2014-05-20', NULL, 62000),
(17, 'Quinn Garcia', '2009-09-09', '2017-09-08', 70000),
(18, 'Rachel Martinez', '2015-07-30', NULL, 58000),
(19, 'Steve Robinson', '2008-02-28', '2014-02-27', 66000),
(20, 'Tina Clark', '2010-12-20', '2019-12-19', 63000);

