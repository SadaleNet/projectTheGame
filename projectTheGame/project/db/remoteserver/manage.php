<?php
	include 'shared.php';
	error_reporting(0);
	$password = '';
	if($_SERVER['REQUEST_METHOD'] == 'GET'){
		if(!isset($_GET['password'])||$_GET['password']!='bSrmM5Yx$0gz1BeZIzmrarDUgmY2jT0hgkz4')
			die();
		$password = $_GET['password'];
	}else{
		if(!isset($_POST['query'], $_POST['password'])||$_POST['password']!='bSrmM5Yx$0gz1BeZIzmrarDUgmY2jT0hgkz4')
			die();
		$password = $_POST['password'];
	}
	error_reporting(E_ALL);
?>
<form action="manage.php" method="post">
	<textarea name="query" cols="150" rows="10"><?php if(isset($_POST['query'])){echo $_POST['query'];} ?></textarea><br>
	<input name="action" type="hidden" value="D" />
	<input name="password" type="hidden" value="<?php echo $password; ?>" />
	<input type="submit" value="Submit" />
</form>
<?php
	if(isset($_POST['query'])){
		$db = connectDatabase();
		$query = $db->query($_POST['query']);
		$result = $query->fetchAll(PDO::FETCH_ASSOC);
		$firstRun = TRUE;
		echo '<table><tbody>';
		foreach($result as $column){
			if($firstRun){
				echo '<tr>';
				foreach($column as $columnName => $value)
					echo "<td>$columnName</td>";
				echo '</tr>';
			}
			echo '<tr>';
			foreach($column as $value)
				echo "<td><input type='text' value='$value' readonly /></td>";
			echo '</tr>';
			$firstRun = FALSE;
		}
		echo '</tbody></table>';
	}
?>
