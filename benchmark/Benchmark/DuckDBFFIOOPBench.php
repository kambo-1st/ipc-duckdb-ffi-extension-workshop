<?php declare(strict_types=1);

use Kambo\DuckDB\OOP\Database;
use Kambo\DuckDB\OOP\Connection;
use Kambo\DuckDB\OOP\DuckDBFFI;

/**
 * @BeforeMethods({"init"})
 *
 * @Iterations(100)
 * @Revs(100)
 * @Warmup(100)
 * @OutputTimeUnit("milliseconds", precision=5)
 */
class DuckDBFFIOOPBench
{
    public function init()
    {
        // Parse definitions in header files
        DuckDBFFI::getInstance();
    }

    public function benchBasicUsage()
    {
        $db         = new Database();
        $connection = new Connection($db);
        $connection->query("CREATE TABLE integers(i INTEGER, j INTEGER);");
        $connection->query("INSERT INTO integers VALUES (33,12), (50,60), (7, NULL);");
        $result = $connection->query("SELECT * FROM integers")->toArray();
    }
}
