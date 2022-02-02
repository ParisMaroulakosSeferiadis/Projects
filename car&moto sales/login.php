



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
		        <td align=center><a href=login.php> Κύρια Σελίδα</a> </td>
				<td align=center><a href=epikoin.html> Στοιχεία επικοινωνίας<a> </td>
				
			
		
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
             <input type="text" name="name" class="form-control" placeholder="Your name" value="<?php echo $name; ?>" maxlength="40" />
                </div>
                <span class="text-danger"><?php echo $nameError; ?></span>
            </div>
            
            <div class="form-group">
             <div class="input-group">
                <span class="input-group-addon"><span class="glyphicon glyphicon-lock"></span></span>
             <input type="password" name="Dlic" class="form-control" placeholder="Your driver license" maxlength="15" />
                </div>
                <span class="text-danger"><?php echo $DlicError; ?></span>
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
<br><br><br><br><br><br><br><br>
	

</body>
</html>
