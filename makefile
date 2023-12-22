build:
	gcc main.c

run:
	./a.out

valgrind:
	valgrind ./a.out

built_test:
	gcc test.c

run_test:
	./test.out
