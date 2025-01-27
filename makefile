
FLAGS = -O3 -march=native -funroll-loops -ftree-vectorize -flto

program: main.cpp Graph.cpp UF.cpp
	g++ $(FLAGS) -o program main.cpp Graph.cpp UF.cpp

clean:
	rm -f program