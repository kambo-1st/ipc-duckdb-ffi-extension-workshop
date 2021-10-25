<?php declare(strict_types=1);

$ffi = FFI::cdef(
    'int abs(int j);
    long int labs(long int j);',
    'libc.so.6'
);

var_dump($ffi->abs(-42));          // int(42)
var_dump($ffi->abs(-2147483649));  // int(2147483647)
var_dump($ffi->labs(-2147483649)); // int(2147483649)
