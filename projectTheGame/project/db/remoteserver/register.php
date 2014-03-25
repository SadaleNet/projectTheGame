<?php
	/*register.php: Register an account with the username and password given.
		Input: username, password
		Output: Success message or error message.
	*/

	/*initialize stuffs*/
	include_once 'shared.php';
	loadQueryString();

	/*Ensure that the username is available*/
	$db = connectDatabase();
	$count = queryOne($db, 'SELECT COUNT(*) FROM userData WHERE username == '.$db->quote($_POST['username']));
	if($count>0)
		error('Error: Username not available. :(');

	/*Register the user*/
	try{
		$db->exec('INSERT INTO userData (userName, password)
					VALUES(	'.$db->quote($_POST['username']).','.
					$db->quote(getHashedPassword()).');');
	}catch(Exception $e){
		error('Sorry, internal error occured.');
	}
	responseMessage('Account created!');
?>
