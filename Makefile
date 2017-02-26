
core: algorithm.c
	gcc -g -Wall -o $@ $^
clean:
	rm core