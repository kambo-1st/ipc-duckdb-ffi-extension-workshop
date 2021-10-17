--TEST--
Check if duckdbext is loaded
--SKIPIF--
<?php
if (!extension_loaded('duckdbext')) {
    echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "duckdbext" is available';
?>
--EXPECT--
The extension "duckdbext" is available
