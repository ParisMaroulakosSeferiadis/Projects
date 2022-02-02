<?php
$username = "paris";
$pass = "paris1997";
$host = "localhost:3306";
$db_name = "ethernet";
$con = mysqli_connect ($host, $username, $pass);
$db = mysqli_select_db ( $con, $db_name );
?>
