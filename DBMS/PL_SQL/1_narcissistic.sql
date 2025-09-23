DROP PROCEDURE IF EXISTS narcissistic;

DELIMITER $$

CREATE PROCEDURE narcissistic(IN num INT)
BEGIN
    DECLARE remainder INT DEFAULT 0;
    DECLARE temp INT DEFAULT 0;
    DECLARE initvalue INT DEFAULT 0;
    DECLARE value INT DEFAULT 0;
    DECLARE result INT DEFAULT 0;
    DECLARE length INT DEFAULT 0;

    SET temp = num;
    SET initvalue = num;

    WHILE temp > 0 DO
        SET temp = temp DIV 10;
        SET length = length + 1;
    END WHILE;

    WHILE num > 0 DO
        SET value = num % 10;
        SET result = result + POW(value, length);
        SET num = num DIV 10;
    END WHILE;

    IF initvalue = result THEN
        SELECT CONCAT('The number ', initvalue, ' is narcissistic') AS Output;
    ELSE
        SELECT CONCAT('The number ', initvalue, ' is not narcissistic') AS Output;
    END IF;
END $$

DELIMITER ;

