echo `which gcc`
echo `which g++`
cmake -DCMAKE_C_COMPILER="${CC}" -DCMAKE_CXX_COMPILER="${CXX}" -DCOVERAGE=ON ${BUILD_ARGS} ..
