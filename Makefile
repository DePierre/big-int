CXX= gcc
CCFLAGS= -Wall -Werror -pedantic -ansi

INCLUDE= ./include
SRC= ./src
INCLUDEDIR= -I. -I$(INCLUDE) -I$(SRC)

LIB= ./lib
LIBDIR= -L$(LIB)

TARGET= test.out

SOURCES= $(SRC)/utils test
OBJECTSFILES= $(SOURCES:=.o)

all: $(TARGET)

lib: $(LIB)/libDList.so $(LIB)/libBigInt.so

$(TARGET): $(LIB)/libDList.so $(LIB)/libBigInt.so $(OBJECTSFILES)
	$(CXX) $(CCFLAGS) $(LIBDIR) -o $@ $^ -lSLL

$(LIB)/libDList.so: $(SRC)/DList.c
	$(CXX) $(CCFLAGS) $(INCLUDEDIR) $< -o $@ -shared -fpic

$(LIB)/libBigInt.so: $(SRC)/BigInt.c
	$(CXX) $(CCFLAGS) $(INCLUDEDIR) $(LIBDIR) $< -o $@ -shared -fpic -lSLL

%.o: %.c
	$(CXX) $(CCFLAGS) $(INCLUDEDIR) -o $@ -c $<

clean:
	rm -irf *.o src/*.o *~ src/*~ *.out
