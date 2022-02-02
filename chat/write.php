<?php
require("./Dbconnect.php");

//get userinput from url
$username=substr($_GET["username"], 0, 32);
$text=substr($_GET["text"], 0, 128);
//escaping is extremely important to avoid injections!
$nameEscaped = htmlentities(mysqli_real_escape_string($conn,$username)); //escape username and limit it to 32 chars
$textEscaped = htmlentities(mysqli_real_escape_string($conn, $text)); //escape text and limit it to 128 chars



//create query
$query="INSERT INTO chat (username, text) VALUES ('$nameEscaped', '$textEscaped')";
//execute query
if ($conn->real_query($query)) {
    //If the query was successful
    echo "Wrote message to db";
}else{
    //If the query was NOT successful
    echo "An error occured";
    echo $conn->errno;
}

$conn->close();
?>
