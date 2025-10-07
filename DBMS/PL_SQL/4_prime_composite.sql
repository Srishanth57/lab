DROP PROCEDURE IF EXISTS primeComposite;

DELIMITER $$

CREATE PROCEDURE primeComposite(IN n INT)
BEGIN
    DECLARE count_prime INT DEFAULT 0;
    DECLARE count_composite INT DEFAULT 0;
    DECLARE number INT DEFAULT 2;
    DECLARE divisor INT;
    DECLARE is_prime BOOLEAN;

    CREATE TEMPORARY TABLE prime_numbers (
        id INT PRIMARY KEY,
        value INT
    );

    CREATE TEMPORARY TABLE composite_numbers (
        id INT PRIMARY KEY,
        value INT
    );

    WHILE count_prime < n OR count_composite < n DO
        SET is_prime = TRUE;
        SET divisor = 2;

       inner_loop:  WHILE divisor < number DO
            IF number % divisor = 0 THEN
                SET is_prime = FALSE;
                LEAVE inner_loop;
            END IF;
            SET divisor = divisor + 1;
        END WHILE inner_loop;

        IF is_prime AND count_prime < n THEN
            INSERT INTO prime_numbers VALUES (count_prime + 1, number);
            SET count_prime = count_prime + 1;
        ELSEIF NOT is_prime AND count_composite < n THEN
            INSERT INTO composite_numbers VALUES (count_composite + 1, number);
            SET count_composite = count_composite + 1;
        END IF;

        SET number = number + 1;
    END WHILE;

    SELECT 'The prime numbers are given below' AS message;
    SELECT * FROM prime_numbers;

    SELECT 'The composite numbers are given below' AS message;
    SELECT * FROM composite_numbers;

    DROP TEMPORARY TABLE prime_numbers;
    DROP TEMPORARY TABLE composite_numbers;
END $$

DELIMITER ;

