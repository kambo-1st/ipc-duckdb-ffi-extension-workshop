<?php

// Start coding here...

/*
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "duckdb.h"

int main() {
    duckdb_database db;
    duckdb_connection con;

    if (duckdb_open(NULL, &db) == DuckDBError) {
        exit(1);
    }

    if (duckdb_connect(db, &con) == DuckDBError) {
        exit(1);
    }

    // run queries...
    duckdb_state state;
    duckdb_result result;

    // create a table
    state = duckdb_query(con, "CREATE TABLE integers(i INTEGER, j INTEGER);", NULL);
    if (state == DuckDBError) {
        exit(1);
    }

    // insert three rows into the table
    state = duckdb_query(con, "INSERT INTO integers VALUES (3, 4), (5, 6), (7, NULL);", NULL);
    if (state == DuckDBError) {
        exit(1);
    }

    // query rows again
    state = duckdb_query(con, "SELECT * FROM integers", &result);
    if (state == DuckDBError) {
        printf("%s", result.error_message);
        exit(1);
    }

    // print the above result
    for (idx_t row = 0; row < result.row_count; row++) {
        for (idx_t col = 0; col < result.column_count; col++) {
            char *str_val = duckdb_value_varchar(&result, col, row);
            printf("%s", str_val);

            duckdb_free(str_val);
        }
        printf("\n");
    }


    // destroy the result after we are done with it
    duckdb_destroy_result(&result);

    // cleanup
    duckdb_disconnect(&con);
    duckdb_close(&db);
}

*/

// Generate headers
// echo '#define FFI_LIB "./libduckdb.so"' >> duckdb-ffi.h
// cpp -P -C -D"__attribute__(ARGS)=" duckdb.h >> duckdb-ffi.h

// Memory leaks detections
// valgrind --leak-check=full php duckdb.php

// GDB
// gdb --args php duckdb.php
// source /data/php-src/.gdbinit
// (gdb) dump_bt executor_globals.current_execute_data
