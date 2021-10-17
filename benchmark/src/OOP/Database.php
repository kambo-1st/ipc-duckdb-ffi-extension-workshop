<?php declare(strict_types=1);

namespace Kambo\DuckDB\OOP;

/**
 *
 */
class Database
{
    private $database;

    public function __construct(?string $name=null) {
        $duckDBFFI = DuckDBFFI::getInstance();
        $this->database = $duckDBFFI->new("duckdb_database");
        $result = $duckDBFFI->duckdb_open($name, \FFI::addr($this->database));

        if ($result === $duckDBFFI->DuckDBError) {
            throw new \Exception('Cannot open database');
        }

    }

    public function toInternalDataStructure() {
        return $this->database;
    }

    public function __destruct() {
        DuckDBFFI::getInstance()->duckdb_close(\FFI::addr($this->database));
    }
}
