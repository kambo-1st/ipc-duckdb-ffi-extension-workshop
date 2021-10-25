--TEST--
DuckDB\Result should not be created without calling constructor
--SKIPIF--
<?php
if (!extension_loaded('duckdbext')) {
    echo 'skip';
}
?>
--FILE--
<?php
$class = new ReflectionClass(DuckDB\Result::class);
try {
    var_dump($class->newInstanceWithoutConstructor());
} catch (ReflectionException $e) {
    echo $e->getMessage(), "\n";
}

?>
--EXPECT--
Class DuckDB\Result is an internal class marked as final that cannot be instantiated without invoking its constructor