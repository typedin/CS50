<?php 
	
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
		die($mail->ErrInfo);
	}
	else
	{
		print("Mail send\n");
	}
?>
