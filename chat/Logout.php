<?php
 session_start();
 if (!isset($_SESSION['name'])) {
  header("Location: login.php");
 } else if(isset($_SESSION['name'])!="") {
  header("Location: chat.php");
 }
 
 if (isset($_GET['logout'])) {
  unset($_SESSION['name']);
  session_unset();
  session_destroy();
  header("Location: login.php");
  exit;
 }
?>