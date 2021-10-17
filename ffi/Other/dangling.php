<?php declare(strict_types=1);

$ffi = FFI::cdef("struct tm {int tm_sec;};");

function dateTimeDefinition($ffi) {
    $time = $ffi->new("struct tm");
    $time->tm_sec = 10;
    var_dump($time->tm_sec);
    return FFI::addr($time);
}

$time = dateTimeDefinition($ffi);

var_dump($time->tm_sec); // Print rubbish value or crash
