CXX = g++
CXXFLAGS = -std=c++17 -I. -I/usr/include/eigen3
LDFLAGS = -lgtest -lpthread

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
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(TEST_BIN) result.csv

.PHONY: all run_tests clean