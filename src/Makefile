TESTFLAGS = -lcheck
# GCCFLAGS = -Wall -Werror -Wextra
# GCOVFLAGS = -fprofile-arcs -ftest-coverage

SRC_DIR = ../ahmad
SRCS := $(wildcard $(SRC_DIR)/*.c)


clean_screen:
	@clear

debug:
	@gcc -o runme $(SRCS)

clean:
	@rm -rf runme

start:
	@./runme

run: clean_screen clean debug start
