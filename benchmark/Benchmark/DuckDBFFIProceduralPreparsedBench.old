<?php declare(strict_types=1);

use Kambo\DuckDB\DuckDBFFIProcedural;

/**
 * @BeforeMethods({"init"})
 * @Iterations(100)
 * @Revs(100)
 * @Warmup(100)
 * @OutputTimeUnit("milliseconds", precision=5)
 */
class DuckDBFFIProceduralPreparsedBench
{
    private DuckDBFFIProcedural $DuckDBFFIProcedural;

    public function init()
    {
        $this->DuckDBFFIProcedural = new DuckDBFFIProcedural();
        $this->DuckDBFFIProcedural->parseDefinitions();
    }

    public function benchBasicUsage()
    {
        $result = $this->DuckDBFFIProcedural->getData();
    }
}
