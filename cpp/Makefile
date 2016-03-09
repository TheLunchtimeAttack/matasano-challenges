CC=g++
CFLAGS=-std=c++14 -Wall
LDFLAGS=
LIBHEADERS:=$(shell echo util/*.h)
LIBS:=$(shell echo util/*.cpp)
LIBOUTS=$(LIBS:.cpp=.o)
EXECUTABLE:=$(shell ls challenges/challenge-*.cpp | sed 's/.cpp//' | sed 's/challenges\///')
CHALLENGES:=$(shell echo challenges/challenge-*.cpp)
CHALLENGEOUT=$(CHALLENGES:.cpp=.o)
RM=rm -f

new: clean all

all:
	$(MAKE) $(EXECUTABLE)

%: challenges/%.o $(LIBHEADERS) $(LIBOUTS)
	$(CC) $(CFLAGS) $< $(LIBOUTS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(LIBOUTS) $(CHALLENGEOUT) $(EXECUTABLE)

rm-exec:
	$(RM) $(EXECUTABLE)

