CFLAGS= -Wall -Werror -pedantic


Laboratorio3: Lab3.o static_library.a dynamic_lib.so 
		gcc $(CFLAGS) -o Laboratorio3 Lab3.o static_library.a dynamic_lib.so -ldl

Lab3.o: Lab3.c functions.h 
		gcc $(CFLAGS) -c Lab3.c

static_library.a: functs.o cJSON.o
		ar 	rcs static_library.a functs.o cJSON.o

dynamic_lib.so: dynamic_lib.o cJSON.o
		gcc $(CFLAGS) -shared -o dynamic_lib.so dynamic_lib.o cJSON.o

dynamic_lib.o: dynamic_lib.c functions.h cJSON.o
		gcc $(CFLAGS) -fPIC -c dynamic_lib.c

functs.o: functs.c functions.h 
		gcc $(CFLAGS) -c functs.c

cJSON.o: cJSON.c cJSON.h
		gcc $(CFLAGS) -c cJSON.c 


clean:
	rm -f *.o *.a *.so Laboratorio3

 
