<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Προσωπικό</title>
<style type="text/css">
<!--
.style1 {
	font-size: 24px;
	font-weight: bold;
	font-family: "Times New Roman", Times, serif;
}
body {
	background-color: #00CCCC;
}
.style3 {font-size: 9px}
-->
</style>
</head>

<body>
<p align="center"><strong><font size="+2">Εγεγγραμμένοι</font></strong><br/>
<center>
<table border="2" bgcolor="lightcyan">
<thead>
 <tr>
  <th>
   ONOMA
  </th>
  <th>
   AΔΕΙΑ ΟΔΗΓΗΣΗΣ
  </th>
  <th>
   ΤΗΛΕΦΩΝΟ
  </th>  
  <th>
   ΠΟΛΗ
 </tr>
</thead>
<tbody>
<?php
    include('connect.php');

    //SQL query 
    $query = "Select name,D_license,Cell_num,city,address from CUSTOMER"; 
     
    //execute query 
    $result = mysqli_query($con, $query); 

    if (!$result){
        echo("Error description: " . mysqli_error($con));
    }
    
    //query database 
    while($rows = mysqli_fetch_array($result)){
        $name = $rows['name'];
        $dlicense = $rows['D_license'];
        $cellnum = $rows['Cell_num'];
        $city = $rows['city'];
    //format results 

        echo ("<tr><td><div align=\"center\"> $name</div></td> <td><div align=\"center\"> $dlicense</div></td> <td><div align=\"center\"> $cellnum </div></td> <td><div ");     
        echo ("align=\"center\"> $city </div></td>");  
        echo ("</tr>");
    
    }  

    ?> 

</tbody>
	</table>
    </center>
<br><br>
<center>  
    <a href=index.php>Για να μεταβείτε στην αρχική σελίδα πατήστε εδώ! </a>
</center>
</body>
</html>
