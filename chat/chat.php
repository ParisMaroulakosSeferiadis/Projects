<?php
 ob_start();
 session_start();
 require_once 'Dbconnect.php';
 
 // if session is not set this will redirect to login page
 if( !isset($_SESSION['user']) ) {
  header("Location: login.php");
  exit;
 }
 // select loggedin users detail
 $res=mysqli_query($conn,"SELECT * FROM users WHERE userId=".$_SESSION['user']);
 $userRow=mysqli_fetch_array($res,MYSQLI_ASSOC);
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>CHAT</title>
    <link rel="stylesheet" href="main.css" type="text/css" media="screen" />
</head>
<body text="#0048BA">
    <div class="container">
        <header class="header">
            <h1><b><center>Γράψτε το μήνυμα σας στο chatbox!!</center></b></h1>
        </header>
        <main>
		<div class="userSettings">
                <label for="userName">Username:</label>
                <input id="userName" type="text" placeholder="Username" maxlength="32" value="Somebody">
            </div>
			<div><?php  date_default_timezone_set("Turkey");
			$clock=date("h:i"); 
			echo $clock; ?>
			</div>
            <div class="chat">
                <div id="chatOutput"></div>
                <input id="chatInput" type="text" placeholder="Input Text here" maxlength="256">
                <button id="chatSend">Αποστολή</button>
            </div>
        <p><a href="Logout.php?logout"><span class="glyphicon glyphicon-log-out"></span>&nbsp;Αποσύνδεση</a></p>
        <div style="clear:both"></div>
    </div>
     
        </main>
    </div>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
    <script src="chat.js"></script>
</body>
</html>

       
<?php ob_end_flush(); ?>

       
    