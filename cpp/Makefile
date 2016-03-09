CXX      = g++
CXXFLAGS = -std=c++14 -Wall -O3
LDFLAGS  =

TARGET = $(patsubst challenges/%.cpp,%,$(wildcard challenges/challenge-*.cpp))
CHAL_SRCS = $(wildcard challenges/*.cpp)
SRCS   = $(wildcard util/*.cpp)
OBJS   = $(SRCS:.cpp=.o)


.PHONY: clean all

all: $(TARGET)

challenge-%: $(OBJS) challenges/challenge-%.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

.SECONDARY: $(OBJS)