<?php

// Load resources from composer.
require_once __DIR__.'/vendor/autoload.php';

// Load configuration constants.
require_once('config/config.php');


require_once('Mail.php');

// This is for the web service-account auth
putenv('GOOGLE_APPLICATION_CREDENTIALS=CSC131-Attendance-ebe15e15e23b.json');

// The scope allows access to only the Google Sheets API through.
define('SCOPES', implode(' ', array( Google_Service_Sheets::SPREADSHEETS) ));


/**
 * This is the main class file for now, it supports the cli and web apps.
 *
 */
class StudentAuth {


	/**
	 * StudentAuth constructor.
	 */
	function __construct() {
		$this->client = $this->getClient();
		$this->service = new Google_Service_Sheets($this->client);
		$this->spreadsheetId = G_SHEET_ID; // Our Demo Sheet
	}


	/**
	 * Returns an authorized API client.
	 * @return Google_Client the authorized client object
	 */
	function getClient() {

		$client = new Google_Client();

		$client->useApplicationDefaultCredentials();
		$client->setApplicationName(APPLICATION_NAME);
		$client->setScopes(SCOPES);
		$client->setAccessType('offline');

		return $client;
	}


	/**
	 * Get a student id, and try and set their attendance.
	 *
	 * @param $student_id
	 * @return int
	 */
	function tryStudentID($student_id) {

		// Range of student ID's in our sheet
		$range = 'A2:A31';

		// Google Sheets API response.
		$response = $this->service->spreadsheets_values->get($this->spreadsheetId, $range);
		$values = $response->getValues();

		$row_counter = 2;

		foreach ($values as $row) {

			if($row[0] == $student_id) {

				$attendance_cell = 'D'.$row_counter;
                                $date_cell = 'E'.$row_counter;
                                $time_cell = 'F'.$row_counter;

				if($this->checkAttendance($attendance_cell)) {
					return 2;
				}
				else {
                    $attending = 'yes';
					$this->updateAttendance($attendance_cell, $attending);
					$time =  date("Y-m-d") . " at " . date("g:i:s a");
                    $this->updateAttendance($date_cell, date("m-d-Y")); //Fix to pass in values of time
                    $this->updateAttendance($time_cell, date("g:i:s a")); //Fix to pass in values of time variable

					// Give the student a receipt
					$this->getReceipt($time, $student_id, $row_counter);

					// Set a browser cookie if not in cli environment.
					return 1;
				}

			}

			$row_counter++;

		}

		return 0;

	}


	/**
	 * Check current attendance of student by
     * checking the spreadsheets cell.
	 *
     * @param string
	 * @return boolean
	 */
	function checkAttendance($range) {

		// Google Sheets API response.
		$response = $this->service->spreadsheets_values->get($this->spreadsheetId, $range);
		$values = $response->getValues();


		if($values[0][0] == "yes") {
			return true;
		}

		return false;

	}


    /**
     * Validate that the key sent by the student is correct.
     *
     * @param string
     * @return bool
     */
    function validateKey($key) {

        // Google Sheets API response.
        $response = $this->service->spreadsheets_values->get($this->spreadsheetId, 'J2');
        $values = $response->getValues();


        if($values[0][0] == $key) {
            return true;
        }

        return false;

    }


	/**
	 * Set student the attendance.
	 *
     * @param string
     * @param string
	 * @return Google_Service_Sheets_UpdateValuesResponse
	 */
	function updateAttendance($range, $cell_value) {

		$values = array(
			array(
				$cell_value
			),
		);

		$body = new Google_Service_Sheets_ValueRange( array(
			'values' => $values
		));

		$params = array(
			'valueInputOption' => 'USER_ENTERED'
		);

		$result = $this->service->spreadsheets_values->update($this->spreadsheetId, $range, $body, $params);

		return $result;
	}

    /**
     * Provide the student a receipt upon
     * successful registration for class.
     *
     * @param $time
     * @param $student_id
     * @param $row_counter
     */
	function getReceipt($time, $student_id, $row_counter) {

        //Pulling in the cells with First and Last Names
        $range = 'B2:G32';
        $response = $this->service->spreadsheets_values->get($this->spreadsheetId, $range);
        $values = $response->getValues();

        $msg = "\nHere is your receipt:\n"
            . "\n\n------------------------------------------------\n\n"
            . "Name: " . $values[$row_counter - 2][0] . " " . $values[$row_counter - 2][1]
            . "\nStudent ID: " . $student_id . "\n"
            . "Checked in on " . $time . "\n\n"
            . "----------------------------------------------------\n\n";

        $msg = wordwrap($msg, 70);
        $recipients = $values[$row_counter - 2][5]; //Get email

        Mail::sendReciept($recipients, $msg);

    }
}
