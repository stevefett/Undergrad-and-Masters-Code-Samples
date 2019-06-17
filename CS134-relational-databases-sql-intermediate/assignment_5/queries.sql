SELECT bus_name
FROM CUSTOMER, HIRE
WHERE CUSTOMER.cust_id = HIRE.cust_id AND hours >= 10 AND zip = 95819;


SELECT PAINT_COLOR.mfg_id, PAINT_COLOR.color_id, PAINT_COLOR.name 
FROM PAINT_COLOR 
WHERE PAINT_COLOR.color_id NOT IN (SELECT color_id FROM PAINTED);


SELECT CUSTOMER.cust_id, CUSTOMER.first, CUSTOMER.last
FROM CUSTOMER, PAINTED, ROOM, PAINT_COLOR
WHERE CUSTOMER.cust_id = ROOM.cust_id
AND CUSTOMER.cust_id = PAINTED.cust_id
AND PAINTED.rm_name = ROOM.name
AND PAINT_COLOR.color_id = PAINTED.color_id
AND PAINT_COLOR.name = 'Blushing Pink'
AND ROOM.name = 'Bedroom 1';


SELECT CUSTOMER.cust_id, CUSTOMER.first, CUSTOMER.last
FROM CUSTOMER, PAINTED, ROOM, PAINT_COLOR
WHERE CUSTOMER.cust_id = ROOM.cust_id
AND CUSTOMER.cust_id = PAINTED.cust_id
AND PAINTED.rm_name = ROOM.name
AND PAINT_COLOR.color_id = PAINTED.color_id
AND PAINT_COLOR.name = 'Blushing Pink'
AND ROOM.name <> 'Bedroom 1';



SELECT CONTRACTOR.bus_name, CONTRACTOR.discount, SUM(HIRE.hours) AS TotalHours
FROM CONTRACTOR, HIRE
WHERE CONTRACTOR.bus_name = HIRE.bus_name
GROUP BY CONTRACTOR.bus_name
ORDER BY TotalHours DESC;


Find the customers with two or more rooms painted. For each customer, list their first and last name and the number of rooms painted, and have the output call this column ‘Room Count’. Be sure to populate the database so that there are at least two different customers returned by this query.

SELECT CUSTOMER.first, CUSTOMER.last, COUNT(PAINTED.cust_id) AS 'Room Count'
FROM CUSTOMER, PAINTED
WHERE CUSTOMER.cust_id = PAINTED.cust_id
GROUP BY CUSTOMER.cust_id
HAVING COUNT(*) >= 2;










