#!/bin/bash
#for i in {0..1024..1}
for i in {0..512..1}
    do
        echo "$i"
        cp -a 11_float_test_base "11_float_test_$i"
        sed -i "s/MAX_DIV_BASE_VALUE/$i/g" "11_float_test_$i/src/NC.h"
    done
