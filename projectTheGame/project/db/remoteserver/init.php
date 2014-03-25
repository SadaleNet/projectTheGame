<?php
	/*init.php: Database creation script
		Input: password
		Output: 'Done.' is the database is initialized
	*/

	/*initialize stuffs*/
	include_once 'shared.php';
	error_reporting(0);
	if(file_exists('database.sqlite')||!isset($_GET['password'])||$_GET['password']!='bSrmM5Yx$0gz1BeZIzmrarDUgmY2jT0hgkz4')
		die();

	//create database
	$db = connectDatabase();
	$db->exec(<<<HEREDOC
		PRAGMA foreign_keys = ON;
		BEGIN TRANSACTION;
			CREATE TABLE userData (
				username TEXT PRIMARY KEY NOT NULL,
				password TEXT NOT NULL,
				score INTEGER NOT NULL DEFAULT 0,
				data TEXT
			);
		COMMIT;
HEREDOC
	);
	echo 'Done.';
?>
