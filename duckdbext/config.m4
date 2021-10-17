PHP_ARG_ENABLE([duckdbext],
  [whether to enable duckdbext support],
  [AS_HELP_STRING([--enable-duckdbext],
    [Enable duckdbext support])],
  [no])

if test "$PHP_DUCKDBEXT" != "no"; then
  SEARCH_PATH="/usr/local /usr"     # you might want to change this
  SEARCH_FOR="/lib/duckdb/duckdb.h"  # you most likely want to change this
  if test -r $PHP_DUCKDB/$SEARCH_FOR; then # path given as parameter
    DUCKDB_DIR=$PHP_DUCKDB
  else # search default path list
    AC_MSG_CHECKING([for duckdb files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        DUCKDB_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$DUCKDB_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the duckdb distribution])
  fi

  PHP_ADD_INCLUDE($DUCKDB_DIR/lib/duckdb/)

  PHP_ADD_LIBRARY_WITH_PATH(duckdb, $DUCKDB_DIR/lib/duckdb/, DUCKDBEXT_SHARED_LIBADD)
  PHP_SUBST(DUCKDBEXT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(duckdbext, duckdbext.c, $ext_shared)
fi
