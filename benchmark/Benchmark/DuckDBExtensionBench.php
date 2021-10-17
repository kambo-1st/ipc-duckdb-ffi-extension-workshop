<?php declare(strict_types=1);

/**
 * @Iterations(100)
 * @Revs(100)
 * @Warmup(100)
 * @OutputTimeUnit("milliseconds", precision=5)
 */
class DuckDBExtensionBench
{
    public function benchBasicUsage()
    {
        $db         = new \DuckDB\Database();
        $connection = new \DuckDB\Connection($db);
        $connection->query("CREATE TABLE integers(i INTEGER, j INTEGER);");
        $connection->query("INSERT INTO integers VALUES (33,12), (50,60), (7, NULL);");
        $result = $connection->query("SELECT * FROM integers")->toArray();
    }
}
