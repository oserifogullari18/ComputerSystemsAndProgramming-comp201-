CC = gcc

all: clean install
	./fcalculator
install: fcalculator

clean:
	rm -rf mainfunc.o f.o io.o fcalculator

fcalculator: compilemain f.o io.o
	$(CC) -o fcalculator mainfunc.o f.o io.o

compilemain: mainfunc.c
	$(CC) -c mainfunc.c

f.o: f.c
	$(CC) -c f.c

io.o: io.c
	$(CC) -c io.c