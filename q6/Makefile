CC ?= gcc
CFLAGS_common ?= -O0 -Wall -std=gnu99 -g3
LDFLAGS = 

EXEC = iterative recursive
all: $(EXEC)

iterative: main.o iterative.o
	$(CC) -o $@ $^

recursive: main.o recursive.o
	$(CC)  -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS_common) -o $@ $<

run:$(EXEC)
	@echo --------------Iterative Version Start---------------
	@echo RUN Iterative Version:
	@./iterative
	@echo --------------Iterative Version End-----------------
	@echo --------------Recursive Version Start---------------
	@echo RUN Recursive Version:
	@./recursive
	@echo --------------Recursive Version End-----------------

clean:
	$(RM) $(EXEC) *.o perf.* result.txt
