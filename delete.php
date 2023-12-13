<!-- 
  COMP 333: Software Engineering
  Lance Gartrell
-->



<!DOCTYPE HTML>
<html lang="en">
<head>
  <!-- This is the default encoding type for the HTML Form post submission. 
  Encoding type tells the browser how the form data should be encoded before 
  sending the form data to the server. 
  https://www.logicbig.com/quick-info/http/application_x-www-form-urlencoded.html -->
  <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible"
          content="IE=edge">
    <meta name="viewport" content="application_x-www-form-urlencoded">
    <meta name ="description" content = "The delete page">
    <meta name="description" content="">
    <title>Welcome to the Best Music community</title>
    <link rel="stylesheet" href="">
</head>

<body>
  <?php session_start();

    // insert _GET statement for the global username here
    // may need to sub $u for the global variable 
    if($_SESSION["loggedin"]){
      $u = $_SESSION['name'];
      echo 'logged in as: ' . $u;
    }
    echo '<br /><a href="login.php">Log out</a>';
    if(isset($_GET["id"])){
      $id = $_GET["id"];
    }
    // PHP code for retrieving data from the database. If you have multiple files
    // relying on the this server config, you can create a config.php file and
    // import it with `require_once "config.php";` at the beginning of each file 
    // where you need it.
    // Database credentials per below are default for a local server. Assuming 
    // running MySQL server with default setting (user 'root' with no password).
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "music_db";
    
    // Create server connection.
    // The MySQLi Extension (MySQL Improved) is a relational database driver 
    // used in the PHP scripting language to provide an interface with MySQL 
    // databases (https://en.wikipedia.org/wiki/MySQLi).
    // Instances of classes are created using `new`.
    $conn = new mysqli($servername, $username, $password, $dbname);
    $db = mysqli_connect($servername, $username, $password, $dbname);

    // Check server connection.
    if ($conn->connect_error) {

      // Exit with the error message.
      // . is used to concatenate strings.
      die("Connection failed: " . $conn->connect_error);
    }
    $sql_query = "SELECT song, artist, rating FROM ratings WHERE id = ?";
    $stmt = mysqli_prepare($conn, $sql_query);   
    mysqli_stmt_bind_param($stmt, "i", $id);
    mysqli_stmt_execute($stmt);
    $result = mysqli_stmt_get_result($stmt);
    $row = mysqli_fetch_assoc($result);
    $s = $row['song'];

    if (isset($_REQUEST['submit'])) {
      // Get the submitted ratings to delete
      $song = $_REQUEST["song"];
  
      if(!isset($song)) {
          echo "Please put in a proper selection.";
      }else {
          // Prepare a SQL query to delete the selected ratings
          $sql = "DELETE FROM ratings WHERE song = ? AND username = ?";
          $stmt = mysqli_prepare($conn, $sql);
          mysqli_stmt_bind_param($stmt, "ss", $song, $u);
          if(mysqli_stmt_execute($stmt)){
            echo "your entry has been deleted.";
            header("Location: index.php");
          } else {
            echo "something went wrong";
          }
        }
    }
  
  ?>


  <h1>Delete Rating</h1>
    <hr color="#a01d88"/>
    <p class = "middle">Please enter the name of the song you would like to delete </p>
    
  <!-- 
    HTML code for the form by which the user can query data.
  -->
  <form method="GET" action="">
  Song: <input type="text" name="song" placeholder="<?php echo $s ?>" /><br>
  <input type="submit" name="submit" value="Submit"/>

  

  </form>
  <br /><a href="index.php">Cancel</a>
  <?php
  echo '<br /><a href="index.php">Back</a>';
  ?>
</body>
</html>