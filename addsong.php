<!DOCTYPE HTML>
<html lang="en">
<head>
<meta http-equiv="Content-Type" content="application/x-www-form-urlencoded"/>
<meta name="description" content="The login page">
<link rel="stylesheet" type="text/css" href="" />
  <title>Add New Song</title>
</head>

<body>
<?php 
  session_start();
  // insert _GET statement for the global username here 
  if($_SESSION["loggedin"]){
    $u = $_SESSION['name'];
    echo 'logged in as: ' . $u;
  }
  echo '<br /><a href="login.php">Log out</a>';
  // database information
  $servername = "localhost";
  $username = "root";
  $password = "";
  $dbname = "music_db";

  $db = mysqli_connect($servername, $username, $password, $dbname);
  $conn = new mysqli($servername, $username, $password, $dbname);

  // Check server connection.
  if ($conn->connect_error) {

    // Exit with the error message.
    // . is used to concatenate strings.
    die("Connection failed: " . $conn->connect_error);
  }
  
  // checks if form was submited
  if(isset($_REQUEST['submit'])){
    $out_value = "";
    $artist = $_REQUEST['Artist'];
    $song = $_REQUEST['Song'];
    $rating = $_REQUEST['Rating'];
  

  // checks if the song has already been rated 
    $duplicate = "SELECT * FROM ratings WHERE song = ? ";
    $stmt = mysqli_prepare($conn, $duplicate);
    mysqli_stmt_bind_param($stmt, "s", $song);
    mysqli_stmt_execute($stmt);
    $result = mysqli_stmt_get_result($stmt);
    $row = mysqli_fetch_assoc($result);


    // inserts the user rating into the ratings db 
    if ($row > 0){
        echo "you cant rate the same song twice";
    } else if (empty($song) || empty($artist) || empty($rating)){
        echo "please fill out all fields";
    } else if (!is_numeric($rating)){
        echo "Please enter a number in for the ratings";
    }
    else if(strlen($rating)!=1){
      echo "rating digit should be 1";

    }
    else {
        $sql = "INSERT INTO ratings (username, artist, song, rating) VALUES (?,?,?,?)";
        $stmt1 = mysqli_prepare($conn, $sql);   
        mysqli_stmt_bind_param($stmt1, "sssi", $_SESSION['name'],$artist, $song, $rating);
        mysqli_stmt_execute($stmt1);
        header("Location: index.php");
  }
}
?>

  <h1>Add Song</h1>
    <hr color="#a01d88"/>
    <p class = "middle">Add a New Song Down Below: </p>
  
  <form method="POST" action="">
  Artist: <input type="text" name="Artist" placeholder="" /><br>
  Song: <input type="text" name="Song" placeholder="" /><br>
  Rating: <input type="text" name="Rating" placeholder="" /><br>
  <input type="submit" name="submit" value="submit"/>

  </form>
  <br /><a href="index.php">Cancel</a>
</body>
</html>
