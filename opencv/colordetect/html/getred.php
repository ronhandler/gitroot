<?php 
header('Content-type: application/json');
	$red_count = file('red_count.txt')[0];
	print($red_count);
?>

