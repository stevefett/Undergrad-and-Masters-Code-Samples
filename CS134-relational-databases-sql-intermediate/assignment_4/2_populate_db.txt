--
-- Insert for table 'HIRE'
--
INSERT INTO CUSTOMER (cust_id, first, last, street, city, state, zip)VALUES (601, 'ryan', 'kozak', '123 Fake Street', 'Fair Oaks', 'California', '95628');

--
-- Insert for table 'REWARDS'
--
INSERT INTO REWARDS (r_id, points, cust_id)VALUES (111, 3000, 601);

--
-- Insert for table 'CUSTOMER_PHONE'
--
INSERT INTO CUSTOMER_PHONE (cust_id, phone)VALUES (601, '555-123-4567');

--
-- Insert for table 'CONTRACTOR'
--
INSERT INTO CONTRACTOR (bus_name, discount)VALUES ('JB Paints', 33);

--
-- Insert for table 'CONTRACTOR_PHONE'
--
INSERT INTO CONTRACTOR_PHONE (bus_name, phone)VALUES ('JB Paints', '555-233-5555');

--
-- Insert for table 'HIRE'
--
INSERT INTO HIRE (cust_id, bus_name, hours)VALUES (601, 'JB Paints', 20);

--
-- Insert for table 'ROOM'
--
INSERT INTO ROOM (name, cust_id)VALUES ('Bed Room', 601);
INSERT INTO ROOM (name, cust_id)VALUES ('Living Room', 601);

--
-- Insert for table 'PAINT_COLOR'
--
INSERT INTO PAINT_COLOR (mfg_id, color_id, name)VALUES (987, 333, 'Blueish');
INSERT INTO PAINT_COLOR (mfg_id, color_id, name)VALUES (986, 334, 'Greenish');

--
-- Insert for table 'PAINTED'
--
INSERT INTO PAINTED (rm_name, cust_id, mfg_id, color_id)VALUES ('Bed Room', 601, 987, 333);
INSERT INTO PAINTED (rm_name, cust_id, mfg_id, color_id)VALUES ('Living Room', 601, 986, 334);

--
-- Delete for table 'PAINTED'
--
DELETE FROM PAINTED WHERE rm_name = 'Living Room' AND cust_id = 601;

--
-- Update for table 'HIRE'
--
UPDATE HIRE SET hours = 35 WHERE cust_id = 601 AND bus_name = 'JB Paints';



