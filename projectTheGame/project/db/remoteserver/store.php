<?php
	/*store.php: store user score/data to database
		Input: username, password, (optional:score), content
		Output: If error occurs, returns error message. Else, returns nothing.
		If score is set, the content will be stored as score. Will be stored as data else.
	*/

	/*initialize stuffs*/
	include_once 'shared.php';
	loadQueryString();
	if(!isset($_POST['content']))
		error('Error: Invalid query string.');

	/*fetch the requested user data*/
	$db = connectDatabase();
	require('login.php'); //ensure that the login is valid
	$fetched = queryOne($db, 'UPDATE userdata SET '.
								( isset($_POST['score'])?'score':'data' ).' = '.$db->quote($_POST['content']).
							' WHERE username == '.$db->quote($_POST['username']).
							' AND password == '.$db->quote(getHashedPassword()));
?>
