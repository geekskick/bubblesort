# bubblesort
I did this as a kata of sorts - to get in the zone with TDD techniques and using tools. I also have been learning Java and wanted to use it for something. 

## Prerequisites
* maven
* java 8
* c++11
* cmake
* conan

## Build and run bubblesort benchmark
```bash
mkdir build && cd build
conan install ..
cmake ..
make
./bin/bubblebenchmark --benchmark_out=../benchmark.json --benchmark_out_format=json
```

## Plot the results
```bash
cd plotter/speed_plotter
mvn clean compile assembly:single
java -cp target/speed_plotter-1.0-jar-with-dependencies.jar bubblesort.App ../../benchmark_out.json
```
