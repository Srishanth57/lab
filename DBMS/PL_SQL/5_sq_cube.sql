DROP PROCEDURE IF EXISTS sq_cube;

DELIMITER $$

CREATE PROCEDURE sq_cube(IN n INT)
BEGIN
    DECLARE i INT DEFAULT 1;
    DECLARE sqr INT;
    DECLARE cub INT;

    CREATE TEMPORARY TABLE square(num INT, square_value INT);
    CREATE TEMPORARY TABLE cubeval(num INT, cube_value INT);

    WHILE i <= n DO
        SET sqr = POW(i, 2);
        INSERT INTO square VALUES (i, sqr);
        SET cub = POW(i, 3);
        INSERT INTO cubeval VALUES (i, cub);
        SET i = i + 1;
    END WHILE;
	select 'Square values are given below' as message;
    SELECT * FROM square;
    select 'Cube values are given below' as message;
    SELECT * FROM cubeval;
    
    
    drop temporary table if exists square; 
    drop temporary table if exists cubeval; 
    

END $$
DELIMITER ;



/* 
call sq_cube(5);

+-------------------------------+
| message                       |
+-------------------------------+
| Square values are given below |
+-------------------------------+

+------+--------------+
| num  | square_value |
+------+--------------+
|    1 |            1 |
|    2 |            4 |
|    3 |            9 |
|    4 |           16 |
|    5 |           25 |
+------+--------------+

+-----------------------------+
| message                     |
+-----------------------------+
| Cube values are given below |
+-----------------------------+


+------+------------+
| num  | cube_value |
+------+------------+
|    1 |          1 |
|    2 |          8 |
|    3 |         27 |
|    4 |         64 |
|    5 |        125 |
+------+------------+


*/
