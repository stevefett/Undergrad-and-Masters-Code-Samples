-- MySQL dump 10.13  Distrib 5.6.41, for Linux (i686)
--
-- Host: athena    Database: test
-- ------------------------------------------------------
-- Server version	5.6.41

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `CONTRACTOR`
--

DROP TABLE IF EXISTS `CONTRACTOR`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CONTRACTOR` (
  `bus_name` varchar(15) NOT NULL,
  `discount` int(11) DEFAULT NULL,
  PRIMARY KEY (`bus_name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CONTRACTOR`
--

LOCK TABLES `CONTRACTOR` WRITE;
/*!40000 ALTER TABLE `CONTRACTOR` DISABLE KEYS */;
/*!40000 ALTER TABLE `CONTRACTOR` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `CONTRACTOR_PHONE`
--

DROP TABLE IF EXISTS `CONTRACTOR_PHONE`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CONTRACTOR_PHONE` (
  `bus_name` varchar(15) NOT NULL,
  `phone` int(11) NOT NULL,
  PRIMARY KEY (`bus_name`),
  UNIQUE KEY `phone` (`phone`),
  CONSTRAINT `CONTRACTOR_PHONE_ibfk_1` FOREIGN KEY (`bus_name`) REFERENCES `CONTRACTOR` (`bus_name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CONTRACTOR_PHONE`
--

LOCK TABLES `CONTRACTOR_PHONE` WRITE;
/*!40000 ALTER TABLE `CONTRACTOR_PHONE` DISABLE KEYS */;
/*!40000 ALTER TABLE `CONTRACTOR_PHONE` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `CUSTOMER`
--

DROP TABLE IF EXISTS `CUSTOMER`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CUSTOMER` (
  `cust_id` int(11) NOT NULL,
  `first` varchar(15) NOT NULL,
  `last` varchar(15) NOT NULL,
  `street` varchar(15) NOT NULL,
  `city` varchar(15) NOT NULL,
  `state` varchar(15) NOT NULL,
  `zip` varchar(15) NOT NULL,
  PRIMARY KEY (`cust_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CUSTOMER`
--

LOCK TABLES `CUSTOMER` WRITE;
/*!40000 ALTER TABLE `CUSTOMER` DISABLE KEYS */;
/*!40000 ALTER TABLE `CUSTOMER` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `CUSTOMER_PHONE`
--

DROP TABLE IF EXISTS `CUSTOMER_PHONE`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CUSTOMER_PHONE` (
  `cust_id` int(11) NOT NULL,
  `phone` int(11) NOT NULL,
  PRIMARY KEY (`cust_id`),
  UNIQUE KEY `phone` (`phone`),
  CONSTRAINT `CUSTOMER_PHONE_ibfk_1` FOREIGN KEY (`cust_id`) REFERENCES `CUSTOMER` (`cust_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CUSTOMER_PHONE`
--

LOCK TABLES `CUSTOMER_PHONE` WRITE;
/*!40000 ALTER TABLE `CUSTOMER_PHONE` DISABLE KEYS */;
/*!40000 ALTER TABLE `CUSTOMER_PHONE` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `HIRE`
--

DROP TABLE IF EXISTS `HIRE`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `HIRE` (
  `cust_id` int(11) NOT NULL,
  `bus_name` varchar(15) NOT NULL,
  `hours` int(11) DEFAULT NULL,
  PRIMARY KEY (`cust_id`),
  UNIQUE KEY `bus_name` (`bus_name`),
  CONSTRAINT `HIRE_ibfk_1` FOREIGN KEY (`cust_id`) REFERENCES `CUSTOMER` (`cust_id`),
  CONSTRAINT `HIRE_ibfk_2` FOREIGN KEY (`bus_name`) REFERENCES `CONTRACTOR` (`bus_name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `HIRE`
--

LOCK TABLES `HIRE` WRITE;
/*!40000 ALTER TABLE `HIRE` DISABLE KEYS */;
/*!40000 ALTER TABLE `HIRE` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PAINTED`
--

DROP TABLE IF EXISTS `PAINTED`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PAINTED` (
  `rm_name` varchar(15) NOT NULL,
  `cust_id` int(11) NOT NULL,
  `mfg_id` int(11) NOT NULL,
  `color_id` int(11) NOT NULL,
  PRIMARY KEY (`rm_name`),
  UNIQUE KEY `cust_id` (`cust_id`),
  UNIQUE KEY `mfg_id` (`mfg_id`),
  UNIQUE KEY `color_id` (`color_id`),
  CONSTRAINT `PAINTED_ibfk_1` FOREIGN KEY (`rm_name`) REFERENCES `ROOM` (`name`),
  CONSTRAINT `PAINTED_ibfk_2` FOREIGN KEY (`cust_id`) REFERENCES `ROOM` (`cust_id`),
  CONSTRAINT `PAINTED_ibfk_3` FOREIGN KEY (`mfg_id`) REFERENCES `PAINT_COLOR` (`mfg_id`),
  CONSTRAINT `PAINTED_ibfk_4` FOREIGN KEY (`color_id`) REFERENCES `PAINT_COLOR` (`color_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PAINTED`
--

LOCK TABLES `PAINTED` WRITE;
/*!40000 ALTER TABLE `PAINTED` DISABLE KEYS */;
/*!40000 ALTER TABLE `PAINTED` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PAINT_COLOR`
--

DROP TABLE IF EXISTS `PAINT_COLOR`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PAINT_COLOR` (
  `mfg_id` int(11) NOT NULL,
  `color_id` int(11) NOT NULL,
  `name` int(11) DEFAULT NULL,
  PRIMARY KEY (`mfg_id`),
  UNIQUE KEY `color_id` (`color_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PAINT_COLOR`
--

LOCK TABLES `PAINT_COLOR` WRITE;
/*!40000 ALTER TABLE `PAINT_COLOR` DISABLE KEYS */;
/*!40000 ALTER TABLE `PAINT_COLOR` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `REWARDS`
--

DROP TABLE IF EXISTS `REWARDS`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `REWARDS` (
  `r_id` int(11) NOT NULL,
  `points` int(11) DEFAULT NULL,
  `cust_id` int(11) NOT NULL,
  PRIMARY KEY (`r_id`),
  UNIQUE KEY `cust_id` (`cust_id`),
  CONSTRAINT `REWARDS_ibfk_1` FOREIGN KEY (`cust_id`) REFERENCES `CUSTOMER` (`cust_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `REWARDS`
--

LOCK TABLES `REWARDS` WRITE;
/*!40000 ALTER TABLE `REWARDS` DISABLE KEYS */;
/*!40000 ALTER TABLE `REWARDS` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ROOM`
--

DROP TABLE IF EXISTS `ROOM`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ROOM` (
  `name` varchar(15) NOT NULL,
  `cust_id` int(11) NOT NULL,
  PRIMARY KEY (`name`),
  UNIQUE KEY `cust_id` (`cust_id`),
  CONSTRAINT `ROOM_ibfk_1` FOREIGN KEY (`cust_id`) REFERENCES `CUSTOMER` (`cust_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ROOM`
--

LOCK TABLES `ROOM` WRITE;
/*!40000 ALTER TABLE `ROOM` DISABLE KEYS */;
/*!40000 ALTER TABLE `ROOM` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-03-25 14:22:16
