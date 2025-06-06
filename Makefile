CXX = g++
CXXFLAGS = -std=c++17 -I. -I/opt/homebrew/opt/eigen/include/eigen3 -I/opt/homebrew/opt/googletest/include
LDFLAGS = -L/opt/homebrew/opt/googletest/lib

TARGET = gauss_solver
TEST_BIN = test

GAUSS_SRCS = gauss.cpp main.cpp
TEST_SRCS = gauss.cpp test.cpp

all: $(TARGET)

$(TARGET): gauss.h $(GAUSS_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(GAUSS_SRCS) $(LDFLAGS)

run_tests: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): gauss.h $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_SRCS) $(LDFLAGS) -lgtest -lpthread

clean:
	rm -f $(TARGET) $(TEST_BIN) result.csv

.PHONY: all run_tests clean