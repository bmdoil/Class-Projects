CXX = g++
CXXFLAGS = -g
CXXFLAGS += -std=c++11

all : merge4 merge4Time

merge4 : merge4.o
	$(CXX) $(CXXFLAGS) merge4.cpp -o merge4
merge4Time : merge4Time.o
	$(CXX) $(CXXFLAGS) merge4Time.cpp -o merge4Time
clean :
	rm *.o
	rm merge4
	rm merge4Time
	rm merge4.txt
