<?php declare(strict_types=1);

use Kambo\DuckDB\DuckDBFFIProcedural;

/**
 * @Iterations(100)
 * @Revs(100)
 * @Warmup(100)
 * @OutputTimeUnit("milliseconds", precision=5)
 */
class DuckDBFFIProceduralBench
{
    public function benchBasicUsage()
    {
        $duckDBFFIProcedural = new DuckDBFFIProcedural();
        $duckDBFFIProcedural->parseDefinitions();

        $result = $duckDBFFIProcedural->getData();
    }
}
