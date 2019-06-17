--
-- Table structure for table `CUSTOMER`
--
CREATE TABLE `CUSTOMER` (
  `cust_id` int(11) NOT NULL,
  `first` varchar(15) NOT NULL,
  `last` varchar(15) NOT NULL,
  `street` varchar(15) NOT NULL,
  `city` varchar(15) NOT NULL,
  `state` varchar(15) NOT NULL,
  `zip` varchar(15) NOT NULL,
  PRIMARY KEY (`cust_id`)
);

--
-- Table structure for table `REWARDS`
--
CREATE TABLE `REWARDS` (
  `r_id` int(11) NOT NULL,
  `points` int(11) DEFAULT NULL,
  `cust_id` int(11) NOT NULL,
  PRIMARY KEY (`r_id`),
  UNIQUE KEY `cust_id` (`cust_id`),
  CONSTRAINT `REWARDS_ibfk_1` FOREIGN KEY (`cust_id`) REFERENCES `CUSTOMER` (`cust_id`)
);

--
-- Table structure for table `CUSTOMER_PHONE`
--
CREATE TABLE `CUSTOMER_PHONE` (
  `cust_id` int(11) NOT NULL,
  `phone` varchar(15) NOT NULL,
  PRIMARY KEY (`cust_id`),
  UNIQUE KEY `phone` (`phone`),
  CONSTRAINT `CUSTOMER_PHONE_ibfk_1` FOREIGN KEY (`cust_id`) REFERENCES `CUSTOMER` (`cust_id`)
);

--
-- Table structure for table `CONTRACTOR`
--
CREATE TABLE `CONTRACTOR` (
  `bus_name` varchar(15) NOT NULL,
  `discount` int(11) DEFAULT NULL,
  PRIMARY KEY (`bus_name`)
);

--
-- Table structure for table `CONTRACTOR_PHONE`
--
CREATE TABLE `CONTRACTOR_PHONE` (
  `bus_name` varchar(15) NOT NULL,
  `phone` varchar(15) NOT NULL,
  PRIMARY KEY (`bus_name`),
  UNIQUE KEY `phone` (`phone`),
  CONSTRAINT `CONTRACTOR_PHONE_ibfk_1` FOREIGN KEY (`bus_name`) REFERENCES `CONTRACTOR` (`bus_name`)
);

--
-- Table structure for table `HIRE`
--
CREATE TABLE `HIRE` (
  `cust_id` int(11) NOT NULL,
  `bus_name` varchar(15) NOT NULL,
  `hours` int(11) DEFAULT NULL,
  PRIMARY KEY (`cust_id`),
  UNIQUE KEY `bus_name` (`bus_name`),
  CONSTRAINT `HIRE_ibfk_1` FOREIGN KEY (`cust_id`) REFERENCES `CUSTOMER` (`cust_id`),
  CONSTRAINT `HIRE_ibfk_2` FOREIGN KEY (`bus_name`) REFERENCES `CONTRACTOR` (`bus_name`)
);

--
-- Table structure for table `ROOM`
--
CREATE TABLE `ROOM` (
  `name` varchar(15) NOT NULL,
  `cust_id` int(11) NOT NULL,
  PRIMARY KEY (`name`),
  CONSTRAINT `ROOM_ibfk_1` FOREIGN KEY (`cust_id`) REFERENCES `CUSTOMER` (`cust_id`)
);

--
-- Table structure for table `PAINT_COLOR`
--
CREATE TABLE `PAINT_COLOR` (
  `mfg_id` int(11) NOT NULL,
  `color_id` int(11) NOT NULL,
  `name` varchar(15) DEFAULT NULL,
  PRIMARY KEY (`mfg_id`),
  UNIQUE KEY `color_id` (`color_id`)
);

--
-- Table structure for table `PAINTED`
--
CREATE TABLE `PAINTED` (
  `rm_name` varchar(15) NOT NULL,
  `cust_id` int(11) NOT NULL,
  `mfg_id` int(11) NOT NULL,
  `color_id` int(11) NOT NULL,
  PRIMARY KEY (`rm_name`),
  CONSTRAINT `PAINTED_ibfk_1` FOREIGN KEY (`rm_name`) REFERENCES `ROOM` (`name`),
  CONSTRAINT `PAINTED_ibfk_2` FOREIGN KEY (`cust_id`) REFERENCES `ROOM` (`cust_id`),
  CONSTRAINT `PAINTED_ibfk_3` FOREIGN KEY (`mfg_id`) REFERENCES `PAINT_COLOR` (`mfg_id`),
  CONSTRAINT `PAINTED_ibfk_4` FOREIGN KEY (`color_id`) REFERENCES `PAINT_COLOR` (`color_id`)
);
