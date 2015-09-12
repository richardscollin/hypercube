
all:
	gcc -Wall -o main internals.c -lwiringPi

clean:
	rm main
