<?php

/** @generate-function-entries */

/**
 * Represents a DuckDB database
 */
class Database {
    /**
     * Instantiates an Database object
     *
     * @param string|null $file Path to the DuckDB database. If filename is null, then a in memory database will be created.
     */
    public function __construct(?string $file = null) {}
}

// /**
//  * Represents a connection to DuckDB database
//  */
// class Connection {
//   /**
//    * Instantiates a Connection object
//    *
//    * @param DuckDB\Database $database A database to which we want to connect
//    */
//    public function __construct(DuckDB\Database $database) {}
//
//    /**
//     * Executes an SQL query, returning a Result object. If the query does not yield a result
//     * (such as DML statements) the returned Result object is not really usable.
//     *
//     * @param string $query The SQL query to execute.
//     *
//     * @return DuckDB\Result
//     */
//    public function query(string $query) : DuckDB\Result {}
// }
//
// /**
//  * Represents a query result
//  */
// class Result {
//     private function __construct() {}
//     /**
//      * Transform result with all rows to an associative or numerically indexed array or both
//      *
//      * @return array
//      */
//     public function toArray() : array {}
// }
