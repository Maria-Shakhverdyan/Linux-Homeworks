CXX = g++
CXXFLAGS = -std=c++11

all: complex_sort

complex_sort: main.o ComplexNum.o
	$(CXX) $(CXXFLAGS) -o complex_sort main.o ComplexNum.o

main.o: main.cpp ComplexNum.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

ComplexNum.o: ComplexNum.cpp ComplexNum.hpp
	$(CXX) $(CXXFLAGS) -c ComplexNum.cpp

clean:
	rm -f complex_sort main.o ComplexNum.o
