all:
	clang -Wall -Werror -Wextra -pedantic -O3 main.c

clean:
	rm *.out
