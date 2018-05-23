simd.p5.o:	simd.p5.h  simd.p5.cpp
		g++  -c  simd.p5.cpp -o simd.p5.o

project5:	project5.cpp simd.p5.o
		g++  -o project5  project5.cpp simd.p5.o  -lm  -fopenmp -g