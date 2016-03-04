CC=g++
CFLAGS=-std=c++14 -c -Wall
LDFLAGS=
LIBHEADERS:=$(shell ls util/*.h)
LIBS:=$(shell ls util/*.cpp)
LIBOUT=$(LIBS:.cpp=.o)
EXECUTABLE:=$(shell ls challenges/challenge-*.cpp | sed 's/.cpp//' | sed 's/challenges\///')
CHALLENGES:=$(shell ls challenges/challenge-*.cpp)
CHALLENGEOUT=$(CHALLENGES:.cpp=.o)
RM=rm -f

new: clean all

all: $(LIBHEADERS) $(LIBS) $(CHALLENGES) $(EXECUTABLE)

$(EXECUTABLE): $(LIBHEADERS) $(LIBOUT) $(CHALLENGEOUT)
	$(CC) $(LDFLAGS) challenges/$@.o $(LIBOUT) -o $@

.cpp:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(LIBOUT) $(CHALLENGEOUT) $(EXECUTABLE)

rm-exec:
	$(RM) $(EXECUTABLE)

