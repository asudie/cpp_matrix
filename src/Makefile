CC=g++
FLAGS= -lgtest -lgtest_main -pthread
LIBS_LINUX= -lcheck -lm -lpthread -lrt -lsubunit -D_GNU_SOURCE
LIBS_MACOS= -L /usr/local/lib -lcheck

OS = $(shell uname)
ifeq ($(OS), Darwin)
OPEN=open report.html
LIBS=$(LIBS_MACOS)
LEAK_CHECK = CK_FORK=no leaks -atExit -- ./s21_test
endif
 
ifeq ($(OS), Linux)
OPEN=lynx
LIBS=$(LIBS_LINUX)
LEAK_CHECK = valgrind --leak-check=full --show-leak-kinds=all -s ./a.out
endif

all: clean test cpp gcov_report

test:
	$(CC) -g s21_matrix_oop.cc test.cc $(FLAGS) $(LIBS) --coverage
	./a.out

s21_matrix_oop.a:
	$(CC) -c s21_matrix_oop.cc test.cc
	ar -rcs s21_matrix_oop.a s21_matrix_oop.o


gcov_report:
	gcovr --html --html-details -o report.html
	$(OPEN) report.html

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.h *.cc --language=c++
	# clang-format -style=google -i *.c
	# clang-format -style=google -i *.h
	# clang-format -style=google -n *.c
	# clang-format -style=google -n *.h

leaks: clean test
	CK_FORK=no leaks -atExit -- ./a.out


clean:
	rm -f *.out *.gcda *.gcno *.o *.a report.* s21_test test_with_gcov* *.gcov test.c

git:
	git add Makefile s21_matrix_oop.cc s21_matrix_oop.h test.cc
	git commit -m'New commit'
	git push origin develop
