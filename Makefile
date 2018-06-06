#Makefile for project
CXX=g++

BINARIES = run

all: ${BINARIES}

run: Main.o Hashtable.o Student.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o