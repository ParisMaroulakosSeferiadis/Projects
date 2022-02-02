<?php
 ob_start();
 session_start();
 require_once 'Dbconnect.php';
 
 // it will never let you open index(login) page if session is set
 if ( isset($_SESSION['user'])!="" ) {
  header("Location: chat.php");
  exit;
 }
 
 $error = false;
 
 if( isset($_POST['btn-login']) ) { 
  
  // prevent sql injections/ clear user invalid inputs
  $email = trim($_POST['email']);
  $email = strip_tags($email);
  $email = htmlspecialchars($email);
  
  $pass = trim($_POST['pass']);
  $pass = strip_tags($pass);
  $pass = htmlspecialchars($pass);
  // prevent sql injections / clear user invalid inputs
  
  if(empty($email)){
   $error = true;
   $emailError = "Παρακαλώ καταχωρηστε τη διεύθυνση email σας.";
  } else if ( !filter_var($email,FILTER_VALIDATE_EMAIL) ) {
   $error = true;
   $emailError = "Παρακαλώ καταχωρηστε μια έγκυρη διεύθυνση email.";
  }
  
  if(empty($pass)){
   $error = true;
   $passError = "Παρακαλώ καταχωρηστε τον κωδικό σας.";
  }
  
  // if there's no error, continue to login
  if (!$error) {
   
   $password = hash('sha256', $pass); // password hashing using SHA256
   $res=mysqli_query($conn,"SELECT userId, userName, userPass  FROM users WHERE userEmail='$email'");
   $row=mysqli_fetch_array($res,MYSQLI_ASSOC);
   $count=mysqli_num_rows($res); // if uname/pass correct it returns must be 1 row
   if( $count == 1 && $row['userPass']==$password ) {
    $_SESSION['user'] = $row['userId'];
    header("Location: chat.php");
   } else {
    $errMSG = "Λάθος συνδυασμός email-κωδικού!Δοκιμάστε ξανά!";
   }
    
  }
  
 }
?>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Σύνδεση μέλους</title>
</head>
<body text="#0048BA">


<div class="container">

 <div id="login-form">
    <form method="post" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>" autocomplete="on">
    
     <div class="col-md-12">
        
         <div class="form-group">
             <h2 class=""><center>Σύνδεση</center></h2>
            </div>
			<table border=3 width=100% bgcolor=grey  >
			<tr>
				<td align=center><a href=odhgosxrhshs.html> Οδηγός Χρήσης </a></td>
				<td align=center><a href=epikoin.html> Στοιχεία επικοινωνίας<a> </td>
				<td align=center><a href=login.php> Κύρια Σελίδα</a> </td>
			</tr>
		</table>
		<br><br><br>
		<a href=index.html>Για να μεταβείτε στην αρχική σελίδα πατήστε εδώ! </a>
        
         <div class="form-group">
             <hr />
            </div>
            
            <?php
   if ( isset($errMSG) ) {
    
    ?>
    <div class="form-group">
             <div class="alert alert-danger">
    <span class="glyphicon glyphicon-info-sign"></span> <?php echo $errMSG; ?>
                </div>
             </div>
                <?php
   }
   ?>
            
            <div class="form-group">
             <div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-envelope"></span></span>
             <input type="email" name="email" class="form-control" placeholder="Your Email" value="<?php echo $email; ?>" maxlength="40" />
                </div>
                <span class="text-danger"><?php echo $emailError; ?></span>
            </div>
            
            <div class="form-group">
             <div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-lock"></span></span>
             <input type="password" name="pass" class="form-control" placeholder="Your Password" maxlength="15" />
                </div>
                <span class="text-danger"><?php echo $passError; ?></span>
            </div>
            
            <div class="form-group">
             <hr />
            </div>
            
            <div class="form-group">
             <button type="submit" class="btn btn-block btn-primary" name="btn-login">Σύνδεση</button>
            </div>
            
            <div class="form-group">
             <hr />
            </div>
            
            <div class="form-group">
             <a href="signup.php">Γίνετε μέλος εδώ!</a>
            </div>
        
        </div>
   
    </form>
    </div> 

</div>
<br><br><br><br><br>
<center><img  src ="communication.gif"  width="400" height="200" ></center>
<br><br><br><br><br><br><br><br><br><br>
	<hr><hr>
	<h1><center>  Duth Chat </center></h1>

</body>
</html>
<?php ob_end_flush(); ?>