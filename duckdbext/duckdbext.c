/* duckdb extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "zend_exceptions.h"
#include "php_duckdbext.h"
#include "duckdbext_arginfo.h"
#include "duckdb.h"
#include "php_duckdbext_structs.h"
#include "ext/spl/spl_exceptions.h"
#include "zend_interfaces.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

static zend_class_entry *duckdb_database_ce = NULL;
static zend_class_entry *duckdb_connect_ce = NULL;
static zend_class_entry *duckdb_statementexception_ce = NULL;
static zend_class_entry *duckdb_result_ce = NULL;

static zend_object_handlers duckdb_database_handlers;
static zend_object_handlers duckdb_connection_object_handlers;
static zend_object_handlers duckdb_result_object_handlers;

static zend_object *php_database_object_new(zend_class_entry *class_type)
{
    php_duckdb_db_object *intern;

    /* Allocate memory for it */
    intern = zend_object_alloc(sizeof(php_duckdb_db_object), class_type);

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->zo.handlers = &duckdb_database_handlers;

    return &intern->zo;
}

static void php_database_object_free(zend_object *object)
{
    php_duckdb_db_object *intern = php_duckdb_database_from_obj(object);

    if (!intern) {
        return;
    }

    if (intern->db) {
        duckdb_close(&intern->db);
    }

    zend_object_std_dtor(&intern->zo);
}

PHP_METHOD(Database, __construct) {
    char *db_path = NULL;
    size_t db_path_len = 0;

    php_duckdb_db_object *db_obj;
    zval *object = ZEND_THIS;

    db_obj = Z_DUCKDATABASE_P(object);

    ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
        Z_PARAM_STRING(db_path, db_path_len)
    ZEND_PARSE_PARAMETERS_END();

    if (duckdb_open(db_path, &(db_obj->db)) == DuckDBError) {
        zend_throw_exception(zend_ce_exception, "Error during initialization", 0);
        RETURN_THROWS();
    }
}

static zend_object *php_connection_object_new(zend_class_entry *class_type)
{
    php_duckdb_connection_object *intern;

    /* Allocate memory for it */
    intern = zend_object_alloc(sizeof(php_duckdb_connection_object), class_type);

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->zo.handlers = &duckdb_connection_object_handlers;

    return &intern->zo;
}

static void php_connection_object_free(zend_object *object)
{
    php_duckdb_connection_object *intern = php_duckdb_connection_from_obj(object);

    if (!intern) {
        return;
    }

    if (intern->connection) {
        duckdb_disconnect(&intern->connection);
    }

    zend_object_std_dtor(&intern->zo);
}

PHP_METHOD(Connection, __construct) {
    php_duckdb_db_object *db_obj;
    zval *db_zval;
    zval *object = ZEND_THIS;
    php_duckdb_connection_object *connection_obj;

    connection_obj = Z_DUCK_CONNECTION_P(object);

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_OBJECT_OF_CLASS(db_zval, duckdb_database_ce)
    ZEND_PARSE_PARAMETERS_END();

    db_obj = Z_DUCKDATABASE_P(db_zval);

    if (duckdb_connect(db_obj->db, &(connection_obj->connection)) == DuckDBError) {
        // In v0.2.7 there is no possibility to obtain error message.
        zend_throw_exception(zend_ce_exception, "Error during initialization", 0);
        RETURN_THROWS();
    }
}

static zend_object *php_result_object_new(zend_class_entry *class_type)
{
    php_duckdb_result_object *intern;

    /* Allocate memory for it */
    intern = zend_object_alloc(sizeof(php_duckdb_result_object), class_type);

    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);

    intern->zo.handlers = &duckdb_result_object_handlers;

    return &intern->zo;
}

static void php_result_object_free(zend_object *object)
{
    php_duckdb_result_object *intern = php_duckdb_result_from_obj(object);

    if (!intern) {
        return;
    }

    if (intern->result) {
        duckdb_destroy_result(intern->result);
    }

    efree(intern->result);

    zend_object_std_dtor(&intern->zo);
}

PHP_METHOD(Connection, query)
{
    char *query      = NULL;
    size_t query_len = 0;

    zval *object = ZEND_THIS;
    php_duckdb_connection_object *connection_obj;
    php_duckdb_result_object *result_obj;

    duckdb_result *inner_result;
    inner_result = emalloc(sizeof(duckdb_result));
    inner_result->columns = NULL; // duckdb_query does not set inner_result.columns to NULL :-/
    inner_result->column_count = 0;
    inner_result->row_count = 0;

    connection_obj = Z_DUCK_CONNECTION_P(object);

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(query, query_len)
    ZEND_PARSE_PARAMETERS_END();

    object_init_ex(return_value, duckdb_result_ce);
    result_obj = Z_DUCK_RESULT_P(return_value);
    result_obj->result = inner_result;

    if (duckdb_query(connection_obj->connection, query, inner_result) == DuckDBError) {
        zend_throw_exception_ex(duckdb_statementexception_ce, 0, "%s", inner_result->error_message);
        duckdb_destroy_result(inner_result);

        RETURN_THROWS();
    }
}


