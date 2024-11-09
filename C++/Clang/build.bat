mkdir bin
clang++ -std=c++11 -O3 -flto -DWIN32_CLANG Clang.cpp -o ./bin/Benchmark