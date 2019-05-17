All: bin/parallel_sort_v3 bin/parallel_sort_v2 bin/parallel_sort_v1 bin/serial_sort #bin/parallel bin/serial

flags = g++ -Wall -Werror -std=c++11
parallel = -fopenmp -lm
debug = -g -pg

bin/parallel_sort_v3: build/tests.o build/parallel_sort_v3.o
	$(flags) $(parallel) build/tests.o build/parallel_sort_v3.o -o bin/parallel_sort_v3

build/parallel_sort_v3.o: src/parallel_sort_v3.cpp
	$(flags) $(parallel) -c src/parallel_sort_v3.cpp -o build/parallel_sort_v3.o

bin/parallel_sort_v2: build/tests.o build/parallel_sort_v2.o
	$(flags) $(parallel) build/tests.o build/parallel_sort_v2.o -o bin/parallel_sort_v2

build/parallel_sort_v2.o: src/parallel_sort_v2.cpp
	$(flags) $(parallel) -c src/parallel_sort_v2.cpp -o build/parallel_sort_v2.o

bin/parallel_sort_v1: build/tests.o build/parallel_sort_v1.o
	$(flags) $(parallel) build/tests.o build/parallel_sort_v1.o -o bin/parallel_sort_v1

build/parallel_sort_v1.o: src/parallel_sort_v1.cpp
	$(flags) $(parallel) -c src/parallel_sort_v1.cpp -o build/parallel_sort_v1.o

bin/serial_sort: build/serial_sort.o build/tests.o
	$(flags) $(parallel) build/serial_sort.o build/tests.o -o bin/serial_sort

build/serial_sort.o: src/serial_sort.cpp
	$(flags) $(parallel) -c src/serial_sort.cpp -o build/serial_sort.o

build/tests.o: src/tests.cpp
	$(flags) -c src/tests.cpp -o build/tests.o

bin/parallel: build/parallel.o
	$(flags) $(parallel) build/parallel.o -o bin/parallel

build/parallel.o: src/sum/parallel.cpp
	$(flags) $(parallel) -c src/sum/parallel.cpp -o build/parallel.o

bin/serial: build/serial.o
	$(flags) $(parallel) build/serial.o -o bin/serial

build/serial.o: src/sum/serial.cpp
	$(flags) $(parallel) -c src/sum/serial.cpp -o build/serial.o

clean: 
	rm -rf build/* bin/*