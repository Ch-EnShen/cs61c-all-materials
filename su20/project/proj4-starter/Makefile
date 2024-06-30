CC = gcc
CFLAGS = -g -Wall -std=c99 -fopenmp -mavx -mfma -pthread
LDFLAGS = -fopenmp
CUNIT = -L/home/ff/cs61c/cunit/install/lib -I/home/ff/cs61c/cunit/install/include -lcunit
PYTHON = -I/usr/include/python3.6 -lpython3.6m

install:
	if [ ! -f files.txt ]; then touch files.txt; fi
	rm -rf build
	xargs rm -rf < files.txt
	python3 setup.py install --record files.txt

uninstall:
	if [ ! -f files.txt ]; then touch files.txt; fi
	rm -rf build
	xargs rm -rf < files.txt

clean:
	rm -f *.o
	rm -f test
	rm -rf build
	rm -rf __pycache__

test:
	rm -f test
	$(CC) $(CFLAGS) mat_test.c matrix.c -o test $(LDFLAGS) $(CUNIT) $(PYTHON)
	./test

.PHONY: test