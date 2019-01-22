CXX = g++
CXXFLAGS = -g
CXXFLAGS += -std=c++11

all : insertsort mergesort insertTime mergeTime

insertsort : insertsort.o 
	$(CXX) $(CXXFLAGS) insertsort.cpp -o insertsort
mergesort : mergesort.o
	$(CXX) $(CXXFLAGS) mergesort.cpp -o mergesort
insertTime : insertSortTiming.o
	$(CXX) $(CXXFLAGS) insertSortTiming.cpp -o insertTime
mergeTime : mergeSortTiming.o
	$(CXX) $(CXXFLAGS) mergeSortTiming.cpp -o mergeTime
clean :
	rm *.o
	rm insertsort
	rm mergesort
	rm insertTime
	rm mergeTime
	rm insert.txt
	rm merge.txt
