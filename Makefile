com = g++
std = -std=c++17
flags = -g

output: main.cpp geometry.h
	$(com) $(std) main.cpp -o output.o
	./output.o

clean:
	rm output.o
