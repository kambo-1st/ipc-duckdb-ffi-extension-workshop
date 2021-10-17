/* duckdbext extension for PHP */

#ifndef PHP_DUCKDBEXT_H
# define PHP_DUCKDBEXT_H

extern zend_module_entry duckdbext_module_entry;
# define phpext_duckdbext_ptr &duckdbext_module_entry

# define PHP_DUCKDBEXT_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_DUCKDBEXT)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_DUCKDBEXT_H */
