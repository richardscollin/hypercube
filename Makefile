
all:
	gcc -Wall -o main hypercube.c internals.c -lwiringPi

clean:
	rm main

test:
	gcc -Wall -DTEST_PINS -o main internals.c -lwiringPi
