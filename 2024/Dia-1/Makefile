GXX = g++
FLAGS = -std=c++2a -Wall -Wextra -ggdb -Wno-unused-variable -Wno-unused-parameter
TARGETS = main main1 main2

.PHONY = clean run gdb

clean:
	rm -f *.o $(TARGETS)

main: main.cpp
	$(GXX) $(FLAGS) $^ -o $@


run: main
	./main $(PARTE)
	@echo $(PARTE)

gdb: main
	gdb main $(PARTE)