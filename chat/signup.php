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
  
  $email = trim($_POST['email']);
  $email = strip_tags($email);
  $email = htmlspecialchars($email);
  
  $pass = trim($_POST['pass']);
  $pass = strip_tags($pass);
  $pass = htmlspecialchars($pass);
  
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
  
  //basic email validation
  if ( !filter_var($email,FILTER_VALIDATE_EMAIL) ) {
   $error = true;
   $emailError = "Παρακαλώ καταχωρηστε μια έγκυρη διεύθυνση email!";
  } else {
   // check email exist or not
   $query = "SELECT userEmail FROM users WHERE userEmail='$email'";
   $result = mysqli_query($conn,$query);
   $count = mysqli_num_rows($result);
   if($count!=0){
    $error = true;
    $emailError = "Λυπούμαστε! Η συγκεκριμένη διεύθυνση email χρησιμοποείτα από άλλον χρηστη! ";
   }
  }
  // password validation
  if (empty($pass)){
   $error = true;
   $passError = "Παρακαλώ εισάγετε έναν κωδικό!.";
  } else if(strlen($pass) < 6) {
   $error = true;
   $passError = "Ο κωδικός σας πρέπει να έχει τουλάχιστον 6 στοιχεία!.";
  }
  
  // password encrypt using SHA256();
  $password = hash('sha256', $pass);
  
  // if there's no error, continue to signup
  if( !$error ) {
   
   $query = "INSERT INTO users(userName,userEmail,userPass) VALUES('$name','$email','$password')";
   $res = mysqli_query($conn,$query);
    
   if ($res) {
    $errTyp = "success";
    $errMSG = "Επιτυχής εγγραφή! Τώρα μπορείτε να συνδεθείτε!";
    unset($name);
    unset($email);
    unset($pass);
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
             <input type="email" name="email" class="form-control" placeholder="Enter Your Email" maxlength="40" value="<?php echo $email ?>" />
                </div>
                <span class="text-danger"><?php echo $emailError; ?></span>
            </div>
            
            <div class="form-group">
             <div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-lock"></span></span>
             <input type="password" name="pass" class="form-control" placeholder="Enter Password" maxlength="15" />
                </div>
                <span class="text-danger"><?php echo $passError; ?></span>
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
<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>
	<hr><hr>
	<h1><center>  Duth Chat </center></h1>


</body>
</html>
<?php ob_end_flush(); ?>