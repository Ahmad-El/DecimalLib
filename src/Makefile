TESTFLAGS = -lcheck
GCCFLAGS = -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage

SRC = ./
TEST = $(wildcard $(SRC)/*.c)
MAIN := $(wildcard $(SRC)/arithmetic/*.c)
MAIN += $(wildcard $(SRC)/comparison/*.c)
MAIN += $(wildcard $(SRC)/extra_function/*.c)
MAIN += $(wildcard $(SRC)/converters/*.c)
MAIN += $(wildcard $(SRC)/another/*.c)


all: clean clean_screen test gcov_report

s21_decimal.a:
	@gcc $(GCCFLAGS) -std=c11 -c $(MAIN)
	ar rc s21_decimal.a *.o

test: s21_decimal.a
	@gcc -o test $(MAIN) $(TEST) $(TESTFLAGS) $(GCCFLAGS) $(GCOVFLAGS) 
	@./test

gcov_report: test
	@lcov -t "./gcov" -o report.info --no-external -c -d .
	@genhtml -o report report.info
	@open ./report/index.html

clean:
	@rm -rf runme
	@rm -rf *.o *.a *.out *.gcno *.gcda *.info *.gch test report gcov_report
	@clear

clean_screen:
	@clear

rebuild: clean all

style:
	clang-format --style=google -n *.c *.h arithmetic/*.c another/*.c comparison/*.c extra_function/*.c converters/*.c 
	rm -rf .clang-format
