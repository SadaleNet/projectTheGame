<?php
	/*This file stores functions used by all other .php files in this project.*/
	$DEBUG_MODE = TRUE;
	if($DEBUG_MODE){
		ini_set('display_errors', 1);
		error_reporting(E_ALL);
		function assertCallback($file, $line, $code){
			die("Assertion failed: $file:$line");
		}
		assert_options(ASSERT_CALLBACK, 'assertCallback');
	}else{
		ini_set('display_errors', 0);
	}

	/*misc functions*/
	function getHashedPassword(){
		return sha1($_POST['username'].$_POST['password']);
	}

	/*return an message and terminate the script.
	 * This function is intended to give a better name to die() because die() seems like an error.
	*/
	function responseMessage($str){
		die($str);
	}
	/*return an error message, set the HTTP status to 400 and terminate the script.*/
	function error($msg){
		header('HTTP/1.1 400 Bad Request', true, 400);
		die($msg);
	}
	/*Initialize data before processing the request.*/
	function loadQueryString(){
		/*Basic cheat detection: User-Agent HTTP header is provided by most browser. This can prevent user make query with his browser.*/
		if(isset($_SERVER['HTTP_USER_AGENT']))
			error("Cheat detected. Warning: If you do this again, you will be banned."); //scare the user. In fact, this system have no banning mechism at all! :P
		/*Makes GET behaves as POST*/
		if($_SERVER['REQUEST_METHOD'] == 'GET')
			$_POST = $_GET;
		/*Ensure that username and password are set*/
		if(!isset($_POST['username'], $_POST['password']))
			error('Error: invalid query string');
	}

	/*database functions*/
	function connectDatabase(){
		$ret = new PDO('sqlite:database.sqlite');
		$ret->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		return $ret;
	}
	function queryOne($db, $str){
		$query = $db->query($str);
		$fetchedQuery = $query->fetch(PDO::FETCH_NUM);
		return $fetchedQuery[0];
	}
?>
