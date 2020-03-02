cmake -B build -G "NMake Makefiles" -DENABLE_TESTS=ON
cd build
nmake
cd ..