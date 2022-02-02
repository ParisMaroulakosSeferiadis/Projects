<?php include("connect.php"); ?>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Εισαγωγή δεδομένων</title>
<style type="text/css">
<!--
.style1 {
	font-size: 36px;
	font-style: italic;
}
body {
	background-color: #FFFFFF;
}
-->
</style>
</head>
<body>
  <div align="center">
    <p><BR>
      <?php 
    
    $name = $_POST['name'];
    $dlicense = $_POST['dlicense'];
    $cellnum = $_POST['cellnum'];
    $city= $_POST['city'];
    $address = $_POST['address'];  

    $query = "INSERT INTO CUSTOMER (name,D_license,Cell_Num,city,address) VALUES 
('$name','$dlicense','$cellnum','$city','$address')";
  
    //execute query 
    $queryexe = mysqli_query($con, $query);
    
    if (!$queryexe){
        echo("Error description: " . mysqli_error($con));
    }else{
        echo("Success!");
    }

?>
      </p>
    <a href="index.php">Πίσω</a><BR>
</div>
</body>
</html>