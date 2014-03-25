<?php
	/*deregister.php: Deregister an account with the username and password given.
		Input: username, password
		Output: Success message or error message.
	*/

	/*initialize stuffs*/
	include_once 'shared.php';
	loadQueryString();


	$db = connectDatabase();
	require('login.php'); //ensure that the login is valid

	/*Deregister the user*/
	try{
		$db->exec('DELETE FROM userData WHERE username == '.$db->quote($_POST['username']).
					' AND password == '.$db->quote(getHashedPassword()));
	}catch(Exception $e){
		error('Sorry, internal error occured.');
	}
	responseMessage('Account removed!');
?>
