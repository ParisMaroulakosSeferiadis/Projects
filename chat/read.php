<?php
require("./Dbconnect.php");

$query="SELECT * FROM chat ORDER BY id ASC";
//execute query
if ($conn->real_query($query)) {
	//If the query was successful
	$res = $conn->use_result();

    while ($row = $res->fetch_assoc()) {
        $username=$row["username"];
        $text=$row["text"];
        $date=date("d/m/Y"); 
		$time=date('G:i', strtotime($row["time"])); //outputs date as # #Hour#:#Minute# 
        
        echo "<p>$date|$time| $username: $text</p>\n";
    }
}else{
	//If the query was NOT successful
	echo "An error occured";
	echo $conn->errno;
}

$conn->close();
?>
