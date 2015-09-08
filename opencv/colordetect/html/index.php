<html>
<style>
	body {
		text-align: center;
		background-image: url("background.jpg");
		background-size: 100% 100%;
		background-repeat: no-repeat;
	}
	#header {
		text-align: center;
		font-family: Geneva, Tahoma, Verdana, sans-serif;
		font-size: 80px;
		line-height: 80px;
		letter-spacing: -1px;
		color: #444;
		margin: 0 0 0 0;
		padding: 0 0 10 0;
		font-weight: bold;
	}
	#sub-header {
		text-align: center;
		font-family: Geneva, Tahoma, Verdana, sans-serif;
		font-size: 60px;
		line-height: 60px;
		letter-spacing: -1px;
		color: #444;
		margin: 0 0 0 0;
		padding: 0 0 10 0;
		font-weight: normal;
	}
	#footer {
		font-family: Geneva, Tahoma, Verdana, sans-serif;
		font-size: 30px;
		text-align: left;
		position:fixed;
		left:20px;
		bottom:20px;
		height:30px;
		width:100%;
	}
	#block {
		display: inline-block;
	}
	table {
		border-collapse: collapse;
	}
	th {
		padding: 20 20 20 20;
	}
	[id^='rect'] {
		margin: 20 20 20 20;
		text-align: left;
		font-size: 120pt;
		font-family: Arial Black, Gadget, sans-serif;font-weight:normal;
		text-shadow: 5px 5px 5px #505050;
		color: #ffffff;
		margin-left:auto; 
		margin-right:auto;
	}
	.post-content {
		/*background: none repeat scroll 0 0 #000000;*/
		opacity: 0.8;
		margin: 0 auto;
		margin-top: -290px;
		margin-left: 100px;
		text-align:center;
		position: relative;
		width:40%;
	}
	table {
		margin-left:auto; 
		margin-right:auto;
	}
	#rect_row {
		margin-left:auto; 
		margin-right:auto;
	}
	

</style>
	<head>
		<title>Image recognition</title>
	</head>
	<body>
	<br>
	<br>
	<br>
	<br>

	<div id="header">
		Image recognition IoT project
	</div>
	<div id="header">
		Tomato vs Cucumber
	</div>

	<br>

	<div id="sub-header">
		Academic advisor: <span style="font-style:italic;">Danny Feldman, Ph.D.</span>
	</div>

	<table id="rect_col">
		<tr id="rect_row">
			<th class="thumbnail">
				<img src="tomato.png" width="80%" height="80%">
				<div class="caption post-content">
					<span id="redcount"></span>
				</div>
			</th>
			<th class="thumbnail">
				<img src="cucumber.png" width="80%" height="80%">
				<div class="caption post-content">
					<span id="greencount"></span>
				</div>
			</th>
		</tr>
		<!--
		<tr id="rect_blue">
			<th>Blue </th>
			<th id="bluecount"></th>
		</tr>
		-->
	</table>

	<div id="footer">
		Created by: Gilad Leshem and Ron Handler
	</div>

	<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
	<script>
		setInterval(function(){
			  $('#redcount').load('getred.php');
			  $('#greencount').load('getgreen.php');
			  $('#bluecount').load('getblue.php');
		},1000);

	</script>

	</body>
</html>

