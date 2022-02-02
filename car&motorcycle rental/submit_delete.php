<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Διαγραφή καταχώρησης</title>
<style type="text/css">
<!--
.style1 {
	font-size: 36px;
	font-style: italic;
}
body {
	background-color: #FFFFFF;
	background-image: url("7.jpg");
-->
</style>
</head>
<body>
  <div align="center">
    <p><BR>
      <?php 

    include('connect.php');

    $query = "delete from CUSTOMER where D_license = ".$_POST['dlicense']."";
    $queryexe = mysqli_query($con, $query);
    //execute query 
    if ($queryexe) { 
        echo("<p><font size=\"+1\">Η διαγραφή ήταν επιτυχής!</font></p>");
	} 
    else { 
        echo("<p><font size=\"+1\">Δημιουργήθηκε κάποιο λάθος κατά τη διαγραφή!</font></p>");
	} 

?>
      </p>
    <a href="index.php">Πίσω</a><BR>
</div>
</body>
</html>