<?php declare(strict_types=1);

namespace Kambo\DuckDB\OOP;

/**
 *
 */
class Connection
{
    private $connection;

    public function __construct(Database $database) {
        $duckDBFFI = DuckDBFFI::getInstance();
        $this->connection = $duckDBFFI->new("duckdb_connection");
        $result = $duckDBFFI->duckdb_connect(
            $database->toInternalDataStructure(),
            \FFI::addr($this->connection)
        );

        if ($result === $duckDBFFI->DuckDBError) {
            throw new \Exception('Cannot connect to database');
        }
    }

    public function query(string $query) : Result {
        $duckDBFFI = DuckDBFFI::getInstance();
        $resultObject = new Result();

        $result = $duckDBFFI->duckdb_query(
            $this->connection,
            $query,
            \FFI::addr($resultObject->toInternalDataStructure())
        );

        if ($result === $duckDBFFI->DuckDBError) {
            throw new \Exception(\FFI::string($resultObject->toInternalDataStructure()->error_message));
        }

        return $resultObject;
    }

    public function __destruct() {
        DuckDBFFI::getInstance()->duckdb_disconnect(\FFI::addr($this->connection));
    }
}
