#!/usr/bin/env bash

cmake -G "MSYS Makefiles" -DCMAKE_C_COMPILER="${CC}" -DCMAKE_CXX_COMPILER="${CXX}" -DCOVERAGE=ON ${BUILD_ARGS} ..
