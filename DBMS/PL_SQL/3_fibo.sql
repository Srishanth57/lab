DROP PROCEDURE IF EXISTS fibonacci;

DELIMITER $$

CREATE PROCEDURE fibonacci(IN num INT)
BEGIN
    DECLARE i INT DEFAULT 0;
    DECLARE a INT DEFAULT 0;
    DECLARE b INT DEFAULT 1;
    DECLARE temp INT;

    CREATE TABLE IF NOT EXISTS fib_seq (fib_num INT);
    TRUNCATE TABLE fib_seq;

    WHILE i < num DO
        INSERT INTO fib_seq VALUES (a);
        SET temp = a + b;
        SET a = b;
        SET b = temp;
        SET i = i + 1;
    END WHILE;

    SELECT * FROM fib_seq;
    DROP TABLE fib_seq;
END $$

DELIMITER ;

