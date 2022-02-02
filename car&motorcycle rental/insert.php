<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel=stylesheet href="insert.css" type="text/css">
<title>ΝΕΟΣ ΠΕΛΑΤΗΣ</title>
<style type="text/css">

-->
</style>
<script type='text/JavaScript' src='files/scw.js'></script>
<script language="JavaScript" src="files/gen_validatorv31.js" type="text/javascript"></script>
</head>

<body>

<center>
  <table width="400" border="0">
    <tr>
       <td><div align="center" class="style1">ΝΕΟΣ ΠΕΛΑΤΗΣ</div></td>
    </tr>
  </table>
  <p align="center">&nbsp;</p>
</center>
    <form method="POST" action="submit_insert.php"  name="myform">
      <center>
      <table>
        <tr>
        <td>
      <div align="center"><strong>Όνομα:</strong> <input name="name" type="text" size="50"/></div><br>
      <div align="center"><strong>Άδεια Οδήγησης:</strong> <input name="dlicense" type="number" size="50"/></div><br>
      <div align="center"><strong>Τηλέφωνο:</strong> <input name="cellnum" type="number" size="50"/></div><br>
      <div align="center"><strong>Πόλη:</strong> <input type="text" name="city"  size=25> </div><br>
      <div align="center"><strong>Διεύθυνση:</strong> <input type="text" name="address"  size=25> </div><br>
        <br/>
        </td>
        </tr>
        </table>
        <br/><br/>
        <table width="200" border="0">
          <tr>
            <td width="90"><div align="center">
              <input type="submit" value="Εισαγωγή" />
            </div></td>
            <td width="100"><div align="center">
              <input type="reset" value="Καθαρισμός" />
            </div></td>
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
  frmvalidator.addValidation("firstname","req","Συμπληρώστε πρώτα το πεδίο 'Όνομα' !");
  frmvalidator.addValidation("dlicense","req","Συμπληρώστε πρώτα το πεδίο 'Άδεια οδήγησης' !");
  frmvalidator.addValidation("cellnum","req","Συμπληρώστε πρώτα το πεδίο 'Tηλέφωνο' !");
  frmvalidator.addValidation("city","req","Συμπληρώστε πρώτα το πεδίο 'Πόλη' !");
  frmvalidator.addValidation("addr","req","Επιλέξτε Διεύθυνση!");
 
      </script>
</body>
</html>
