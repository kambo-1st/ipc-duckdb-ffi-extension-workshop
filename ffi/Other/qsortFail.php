<?php declare(strict_types=1);

$ffi = FFI::cdef(
    "void qsort (
        void *array,
        size_t count,
        size_t size,
        int (*comp) (const void *a, const void *b)
    );",
    "libc.so.6"
);



$cmp = function (FFI\CData $a, FFI\CData $b) {
    $aInt = FFI::cast("int", $a)->cdata;
    $bInt = FFI::cast("int", $b)->cdata;

    if ($aInt === $bInt) { return 0;}
    return ($aInt < $bInt) ? -1 : 1;
};

$array = [2,3,1];
$ffi->qsort($array, count($array), FFI::sizeof(FFI::type("int")), $cmp);

var_dump($array);
