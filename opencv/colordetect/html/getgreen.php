<?php 
header('Content-type: application/json');
	$green_count = file('green_count.txt')[0];
	print($green_count);
?>

