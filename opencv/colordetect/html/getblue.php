<?php 
header('Content-type: application/json');
	$blue_count = file('blue_count.txt')[0];
	print($blue_count);
?>

