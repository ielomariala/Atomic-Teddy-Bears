CFLAGS =  -Wall -Wextra -std=c99 

all: code

code: code-ach0

code-ach0: src/project-2.c
	gcc $(CFLAGS) -c src/good.c
	gcc $(CFLAGS) -c src/stockex.c
	gcc $(CFLAGS) -c src/queue.c
	gcc $(CFLAGS) -c src/utility.c
	gcc $(CFLAGS) -c src/strategy.c
	gcc $(CFLAGS) -c src/project-2.c
	gcc -o project $(CFLAGS) good.o stockex.o queue.o utility.o strategy.o project-2.o -lm
	rm -f *.o 

test: test-ach0

test-ach0:
	gcc $(CFLAGS) -c src/good.c
	gcc $(CFLAGS) -c src/stockex.c
	gcc $(CFLAGS) -c src/queue.c
	gcc $(CFLAGS) -c src/utility.c
	gcc $(CFLAGS) -c src/strategy.c
	gcc $(CFLAGS) -c tst/testing_functions.c
	gcc $(CFLAGS) -c tst/A0_testing_functions.c
	gcc $(CFLAGS) -c tst/A1_testing_functions.c
	gcc $(CFLAGS) -c tst/test-2.c
	gcc -o test  $(CFLAGS) good.o stockex.o queue.o utility.o strategy.o testing_functions.o A0_testing_functions.o A1_testing_functions.o test-2.o -lm && ./test
	rm -f *.o

clean:
	rm -f *.o project test
