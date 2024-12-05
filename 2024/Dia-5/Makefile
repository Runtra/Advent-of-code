GXX = g++
FLAGS = -std=c++14 -Wall -Wextra -ggdb -Wno-unused-variable -Wno-unused-parameter
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