<?php
	/*highscores.php: Show high score board
		Input: (limit: optional, default: 10), (padding: optional, default: 20)
		Output: A high score table.
	*/

	/*initialize stuffs*/
	include_once 'shared.php';
	if($_SERVER['REQUEST_METHOD'] == 'GET')
		$_POST = $_GET;
	if(!isset($_POST['limit']))
		$_POST['limit'] = 10;
	if(!isset($_POST['padding']))
		$_POST['padding'] = 20;

	/*fetch the requested user data*/
	$db = connectDatabase();
	$fetched = $db->query("SELECT username, score FROM userData WHERE score > 0 ORDER BY score DESC LIMIT {$_POST['limit']}");

	$responseMessage = '';
	$responseMessage .= str_pad('Username', $_POST['padding']).'Score'."\n";

	foreach($fetched as $row){
		$responseMessage .= str_pad($row['username'], $_POST['padding']).$row['score']."\n";
	}

	if(count($fetched)==0)
		error('No highscore is set. Be the first one to set a highscore!');

	responseMessage($responseMessage);
?>
