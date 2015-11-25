OBJ = main.o copy.o get.o put.o
DES = main copy get put

main : main.o os_2.h
	cc -o$@ main.c
copy : copy.o os_2.h
	cc -o$@ copy.c
get : get.o os_2.h
	cc -o$@ get.c
put : put.o os_2.h
	cc -o$@ put.c

clean:
	rm $(OBJ) $(DES)

