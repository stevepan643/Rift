CFLAGS = -Wall -Wextra -O2
LDFLAGS = -Iinc

rbuidler: src/main.c src/module.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/main.c -o main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/module.c -o module.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o rbuidler main.o module.o
	rm *.o
