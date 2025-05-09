CXX = g++
CXXFLAGS = -std=c++17 -I. $(shell pkg-config --cflags eigen3)
LDFLAGS = $(shell pkg-config --libs eigen3) -llazycsv

TARGET = gauss_solver
TEST   = test

GAUSS_SRC = gauss.cpp
MAIN_SRC  = main.cpp
TEST_SRC  = test.cpp

all: $(TARGET)

$(TARGET): $(GAUSS_SRC) $(MAIN_SRC) gauss.hpp
	$(CXX) $(CXXFLAGS) -o $@ $(GAUSS_SRC) $(MAIN_SRC) $(LDFLAGS)

$(TEST): $(GAUSS_SRC) $(TEST_SRC) gauss.hpp
	$(CXX) $(CXXFLAGS) -o $@ $(GAUSS_SRC) $(TEST_SRC) $(LDFLAGS) -lgtest -lpthread

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(TARGET) $(TEST) result.csv

.PHONY: all test clean