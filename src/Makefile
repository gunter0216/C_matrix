.PHONY: all clean test matrix.a check gcov_report
CC=gcc
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
else
	CC += -D OS_LINUX
endif

default: all
 
all: clean s21_matrix.a test
 
test: s21_matrix.a
ifeq ($(OS), Darwin)
	$(CC) -o test test.c s21_matrix.a -lcheck
	./test
else
	$(CC) -o test test.c s21_matrix.a -lcheck -lm -lsubunit -lrt -lpthread
	./test
endif
 
s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	ranlib $@
	cp $@ lib$@
	
s21_matrix.o: s21_matrix.c
	$(CC) -c -o s21_matrix.o s21_matrix.c

gcov_report: s21_matrix.a
ifeq ($(OS), Darwin)
	$(CC) --coverage -o testresult test.c s21_matrix.c -lcheck
	./testresult
else
	$(CC) --coverage -o testresult test.c s21_matrix.c -lcheck -lm -lsubunit -lrt -lpthread
	./testresult
endif
	lcov -t "testresult" -o testresult.info -c -d .
	genhtml -o report testresult.info

check:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extension=c s21_matrix.c s21_matrix.h test.c
	CK_FORK=no leaks -atExit -- ./test

clean:
	rm -rf test *.a *.o *.out *.gc* *.info report testresult CPPLINT.cfg
 
rebuild: clean all