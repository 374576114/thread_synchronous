main : main.o
	gcc -o $@ $<
main.o : main.c
	gcc -c $<

.PHONY :clean
clean:
	rm main.o main
