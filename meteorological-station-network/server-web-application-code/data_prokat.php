<?php
include ('connection.php');
$sql_insert = "INSERT INTO prokat (DHT_temperature, DHT_humidity, Brightness, LPS_temperature, LPS_pressure, UV_Light) VALUES ('".$_GET["temperature"]."', '".$_GET["humidity"]."', '".$_GET["Lux"]."', '".$_GET["lps_temperature"]."', '".$_GET["lps_pressure"]."', '".$_GET["UV-Light"]."' )";
if(mysqli_query($con,$sql_insert))
{
echo "Done";
mysqli_close($con);
}
else
{
echo "error is ".mysqli_error($con );
}
?>
