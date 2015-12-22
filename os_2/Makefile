.PHONY:all
all: main get put copy

main : main.c
	gcc -o $@ $<
get : get.c
	gcc -o $@ $<
put : put.c
	gcc -o $@ $<
copy: copy.c
	gcc -o $@ $<

.PHONY : clean
clean :
	rm main get put copy
