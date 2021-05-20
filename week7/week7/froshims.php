<!DOCTYPE html>

<html lang="en">
  
  <head>
    <meta charset="utf-8">
    <title>Frosh IMs</title>
    <link href="css/bootstrap/css/bootstrap.css" rel="stylesheet" />
	<link href="css/style.css" rel="stylesheet" />
    <script src="script.js"></script>
  </head>

  <body>
	  <h1>Register form for Frosh IMs</h1>
	  <form action="register-3.php" method="post">
	  
		  	<label>
		  		Name:
			  	<input name="name" type="text"/>
		  	</label>
	

	
		  	<label class="checkbox">
			  	<input name="captain" type="checkbox"/> Captain?
		  	</label>		 
		  	
	  	  	<label class="radio">
				<input name="gender" type="radio" value="F"/> Female
			</label>		 
			<label class="radio">
				<input name="gender" type="radio" value="M"/> Male
		  	</label>		 
		  	
		  	<label>
				Dorm:
		  	</label>
		  	
			<label class="select">  			 
				<select name="dorm">
					<option value=""></option>
					<option value="Apley Court">Apley Court</option>
					<option value="Canaday">Canaday</option>
					<option value="Grays">Grays</option>
				</select>
			</label>
			
			<label class="button">
				<input type="submit" value="Register">
			</label>
	  </form>
    <!-- page content -->
  </body>
  
</html>
