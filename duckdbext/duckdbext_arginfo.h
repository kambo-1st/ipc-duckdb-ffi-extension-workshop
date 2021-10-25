/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 330ca1c19c7fcb488c980c0939ab91fa53476801 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Database___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, file, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Connection___construct, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, database, DuckDB\\Database, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Connection_query, 0, 1, DuckDB\\Result, 0)
	ZEND_ARG_TYPE_INFO(0, query, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Result___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Result_toArray, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()


ZEND_METHOD(Database, __construct);
ZEND_METHOD(Connection, __construct);
ZEND_METHOD(Connection, query);
ZEND_METHOD(Result, __construct);
ZEND_METHOD(Result, toArray);


static const zend_function_entry class_Database_methods[] = {
	ZEND_ME(Database, __construct, arginfo_class_Database___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Connection_methods[] = {
	ZEND_ME(Connection, __construct, arginfo_class_Connection___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Connection, query, arginfo_class_Connection_query, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_Result_methods[] = {
	ZEND_ME(Result, __construct, arginfo_class_Result___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Result, toArray, arginfo_class_Result_toArray, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
