<?php

require_once('config/config.php');

/**
 * This file handles AJAX calls to our application to determine
 * the distance of a student from the classroom. It uses the Google
 * Distance Matrix API.
 *
 */

/* Confirm there is a POST request, and that it contains a latitude and longitude */
if( !empty($_POST) && isset($_POST['lat']) || isset($_POST['long'])) {

    if(valid_coords($_POST['lat'], $_POST['long'])) {
        echo geo_location(floatval($_POST['lat']),floatval($_POST['long']));
    }
    else {
        echo "Invalid POST type!";
    }


}
/*Send them home due to incorrect POST parameters*/
else {
    header( "Location: ");
}


/**
 * Validates that the geocoordinate POST parameters are doubles.
 *
 * @param $lat
 * @param $long
 * @return bool
 */
function valid_coords($lat, $long) {
    return is_double(floatval($lat)) && is_double(floatval($long));
}


/**
 * Determines how far a student's location is from the classroom
 * and returns an integer in meters.
 *
 * @param $student_lat
 * @param $student_long
 * @return $distance_in_meters
 */
function geo_location($student_lat, $student_long) {

    # Google Distance Matrix API URI, endpoint string with variables.
    $api_endpoint = "https://maps.googleapis.com/maps/api/distancematrix/json?&origins=".$student_lat.",".$student_long."&destinations=".CLASS_ROOM_LAT.",".CLASS_ROOM_LONG."&mode=walking&key=".G_MAPS_KEY;

    # Query Google Distance REST API
    $location_response = json_decode(file_get_contents($api_endpoint));

    # Grab the distance in meters from the Google Distance Matrix Response
    $distance_in_meters = $location_response->rows[0]->elements[0]->distance->value;

    # Returns a number.
    return json_encode($distance_in_meters);
}
