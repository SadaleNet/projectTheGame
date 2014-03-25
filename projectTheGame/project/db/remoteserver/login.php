<?php
	/*login.php: Check whether the (username, password) pair is valid
		Input: username, password
		Output: If success, returns nothing. Returns error message else.
	*/

	/*initialize stuffs*/
	include_once 'shared.php';
	loadQueryString();

	/*check whether the login is valid*/
	$db = connectDatabase();
	$count = queryOne($db, 'SELECT COUNT(*) FROM userData WHERE username == '.$db->quote($_POST['username']).
							' AND password == '.$db->quote(getHashedPassword()));
	if($count!=1)
		error('Error: Login failed.');
?>
