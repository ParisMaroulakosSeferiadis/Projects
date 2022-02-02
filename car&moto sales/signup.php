<?php
 ob_start();
 session_start();
 if( isset($_SESSION['user'])!="" ){
  header("Location: chat.php");
 }
 include_once 'Dbconnect.php';

 $error = false;

 if ( isset($_POST['btn-signup']) ) {
  
  // clean user inputs to prevent sql injections
  $name = trim($_POST['name']);
  $name = strip_tags($name);
  $name = htmlspecialchars($name);
  
  $cellnum = trim($_POST['cellnum']);
  $cellnum = strip_tags($cellnum);
  $cellnum = htmlspecialchars($cellnum);
  
  $Dlic = trim($_POST['Dlic']);
  $DLic = strip_tags($DLic);
  $DLIc = htmlspecialchars($DLIc);
  
  $addr = trim($_POST['addr']);
  $addr = strip_tags($addr);
  $addr = htmlspecialchars($addr);
  
  $city = trim($_POST['city']);
  $city = strip_tags($city);
  $city = htmlspecialchars($city);
  
  
  
  
  
  // basic name validation
  if (empty($name)) {
   $error = true;
   $nameError = "Παρακαλώ εισάγετε το όνομά σας!.";
  } else if (strlen($name) < 3) {
   $error = true;
   $nameError = "Το όνομά σας πρέπει να αποτελείται απο τουλάχιστον 3 χαρακτήρες!";
  } else if (!preg_match("/^[a-zA-Z ]+$/",$name)) {
   $error = true;
   $nameError = "Το όνομά σας πρέπει να αποτελείται ΜΟΝΟ από χαρακτήρες και κενά!.";
  }
  
  //basic cellnum validation
  if (empty($cellnum)){
   $error = true;
   $cellnumError = "Παρακαλώ εισάγετε τον αριθμό τηλεφώνου σας!";
  } else {
   // check cellnum exist or not
   $query = "SELECT Cell_num FROM COSTOMER WHERE Cell_num='$cellnum'";
   $result = mysqli_query($conn,$query);
   $count = mysqli_num_rows($result);
   if($count!=0){
    $error = true;
    $cellnumError = "Λυπούμαστε! O συγκεκριμένος αριθμός χρησιμοποιείται ήδη! ";
   }
  }
  // DLIC validation
  if (empty($Dlic)){
   $error = true;
   $DLic = "Παρακαλώ εισάγετε τον αριθμό της  άδειας οδήγησης!";
  } else
	   $query = "SELECT D_license_num FROM COSTOMER WHERE D_license='$DLic'";
       $result = mysqli_query($conn,$query);
       $count = mysqli_num_rows($result);
	 if(strlen($DLic) < 9) {
   $error = true;
   $DLicError = "H άδεια οδήγησης σας πρέπει να έχει 9 στοιχεία!";
  }
  if (empty($city)) {
   $error = true;
   $cityError = "Παρακαλώ εισάγετε το όνομά της πόλης σας!";
  } else if (strlen($city) < 3) {
   $error = true;
   $cityError = "Το όνομά της σας πρέπει να αποτελείται απο τουλάχιστον 3 χαρακτήρες!";
  } else if (!preg_match("/^[a-zA-Z ]+$/",$city)) {
   $error = true;
   $cityError = "Το όνομά της πόλης σας πρέπει να αποτελείται ΜΟΝΟ από χαρακτήρες και κενά!";
  }
   if (empty($addr)) {
   $error = true;
   $addrError = "Παρακαλώ εισάγετε την διευθυνση σας!";
  } else if (strlen($addr) < 3) {
   $error = true;
   $addrError = "Το όνομά σας πρέπει να αποτελείται απο τουλάχιστον 3 χαρακτήρες Και ενα νουμερο!";
  
  
  // Dlic encrypt using SHA256();
  $Dlic = hash('sha256', $DLic);
  
  
  
  // if there's no error, continue to signup
  if( !$error ) {
   
   $query = "INSERT INTO CUSTOMER(name,Cell_num,D_license,city,address) VALUES('$name','$cellnum','$Dlic','$city','$addr')";
   $res = mysqli_query($conn,$query);
    
   if ($res) {
    $errTyp = "success";
    $errMSG = "Επιτυχής εγγραφή! Τώρα μπορείτε να συνδεθείτε!";
    unset($name);
    unset($cellnum);
    unset($Dlic);
	unset($city);
	unset($addr);
   } else {
    $errTyp = "danger";
    $errMSG = "Φαίνεται πως υπήρξε ένα πρόβλημα! Δοκιμάστε ξανά αργότερα!!"; 
   } 
    
  }
  
  
 }
?>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Εγγραφή μέλους</title>
</head>
<body text="#0048BA">

<div class="container">

 <div id="login-form">
    <form method="post" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>" autocomplete="on">
    
     <div class="col-md-12">
        
         <div class="form-group">
             <h2 class=""><center>Εγγραφή</center></h2>
            </div>
        
         <div class="form-group">
             <hr />
            </div>
            
            <?php
   if ( isset($errMSG) ) {
    
    ?>
    <div class="form-group">
             <div class="alert alert-<?php echo ($errTyp=="success") ? "success" : $errTyp; ?>">
    <span class="glyphicon glyphicon-info-sign"></span> <?php echo $errMSG; ?>
                </div>
             </div>
                <?php
   }
   ?>
            
            <div class="form-group">
             <div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-user"></span></span>
             <input type="text" name="name" class="form-control" placeholder="Enter Name" maxlength="50" value="<?php echo $name ?>" />
                </div>
                <span class="text-danger"><?php echo $nameError; ?></span>
            </div>
            
            <div class="form-group">
             <div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-envelope"></span></span>
             <input type="password" name="DLIC" class="form-control" placeholder="Enter Your Driver License" maxlength="40" value="<?php echo $Dlic ?>" />
                </div>
                <span class="text-danger"><?php echo $DlicError; ?></span>
            </div>
			 <div class="form-group">
             <div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-envelope"></span></span>
             <input type="number" name="cellnum" class="form-control" placeholder="Enter Your Cell Number" maxlength="40" value="<?php echo $cellnum ?>" />
                </div>
                <span class="text-danger"><?php echo $cellnumError; ?></span>
            </div>
            
            <div class="form-group">
             <div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-lock"></span></span>
             <input type="text" name="city" class="form-control" placeholder="Enter the name of your City" maxlength="15" />
                </div>
                <span class="text-danger"><?php echo $city; ?></span>
            </div>
			 <div class="form-group">
             <div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-user"></span></span>
             <input type="text" name="address" class="form-control" placeholder="Enter your Address" maxlength="50" value="<?php echo $addr ?>" />
                </div>
                <span class="text-danger"><?php echo $addrError; ?></span>
            </div>
            
            <div class="form-group">
             <hr />
            </div>
            
            <div class="form-group">
             <button type="submit" class="btn btn-block btn-primary" name="btn-signup">Εγγραφή</button>
            </div>
            
            <div class="form-group">
             <hr />
            </div>
            
            <div class="form-group">
             <a href="login.php">Έγινες μέλος;Συνδέσου εδώ!</a>
            </div>
        
        </div>
   
    </form>
    </div> 

</div>
<br><br><br><br><br><br><br>
<center><img src ="communication3.gif"  width="500" height="400" ></center>

</body>
</html>
<?php ob_end_flush(); ?>