CFLAGS = -Wall -fpic -coverage -lm
testme: 
	gcc -o testme testme.c -g $(CFLAGS)
runtestme: testme
	./testme

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out  testme
