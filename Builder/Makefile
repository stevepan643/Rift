CFLAGS = -Iinclude -Wall -Wextra -pedantic
LDFLAGS = -lm

all: builder

builder: src/main.c src/module.c src/base.c src/graph.c src/order.c src/command.c src/build.c
	$(CC) $(CFLAGS) -o ../Builder src/main.c src/module.c src/base.c src/graph.c src/order.c src/command.c src/build.c $(LDFLAGS)