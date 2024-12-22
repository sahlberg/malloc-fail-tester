

all: ld_alloc.so ld_alloc_counter.so

test: ld_alloc.so ld_alloc_counter.so crash
	./test_malloc_failure.sh ./crash

ld_alloc_counter.so: ld_alloc_counter.c
	gcc ld_alloc_counter.c -shared -fPIC -o ld_alloc_counter.so

ld_alloc.so: ld_alloc.c
	gcc ld_alloc.c -shared -fPIC -o ld_alloc.so

crash: crash.c
	gcc crash.c -o crash

