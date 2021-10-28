<?php declare(strict_types=1);

$ffi = FFI::cdef("struct tm {int tm_sec;};");

function dateTimeDefinition($ffi) {
    $timeFci = $ffi->new("struct tm");
    $timeFci->tm_sec = 10;
    var_dump($timeFci->tm_sec);
    $pointer = FFI::addr($timeFci);

    return $pointer;
}

$time = dateTimeDefinition($ffi);

var_dump($time->tm_sec); // Print rubbish value or crash
