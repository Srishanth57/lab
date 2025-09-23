DROP PROCEDURE IF EXISTS palindrome;

DELIMITER $$

CREATE PROCEDURE palindrome(IN str VARCHAR(20))
BEGIN
    DECLARE len INT DEFAULT 0;
    DECLARE i INT DEFAULT 1;
    DECLARE is_palindrome INT DEFAULT 1;

    SET len = LENGTH(str);

    check_loop: WHILE i < len DIV 2 DO
        -- Compare characters from both ends
        IF SUBSTRING(str, i, 1) != SUBSTRING(str, len - i + 1, 1) THEN
            SET is_palindrome = 0;
            LEAVE check_loop;
        END IF;
        SET i = i + 1;
    END WHILE check_loop;

    IF is_palindrome = 1 THEN
        SELECT CONCAT(str, ' is a palindrome.') AS result;
    ELSE
        SELECT CONCAT(str, ' is not a palindrome.') AS result;
    END IF;
END $$

DELIMITER ;

