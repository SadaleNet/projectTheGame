<?php
	/*fetch.php: Fetch user data/score
		Input: username, password, (score: optional)
		Output: If $_POST['score'] is set, returns score. return data else.
	*/

	/*initialize stuffs*/
	include_once 'shared.php';
	loadQueryString();

	/*fetch the requested user data*/
	$db = connectDatabase();
	require('login.php'); //ensure that the login is valid
	$fetched = queryOne($db, 'SELECT '.( isset($_POST['score'])?'score':'data' ).
							' FROM userData WHERE username == '.$db->quote($_POST['username']).
							' AND password == '.$db->quote(getHashedPassword()));
	responseMessage($fetched);
?>
