/**
 * This jQuery functions runs once the DOM is loaded.
 *
 */
$(function() {
    geoLocation();
});


/**
 * Get a users latitude and longitude via their web browser.
 * If geolocation is turned off, then prompt them to turn
 * it on.
 *
 */
function geoLocation() {

    // If on, return latitude and longitude.
    if (navigator.geolocation) {

        navigator.geolocation.getCurrentPosition(function (position) {

            getDistance(position.coords.latitude,position.coords.longitude);

        },function(){},
            {
                enableHighAccuracy: true
            }
        );
    }

    // If off, disable input fields and prompt user to change settings.
    else {
        window.alert('Please enable geolocation!!');
        return false;
    }
}


/**
 * Retrieve a user's distance in meters from the classroom.
 *
 * @param lat
 * @param long
 */
function getDistance(lat,long) {


    var json =  {
        "lat": lat,
        "long": long
    };

    //Destination lat,lng currently hard coded to Riverside Hall.
    var url = "./GeoLocation.php";

    $.ajax(
        {
            url: url,dataType: 'json', type: 'POST', data: json,

            success: function(data)
            {
                console.log(data);
                $("#location").html("Distance from classroom: <b>" + data + " meters</b>");
            },
            error: function(){
                console.log("Can not calculate distance!");
            }
        });

}