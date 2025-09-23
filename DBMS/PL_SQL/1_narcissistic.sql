DROP PROCEDURE IF EXISTS narcissistic;

DELIMITER $$

CREATE PROCEDURE narcissistic(IN num INT)
BEGIN
    DECLARE temp INT DEFAULT 0;
    DECLARE initvalue INT DEFAULT 0;
    DECLARE value INT DEFAULT 0;
    DECLARE result INT DEFAULT 0;
    DECLARE length INT DEFAULT 0;

    SET initvalue = num;
    SET length = LENGTH(CAST(num AS CHAR));
    SET temp = num;

    WHILE temp > 0 DO
        SET value = temp % 10;
        SET result = result + POW(value, length);
        SET temp = temp DIV 10;
    END WHILE;

    IF initvalue = result THEN
        SELECT CONCAT('The number ', initvalue, ' is narcissistic') AS Output;
    ELSE
        SELECT CONCAT('The number ', initvalue, ' is not narcissistic') AS Output;
    END IF;
END $$

DELIMITER ;