PHP_METHOD(Result, __construct)
{

}

void duckdb_value_to_zval(duckdb_result *result, idx_t row, idx_t column, zval *data)
{
    char *val_s;
    val_s = duckdb_value_varchar(result, column, row);
    ZVAL_STRING(data, val_s);
    duckdb_free(val_s);
}

PHP_METHOD(Result, toArray)
{
    zval *object = ZEND_THIS;
    php_duckdb_result_object *result_obj;
    result_obj = Z_DUCK_RESULT_P(object);
    array_init(return_value);

    for (size_t row_idx = 0; row_idx < result_obj->result->row_count; row_idx++) {
        zval row;
        array_init(&row);

        for (size_t col_idx = 0; col_idx < result_obj->result->column_count; col_idx++) {
            zval data;
            duckdb_value_to_zval(result_obj->result, row_idx, col_idx, &data);
            add_index_zval(&row, col_idx, &data);
        }

        add_index_zval(return_value, row_idx, &row);
    }
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(duckdbext)
{
    #if defined(ZTS) && defined(COMPILE_DL_DUCKDB)
        ZEND_TSRMLS_CACHE_UPDATE();
    #endif

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(duckdbext)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "duckdb support", "enabled");
    php_info_print_table_end();
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(duckdbext)
{
    memcpy(&duckdb_database_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    memcpy(&duckdb_connection_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    memcpy(&duckdb_result_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));

    zend_class_entry duckdb_database_ce_local;
    INIT_NS_CLASS_ENTRY(duckdb_database_ce_local, "DuckDB","Database", class_Database_methods);
    duckdb_database_ce_local.create_object = php_database_object_new;
    duckdb_database_handlers.offset = XtOffsetOf(php_duckdb_db_object, zo);
    duckdb_database_handlers.clone_obj = NULL;
    duckdb_database_handlers.free_obj = php_database_object_free;
    duckdb_database_ce = zend_register_internal_class(&duckdb_database_ce_local);
    duckdb_database_ce->serialize = zend_class_serialize_deny;
    duckdb_database_ce->unserialize = zend_class_unserialize_deny;

    zend_class_entry duckdb_connect_ce_local;
    INIT_NS_CLASS_ENTRY(duckdb_connect_ce_local, "DuckDB","Connection", class_Connection_methods);
    duckdb_connect_ce_local.create_object = php_connection_object_new;
    duckdb_connection_object_handlers.offset = XtOffsetOf(php_duckdb_connection_object, zo);
    duckdb_connection_object_handlers.clone_obj = NULL;
    duckdb_connection_object_handlers.free_obj = php_connection_object_free;
    duckdb_connect_ce = zend_register_internal_class(&duckdb_connect_ce_local);
    duckdb_connect_ce->serialize = zend_class_serialize_deny;
    duckdb_connect_ce->unserialize = zend_class_unserialize_deny;

    zend_class_entry duckdb_statementexception_ce_local;
    INIT_NS_CLASS_ENTRY(duckdb_statementexception_ce_local, "DuckDB","StatementException", NULL);
    duckdb_statementexception_ce = zend_register_internal_class_ex(&duckdb_statementexception_ce_local, spl_ce_RuntimeException);

    zend_class_entry duckdb_result_ce_local;
    INIT_NS_CLASS_ENTRY(duckdb_result_ce_local, "DuckDB","Result", class_Result_methods);
    duckdb_result_ce_local.create_object = php_result_object_new;
    duckdb_result_object_handlers.offset = XtOffsetOf(php_duckdb_result_object, zo);
    duckdb_result_object_handlers.clone_obj = NULL;
    duckdb_result_object_handlers.free_obj = php_result_object_free;
    duckdb_result_ce = zend_register_internal_class(&duckdb_result_ce_local);
    duckdb_result_ce->serialize = zend_class_serialize_deny;
    duckdb_result_ce->unserialize = zend_class_unserialize_deny;
    duckdb_result_ce->ce_flags |= ZEND_ACC_FINAL;

    return SUCCESS;
}
/* }}} */

/* {{{ duckdbext_module_entry */
zend_module_entry duckdbext_module_entry = {
        STANDARD_MODULE_HEADER,
        "duckdbext",			   /* Extension name */
        NULL,				       /* zend_function_entry */
        PHP_MINIT(duckdbext),	   /* PHP_MINIT - Module initialization */
        NULL,	                   /* PHP_MSHUTDOWN - Module shutdown */
        PHP_RINIT(duckdbext),	   /* PHP_RINIT - Request initialization */
        NULL,	                   /* PHP_RSHUTDOWN - Request shutdown */
        PHP_MINFO(duckdbext),	   /* PHP_MINFO - Module info */
        PHP_DUCKDBEXT_VERSION,	   /* Version */
        STANDARD_MODULE_PROPERTIES
};
/* }}} */


#ifdef COMPILE_DL_DUCKDBEXT
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(duckdbext)
#endif