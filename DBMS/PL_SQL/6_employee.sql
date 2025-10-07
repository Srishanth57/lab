DROP PROCEDURE IF EXISTS calculate_pension;

DELIMITER $$

CREATE PROCEDURE calculate_pension()
BEGIN
    DECLARE finished INT DEFAULT FALSE;
    DECLARE emp_id INT;
    DECLARE emp_name VARCHAR(100);
    DECLARE join_date DATE;
    DECLARE leave_date DATE;
    DECLARE salary_amt DECIMAL(10,2);
    DECLARE service_years INT;
    DECLARE pension_amt DECIMAL(10,2);

    -- Cursor for relieved employees
    DECLARE emp_cursor CURSOR FOR
        SELECT empid, empname, joining_date, relieving_date, salary
        FROM employee
        WHERE relieving_date IS NOT NULL;

    -- Handler for end of cursor
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET finished = TRUE;

    -- Create temporary result table to store pension calculations
    CREATE TABLE pensionResult (
        employeeId INT PRIMARY KEY,
        employeeName VARCHAR(30),
        yearOfService INT,
        pensionAmount DECIMAL(10, 2)
    );

    OPEN emp_cursor;

    fetch_loop: LOOP
        FETCH emp_cursor INTO emp_id, emp_name, join_date, leave_date, salary_amt;
        IF finished THEN
            LEAVE fetch_loop;
        END IF;

        -- Calculate years of service
        SET service_years = TIMESTAMPDIFF(YEAR, join_date, leave_date);

        -- Calculate pension amount
        SET pension_amt = (service_years * salary_amt) / 100;

        -- Insert results into pensionResult table
        INSERT INTO pensionResult VALUES (emp_id, emp_name, service_years, pension_amt);
    END LOOP;

    CLOSE emp_cursor;

    -- Display the pension results
    SELECT * FROM pensionResult;

    -- Clean up by dropping the result table
    DROP TABLE pensionResult;
END $$

DELIMITER ;

