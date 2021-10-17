--TEST--
Insert numeric values
--SKIPIF--
<?php
if (!extension_loaded('duckdbext')) {
    echo 'skip';
}
?>
--FILE--
<?php
$db         = new DuckDB\Database();
$connection = new DuckDB\Connection($db);
$connection->query("CREATE TABLE integers(i INTEGER, j INTEGER);");
$connection->query("INSERT INTO integers VALUES (30, 40), (50, 60), (70, NULL);");
$result = $connection->query("SELECT * FROM integers");

var_dump($result->toArray());
?>
--EXPECT--
array(3) {
  [0]=>
  array(2) {
    [0]=>
    string(2) "30"
    [1]=>
    string(2) "40"
  }
  [1]=>
  array(2) {
    [0]=>
    string(2) "50"
    [1]=>
    string(2) "60"
  }
  [2]=>
  array(2) {
    [0]=>
    string(2) "70"
    [1]=>
    string(4) "NULL"
  }
}
