<html>
	<head>
		<title>PHP Test</title>
	</head>
	<body>
<?php 
	$command = escapeshellcmd('/upload/script.py');
	$output = shell_exec($command);
	echo $output;
?>

	</body>
</html>

