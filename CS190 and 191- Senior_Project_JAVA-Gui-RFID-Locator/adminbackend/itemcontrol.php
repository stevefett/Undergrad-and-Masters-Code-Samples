<center><a href=locate.php>Locate Items</a>   |   <a href=locationalhistory.php>Location History</a>   |   <a href=usercontrol.php>Manage Users</a>   |   <a href=itemcontrol.php>Manage Item Inventory</a>   |   <a href=itemclasscontrol.php>Manage Item Categories</a>   |   <a href=antennacontrol.php>Manage Antennas</a>   |   <a href=roomcontrol.php>Manage Room Layouts</a></center><br><br>

<form action="itemcontrol.php" method="post">
<center><h1>Item Control System</h1></center>
<br>


<?php
$_SESSION['adminID'] = 1;
if ($_SESSION['adminID'] == 0)
{
    echo 'You don\'t have access to this.';
    exit();
}
else
{
    $adminID = $_SESSION['adminID'];
    $con = mysql_connect("stevefett.gotdns.com", "root", "moocow");
    if (!$con)
    {
	    die('Could not connect: ' . mysql_error());
    }
    $dbname = "seniorproject";
    mysql_select_db($dbname, $con) or die ($dbname . "database not found.");
//	$username = strtolower($_POST[vetUserName]);
    $query1 = "SELECT * FROM itemtable";
    $result = mysql_query($query1) or die ("Failed Query of " . $query1 . "Error: " . mysql_error());
    $thisrow = mysql_fetch_array($result, MYSQL_BOTH);
    echo '<center><table border="1"> <tr> <col width="10"><th>RFID Tag ID</th> <th>Serial Number</th> <th>Make</th> <th>Model</th> <th>Item Class ID</th>
				    <th>Keyword List</th> <th>Added By</th> <th>Current Owner</th> </tr>';
    while ($thisrow != NULL)
    {
	    echo '<tr> <td><input type="text" name="TagID" size=10 value="';
		    echo $thisrow['TagID'];
	    echo '"></td>';
	    echo '<td> <input type="text" name="SerialNumber" size=10 value="';
		    echo $thisrow['SerialNumber'];
	    echo '"></td>';
	    echo '<td><input type="text" name="ItemMake" value="';
		    echo $thisrow['ItemMake'];
	    echo '"></td>';
	    echo '<td><input type="text" name="ItemModel" value="';
		    echo $thisrow['ItemModel'];
	    echo '"></td>';

	$query2 = 'SELECT ItemClassID, ItemClassName FROM itemclasstable WHERE ItemClassID="' . $thisrow['ItemClassID'] . '";';
	$query3 = 'SELECT ItemClassID, ItemClassName FROM itemclasstable';
	$query4 = 'SELECT UserName, FirstName, LastName FROM usertable WHERE UserID="' . $thisrow['AddedBy'] . '";';
	$query5 = 'SELECT UserName, FirstName, LastName FROM usertable WHERE UserID="' . $thisrow['CurrentOwner'] . '";';
	$query6 = 'SELECT UserName, FirstName, LastName FROM usertable';

	
	$result2 = mysql_query($query2);
	$result3 = mysql_query($query3);
	$result4 = mysql_query($query4);
	$result5 = mysql_query($query5);
	$result6 = mysql_query($query6);
	$newrow = mysql_fetch_array($result2, MYSQL_BOTH);
	
	echo '<td>';
	
       echo "<SELECT>
                      <OPTION SELECTED> " . $newrow['ItemClassName'];
                $newrow = mysql_fetch_array($result3, MYSQL_BOTH);
                while ($newrow != NULL)
                {
                        echo "
                                <OPTION>". $newrow['ItemClassName'];
                        $newrow = mysql_fetch_array($result3, MYSQL_BOTH);
                }
                echo '</SELECT>';
	    echo '</td>';

//	    echo '<td><input type="text" name="ItemClassID" value="';
//		    echo $thisrow['ItemClassID'];
//	    echo '"></td>';
	    echo '<td><input type="text" name="KeywordList" value="';
		    echo $thisrow['KeywordList'];
	    echo '"></td>';
	    $userAdded = mysql_fetch_array($result4);
	    echo '<td>' . $userAdded['FirstName'] . ' ' . $userAdded['LastName'];
	    echo '</td>';
//	    echo '<td><input type="text" name="CurrentOwner" value="';
//		    echo $thisrow['CurrentOwner'];

		$newowner = mysql_fetch_array($result5, MYSQL_BOTH);
		echo '<td>';
		echo "<SELECT>
		";
		if ($newowner != NULL)
		{	echo "<OPTION SELECTED> " . $newowner['FirstName'] . " " . $newowner['LastName']; 
		}
		$newowner = mysql_fetch_array($result6, MYSQL_BOTH);
		while ($newowner != NULL)
		    {
			    echo "<OPTION>" . $newowner['FirstName'] . " " . $newowner['LastName'];
			$newowner = mysql_fetch_array($result6, MYSQL_BOTH);
		}
		echo '</SELECT>';
	    echo '</td>';
    
	    echo '</tr>';
	    
	    $thisrow = mysql_fetch_array($result, MYSQL_BOTH);
    }
    echo '<tr> <td> <input type="text" name="TagID" size=10 value=""></td>
	  <td> <input type="text" name="SerialNumber" size=10 value=""></td>
	  <td> <input type="text" name="ItemMake" value=""></td>
	    <td><input type="text" name="ItemModel" value=""></td>
';

      echo "<td><SELECT>";
                $result3 = mysql_query($query3);
		
                while ($newrow = mysql_fetch_array($result3, MYSQL_BOTH))
		{
                echo "
                                <OPTION>". $newrow['ItemClassName'];
                 //       $newrow = mysql_fetch_array($result3, MYSQL_BOTH);
                }
                echo '</SELECT>';
            echo '</td>


	    <td><input type="text" name="KeywordList" value=""></td>

      <td> </td>
           
	      <td><SELECT>';
                $result6 = mysql_query($query6);

                while ($newrow = mysql_fetch_array($result6, MYSQL_BOTH))
                {
                echo "
                                <OPTION>". $newrow['FirstName'] . " " . $newrow['LastName'];
                 //       $newrow = mysql_fetch_array($result3, MYSQL_BOTH);
                }
                echo '</SELECT>';
            echo '</td>

	    </tr>';
    echo '</table> <input type="Submit" value="Submit Updates"><br>To submit new items, fill in the bottom-most blank forms and submit.</center></form>';
    
}

?>



<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<style type="text/css">
a:link.log {color: #FFFFFF; text-decoration: none}
a:visited.log {color: #FFFFFF; text-decoration: none}
a:hover.log {color: #FFFFFF; text-decoration:underline}
a:active.log {color: #FFFFFF; text-decoration: none}
td.bordr {
	border-color: #000050;
	border-width: 3px;
	border-left:solid;
	border-right:solid;
}
form {
	margin: 0;
}
.style1 {
	color:#FFFFFF;
}
.style2 {
	color: #000000;
}
.style3 {
	color: #FFFFFF;
	font-size: small;
}
</style>




<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Item Control</title>

</head>

<body>





        <br>
	  <br>
</body>
</html>
