<html>
	<head>
		<title>PHP Test</title>
	</head>
	<body>
<?php 

	$color = htmlspecialchars($_GET["color"]);
	//print("Hello world<br>");

	if ($color == "green") {
		$fn = "../green_count.txt";
		$green = file($fn)[0];
		$green = $green+1;
		print("Green is now $green. <br>");
		$fh = file_put_contents($fn, $green);
	}

	if ($color == "red") {
		$fn = "../red_count.txt";
		$red = file($fn)[0];
		$red = $red+1;
		print("Red is now $red. <br>");
		$fh = file_put_contents($fn, $red);
	}

	if ($color == "blue") {
		$fn = "../blue_count.txt";
		$blue = file($fn)[0];
		$blue = $blue+1;
		print("blue is now $blue. <br>");
		$fh = file_put_contents($fn, $blue);
	}

?>

	</body>
</html>

