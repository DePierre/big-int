CXX= gcc
#CCFLAGS= -Wall -Werror -pedantic -ansi
CCFLAGS= -Wall
INCLUDEDIR= -I. -I./include -I./src

all: test.out

test.out: src/utils.o src/DList.o src/BigInt.o test.o
	$(CXX) $(CCFLAGS) -o $@ $^

utils.o: utils.c
	$(CXX) $(CCFLAGS) $(INCLUDEDIR) -o $@ -c $<

DList.o: DList.c
	$(CXX) $(CCFLAGS) $(INCLUDEDIR) -o $@ -c $<

BigInt.o: BigInt.c
	$(CXX) $(CCFLAGS) $(INCLUDEDIR) -o $@ -c $<

test.o: test.c
	$(CXX) $(CCFLAGS) $(INCLUDEDIR) -o $@ -c $<

clean:
	rm -irf *.o src/*.o *~ src/*~ *.out
