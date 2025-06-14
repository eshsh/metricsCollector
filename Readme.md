## Description

The library is designed to collect metrics. You can add your own metrics, for example, in the *include/statistics* directory. At the moment, the current metrics are an example. The output of the metrics is currently written to a file or to the console. The output of metrics can be redefined, for example in *examples/custom_logger*.

## OS
Ubuntu 22.04

## Compiler Requirements

GCC version 11.0.4 or newer

Clang version 21.0.0 or newer

## Build
    mkdir build && cd build
    cmake -S ..
    make
    make install


