#ifndef DUCKDB_PHP_DUCKDBEXT_STRUCTS_H
#define DUCKDB_PHP_DUCKDBEXT_STRUCTS_H

#include "duckdb.h"

/* Structure for duckdb Database object. */
typedef struct _php_duckdb_db_object  {
    duckdb_database db;
    zend_object zo;
} php_duckdb_db_object;

static inline php_duckdb_db_object *php_duckdb_database_from_obj(zend_object *obj) {
    return (php_duckdb_db_object*)((char*)(obj) - XtOffsetOf(php_duckdb_db_object, zo));
}

#define Z_DUCKDATABASE_P(zv) ((php_duckdb_db_object*)((char*)(Z_OBJ_P(zv)) - XtOffsetOf(php_duckdb_db_object, zo)))

/* Structure for duckdb Connection struct. */
typedef struct _php_duckdb_connection_object  {
    duckdb_connection connection;
    zend_object zo;
} php_duckdb_connection_object;

static inline php_duckdb_connection_object *php_duckdb_connection_from_obj(zend_object *obj) {
    return (php_duckdb_connection_object*)((char*)(obj) - XtOffsetOf(php_duckdb_connection_object, zo));
}

#define Z_DUCK_CONNECTION_P(zv) ((php_duckdb_connection_object*)((char*)(Z_OBJ_P(zv)) - XtOffsetOf(php_duckdb_connection_object, zo)))

/* Structure for duckdb Result struct. */
typedef struct _php_duckdb_result_object  {
    duckdb_result *result;
    zend_object zo;
} php_duckdb_result_object;

static inline php_duckdb_result_object *php_duckdb_result_from_obj(zend_object *obj) {
    return (php_duckdb_result_object*)((char*)(obj) - XtOffsetOf(php_duckdb_result_object, zo));
}

#define Z_DUCK_RESULT_P(zv) ((php_duckdb_result_object*)((char*)(Z_OBJ_P(zv)) - XtOffsetOf(php_duckdb_result_object, zo)))

#endif //DUCKDB_PHP_DUCKDBEXT_STRUCTS_H
