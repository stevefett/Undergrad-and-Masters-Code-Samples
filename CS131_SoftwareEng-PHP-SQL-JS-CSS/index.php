n<?php
/**
 * This is the main user interface to the.

 *
 */

require_once('config/config.php');
require_once('StudentAuth.php');


/*
 *  If there is a post containing a studentID and an accessKey,
 *  attempt to register the student, otherwise just display the HTML form below.
 */
if( !empty($_POST) && isset($_POST['studentID']) && isset($_POST['accessKey'])) {

    $response = 0;

	$test = new StudentAuth(); // Instance of class.

    // Ensure each POST is a valid integer
    if(preg_match('/^\d+$/', $_POST['studentID']) &&
        preg_match('/^\d+$/', $_POST['accessKey'])) {


        $student_id = $_POST['studentID'];
        $access_key = $_POST['accessKey'];

        if($test->validateKey($access_key)) {

            // Try and register the student, see response
            if(session_status() === PHP_SESSION_ACTIVE) {
                $response = $test->tryStudentID($student_id);
            }

        }
        else {
            $response = 3;
        }

        // Conditional statements to return appropriate UI message to browser.
        if($response == 2) {
            header( "Location: /?signin=duplicate" );
        }
        else if($response == 1) {
            header( "Location: /?signin=success" );
        }
        else if($response == 3) {
            header( "Location: /?signin=key_fail" );
        }
        else {
            header( "Location: /?signin=fail" );
        }


    }
    // Otherwise do not proceed, and go home with a failure.
    else {
        header( "Location: /?signin=fail" );
    }

}

?>

<html>

<head>

	<title>Attendance Tracker</title>

	<meta http-equiv="content-type" content="text/html;charset=UTF-8">
	<meta name="viewport" content="width=device-width, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0, initial-scale=1.0">

    <!-- Favicon for web and mobile -->
    <link rel="apple-touch-icon" sizes="180x180" href="./img/icos/apple-touch-icon.png">
    <link rel="icon" type="image/png" sizes="32x32" href="./img/icos/favicon-32x32.png">
    <link rel="icon" type="image/png" sizes="16x16" href="./img/icos/favicon-16x16.png">
    <link rel="manifest" href="./img/icos/manifest.json">

    <!-- CSS Assets -->
    <link rel="stylesheet" type="text/css" href="./css/bootstrap.min.css">

    <!-- Student Attendance Application Stylesheet -->
    <link rel="stylesheet" type="text/css" href="./css/style.css">

</head>

<body>

    <!-- Success, fail, warning alerts -->
    <?php if(!empty($_GET) && isset($_GET['signin'])): ?>

        <?php if( $_GET['signin'] == 'success' ): ?>
            <div class = "alert alert-success alert-dismissable text-center">
                <button type = "button" class = "close" data-dismiss = "alert">
                    &times;
                </button>
                Success! You're attendance is marked
            </div>
        <?php endif; ?>

	    <?php if( $_GET['signin'] == 'duplicate' ): ?>
            <div class = "alert alert-warning alert-dismissable text-center">
                <button type = "button" class = "close" data-dismiss = "alert">
                    &times;
                </button>
                You've already signed up before.
            </div>
	    <?php endif; ?>

	    <?php if( $_GET['signin'] == 'fail' ): ?>
            <div class = "alert alert-danger alert-dismissable text-center">
                <button type = "button" class = "close" data-dismiss = "alert">
                    &times;
                </button>
                There was an issue with your submission!
            </div>
	    <?php endif; ?>

        <?php if( $_GET['signin'] == 'key_fail' ): ?>
            <div class = "alert alert-danger alert-dismissable text-center">
                <button type = "button" class = "close" data-dismiss = "alert">
                    &times;
                </button>
                The Access Key You Supplied Was Invalid!
            </div>
        <?php endif; ?>

    <?php endif; ?>
    <!-- End of alerts-->

    <div class="login-page container">
        <div class="row">
            <div class="col-md-12">
                <div class="form">
                    <form class="login-form" action="/" method="POST">
                        <input id="studentID" name="studentID" placeholder="STUDENT ID#" required>
                        <input id="accessKey" name="accessKey" placeholder="ACCESS KEY" required>
                        <button id="submitAttendance" class="btn btn-block btn-warning">ATTENDING</button>
                    </form>
                </div>
            </div>
        </div>
        <div class="row">
            <div class="col-md-12">
                <div id="location"></div>
            </div>
        </div>
    </div>

    <!-- JavaScript Assets -->
    <script type="text/javascript" src="//maps.google.com/maps/api/js?key=<?php echo G_MAPS_KEY?>"></script>
    <script type="text/javascript" src="./js/jquery-3.2.1.min.js"></script>
    <script type="text/javascript" src="./js/bootstrap.min.js"></script>

    <!-- Student Attendance Application JS File -->
	<script type="text/javascript" src="./js/script.js"></script>

</body>

</html>



