<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>ΔΙΑΓΡΑΦΗ ΠΕΛΑΤΗ</title>
<link rel=stylesheet href="delete.css" type="text/css">
<style type="text/css">

</style>
<script language="JavaScript" src="files/gen_validatorv31.js" type="text/javascript"></script>
</head>

<body>
<center>
  <table width="400" border="0">
    <tr>
       <td><font color="#ffffff"><div align="center" class="style1">Διαγραφή Πελάτη</div></font></td>
    </tr>
  </table>
  <p align="center">&nbsp;</p>
</center>
    <form method="POST" action="submit_delete.php"  name="myform">
      <center>
      <table>
        <tr>
        <td>
     <font color="#ffffff"> <div align="center"><strong>AΔΕΙΑ ΟΔΗΓΗΣΗΣ:</strong> </font>
        <input name="dlicense" type="num" size="20"/>
        <input type="submit" value="Διαγραφή" /></div>
      <center>
      </center>
        </td>
        </tr>
        </table> 
		<br><br><br>
		<a href=index.php>Για να μεταβείτε στην αρχική σελίδα πατήστε εδώ! </a>
      </center>
</form>
<script language="JavaScript" type="text/javascript">
//You should create the validator only after the definition of the HTML form
  var frmvalidator  = new Validator("myform");
  frmvalidator.EnableMsgsTogether();
  frmvalidator.addValidation("dlicense","req","Συμπληρώστε πρώτα το πεδίο 'Aδεια οδήγησης' !");
  frmvalidator.addValidation("dlicense","num","Η τιμή που δώσατε δεν είναι ακέραιος αριθμός!");
      </script>
</body>
</html>
