<!DOCTYPE html>

<html lang="en">
  
	<head>
		<meta charset="utf-8">
		<title>Frosh IMs</title>
	</head>

	<body>
		<pre>
			<?php 
								
				if(!($_POST["name"]))
				{
					echo("you must provide a name\n");
					header("Location: /froshims.php");
					die;
				}
				if(!($_POST["gender"]))
				{
					echo("you must provide a gender\n");
					header("Location: /froshims.php");
					die;
				}
				if(!($_POST["dorm"]))
				{
					echo("you must provide a dorm\n");
					header("Location: /froshims.php");
					die;
				}
	
				if ($_POST["name"] && $_POST["gender"] && $_POST["dorm"])
				{
					require("PHPMailer/class.phpmailer.php");
					$mail = new PHPMailer();
	
					$mail->IsSMTP();
	
					$mail->Host = "smtp.free.fr";
	
					$mail->SetFrom = ("antoinecheynet@free.fr");
	
					$mail->AddAddress = ("antoinecheynet@free.fr");
	
					$mail->Subject = "registration";
	
					$mail->body = 
					"This person just registered:\n" . 
					"Name: ". $_POST["name"] . "\n" .
					"Captain: ". $_POST["captain"] . "\n" .
					"Gender: ". $_POST["gender"] . "\n" .
					"Dorm: ". $_POST["dorm"] . "\n";
	
					if($mail->Send() == false)
					{
						print("ERROR\n");
						die($mail->ErrInfo);
					}
					else
					{
						print("Mail send\n");
					}
				}
			?>
	  	</pre>
	</body>
  
</html>

