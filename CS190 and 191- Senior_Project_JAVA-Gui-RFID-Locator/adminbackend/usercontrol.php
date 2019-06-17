<center><a href=locate.php>Locate Items</a>   |   <a href=locationalhistory.php>Location History</a>   |   <a href=usercontrol.php>Manage Users</a>   |   <a href=itemcontrol.php>Manage Item Inventory</a>   |   <a href=itemclasscontrol.php>Manage Item Categories</a>   |   <a href=antennacontrol.php>Manage Antennas</a>   |   <a href=roomcontrol.php>Manage Room Layouts</a></center><br><br>

<form action="usercontrol.php" method="post">

<center><h1>User Control System</h1></center>
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
	$query1 = "SELECT * FROM usertable";
	$result = mysql_query($query1) or die ("Failed Query of " . $query1 . "Error: " . mysql_error());
	$thisrow = mysql_fetch_array($result, MYSQL_BOTH);
	echo '<center><table border="1"> <tr> <th>User Name</th> <th>First Name</th> <th>Last Name</th> <th>Set Password</th> <th>Permission</th></tr>';
	while ($thisrow != NULL)
	{
		echo '<tr> <td><input type="text" name="UserName" value="';
			echo $thisrow['UserName'];
		echo '"></td>';
		echo '<td> <input type="text" name="FirstName" value="';
			echo $thisrow['FirstName'];
		echo '"></td>';
		echo '<td><input type="text" name="LastName" value="';
			echo $thisrow['LastName'];
		echo '"></td>';
		echo '<td><input type="text" name="Password" value="';
		
		echo '"></td>';
		echo '<td><SELECT> 
			  <OPTION SELECTED>';
				if ($thisrow['Permissions'] == 1)
					echo 'Lab Manager';
				else if ($thisrow['Permissions'] == 0)
					echo 'System Administrator';
				else
					echo 'User';
			echo '
			  <OPTION>User
			  <OPTION>Lab Manager
			  <OPTION>System Administrator
			  </SELECT>
			 ';

		


		
		echo '</td>';
			
		echo '</tr>';
		
		$thisrow = mysql_fetch_array($result, MYSQL_BOTH);
	}
	echo '<tr> <td> <input type="text" name="UserName" value=""></td>
              <td> <input type="text" name="FirstName" value=""></td>
              <td> <input type="text" name="LastName" value=""></td>
		<td><input type="text" name="Password" value=""></td>
		<td><SELECT>
			<OPTION>User
			<OPTION>Lab Manager
			<OPTION>System Administrator
			</SELECT></td>
		</tr>';
	echo '</table> <input type="Submit" value="Submit Updates"><br>To submit new users, fill in the bottom-most blank forms and submit.</center></form>';
	
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
<title>User Control</title>
</head>

<body>





        <br>
	  <br>
</body>
</html>
