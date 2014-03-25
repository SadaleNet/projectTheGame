<?php
	/*test.php: Test connection and setup
		Output: "It's working!" if the database is working.
	*/

	/*initialize stuffs*/
	include_once 'shared.php';
	if($_SERVER['REQUEST_METHOD'] == 'GET')
		$_POST = $_GET;

	/*fetch the requested user data*/
	$db = connectDatabase();
	echo "It's working!";
?>
