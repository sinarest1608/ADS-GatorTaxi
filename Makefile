CXX=g++
CXXFLAGS=-std=c++11


gatorTaxi: gatorTaxi.cpp
	$(CXX) $(CXXFLAGS) -o gatorTaxi gatorTaxi.cpp

run:
	./gatorTaxi

