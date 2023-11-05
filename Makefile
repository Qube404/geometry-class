com = clang++
std = -std=c++17
flags = -g

output: main.cpp geometry.h
	$(com) $(std) $(flags) main.cpp -o output.o
	./output.o

clean:
	rm output.o
