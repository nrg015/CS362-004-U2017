CFLAGS = -Wall -fpic -coverage -lm

testme.o: testme.c
	gcc -c testme.c -g $(CFLAGS)

testme: testme.o
	gcc -o testme -g testme.o $(CFLAGS)

runtestme:
	./testme

clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno
