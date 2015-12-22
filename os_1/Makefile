obj := main.o
CFLAG := -lpthread

main : ${obj}
	gcc -o $@ $< ${CFLAG}
${obj} : main.c
	gcc -c $<
.PHONY : clean
clean:
	rm ${obj} main
