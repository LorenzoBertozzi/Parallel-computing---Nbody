CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lm

sequential: sequential.c generate.c generate.h
	$(CC) $(CFLAGS) -o sequential sequential.c generate.c $(LDFLAGS)

clean:
	rm -f sequential
