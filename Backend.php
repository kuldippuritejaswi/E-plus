<?php


//session_start();
//$_SESSION["blat"]=9;
//$_SESSION["blong"]=4;
//$_SESSION["clat"]=55;
//$_SESSION["clong"]=66;

$servername = "localhost";
$username = "root";
$password = "";
$dbname="amb";

// Create connection
$conn = new mysqli($servername, $username, $password,$dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
echo "Connected successfully";





if ((!empty($_GET['blat'])) && !empty($_GET['blong']))
{

$x=$_GET['blat'];
$y=$_GET['blong'];



$sql="UPDATE amb set value = $x where name ='blat' ";

$sql1="UPDATE amb set value = $y where name ='blong' ";

if ($conn->query($sql) === TRUE && $conn->query($sql1)==TRUE ) {
    echo "Record updated successfully";
} else {
    echo "Error updating record: " . $conn->error;
}


}


if ((!empty($_GET['clat'])) && !empty($_GET['clong']))
{

$x=$_GET['clat'];
$y=$_GET['clong'];



$sql="UPDATE amb set value = $x where name ='clat' ";

$sql1="UPDATE amb set value = $y where name ='clong' ";

if ($conn->query($sql) === TRUE && $conn->query($sql1)==TRUE ) {
    echo "Record updated successfully";
} else {
    echo "Error updating record: " . $conn->error;
}


}






$sql = "SELECT value FROM amb WHERE name='blat' limit 1";
$result = $conn->query($sql);
$row = $result->fetch_assoc();
$blat = $row["value"];



$sql = "SELECT value FROM amb WHERE name='blong' limit 1";
$result = $conn->query($sql);
$row = $result->fetch_assoc();
$blong = $row["value"];



$sql = "SELECT value FROM amb WHERE name='bclat' limit 1";
$result = $conn->query($sql);
$row = $result->fetch_assoc();
$clat = $row["value"];




$sql = "SELECT value FROM amb WHERE name='clong' limit 1";
$result = $conn->query($sql);
$row = $result->fetch_assoc();
$clong = $row["value"];













 if ((!empty($_GET['alat'])) && !empty($_GET['along']))
{

$alat= $_GET['alat'];
$along=$_GET['along'];




$d1 = sqrt(  pow(($blat-$alat),2) + pow(($blong-$along),2));

$d2 = sqrt(  pow(($clat-$alat),2) + pow(($clong-$along),2));


//patient details
$name='kuldippuritejaswi';
$age="22";
$sex="male";
$blood="b+";
$other="allergic to dust ,yada yada yada";



$message = "

<html>
<head>
<title><b>Accident detected</b></title>
</head>
<body>
<h2> Accident detected near you </h2>
<p>Patient Details</p>
<table>
<tr>
<td>name : $name </td>
<td>age : $age </td>
<td> sex : $sex</td>
<td> age: $age</td>
</tr>
<tr>
<td>blood : $blood </td>
<td>other : $other </td>
</tr>
</table>
callambulance.esy.es/xyz.php?lat=$alat&long=$along

</body>
</html>
";











if($d1<$d2)
{


// The message


// In case any of our lines are larger than 70 characters, we should use wordwrap()
$message = wordwrap($message, 70, "\r\n");
$headers = "MIME-Version: 1.0" . "\r\n";
$headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";

// Send
echo mail('kuldippuritejaswi@gmail.com', 'My Subject', $message,$headers);

}


if($d2<$d1)
{


// The message


// In case any of our lines are larger than 70 characters, we should use wordwrap()
$message = wordwrap($message, 70, "\r\n");
$headers = "MIME-Version: 1.0" . "\r\n";
$headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";

// Send
echo mail('kapticries@gmail.com', 'My Subject', $message,$headers);

}









 } 








?>
