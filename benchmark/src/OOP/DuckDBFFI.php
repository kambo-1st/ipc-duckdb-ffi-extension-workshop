<?php declare(strict_types=1);

namespace Kambo\DuckDB\OOP;

use FFI;

/**
 *
 */
class DuckDBFFI
{
    private static $instance;

    public static function getInstance()
    {
        if (self::$instance === null) {
            self::$instance = FFI::load(__DIR__.DIRECTORY_SEPARATOR.'..'.DIRECTORY_SEPARATOR.'duckdb-ffi.h');
        }
        return self::$instance;
    }
}
