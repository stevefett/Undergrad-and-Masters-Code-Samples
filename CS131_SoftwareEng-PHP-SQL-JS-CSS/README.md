# Student Attendance Tracker --Steven Salmons, CSC131p

Web applicatin designed by Steven Salmons for CSC 131. It is a PHP student attendance tracking system that leverages the Google Sheets API to store student attendance information. API usage is evaluated on how "RESTful" the application utilizes its functions -- agnostic as to the content that is being fetched, modified, and/or stored.

This project is a culmination of CSC131 followint topics:  Dynamic web design on Linux Apache Tomcat;  Use of assistive IDEs such as Composer that can ensure proper install, config, persistence and monitoring of web services as background daemon mode via '&';  Use of JSON, XML, and/or CSS to format the database fetched content and visual appeal of DHTML / HTML5 pages and frames;  how to learn and use functions of external party api libraries, including install, config, & resource management of web applications; execution of stored/transactional SQL functions.

#### Development Installation
1) Rename /config/config.php.sample to /config/config.php
2) Input your configuration settings.
3) Copy your .json token into the project directory for Google Sheets Authentication.
3) Run ```composer install ``` for dependency installation.
