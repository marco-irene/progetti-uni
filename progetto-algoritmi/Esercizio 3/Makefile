CFLAGS=-g -O0

path = ""

all: bin/test bin/app

clean:
	$(RM) -rf bin
	$(RM) -rf build
	@echo "All files have been removed!"

build/oalib.o: src/oalib.c inc/oalib.h
	@mkdir -p "build"
	$(CC) $(CFLAGS) -c src/oalib.c -o build/oalib.o
	
build/hashmap.o: src/hashmap.c inc/hashmap.h
	@mkdir -p "build"
	$(CC) $(CFLAGS) -c src/hashmap.c -o build/hashmap.o

bin/app: inc/oalib.h build/oalib.o inc/hashmap.h build/hashmap.o app/app.c
	@mkdir -p "bin"
	$(CC) $(CFLAGS) -o bin/app build/oalib.o build/hashmap.o app/app.c -g

bin/test: test/hashmap_test.c build/hashmap.o inc/hashmap.h
	@mkdir -p "bin"
	$(CC) $(CFLAGS) test/hashmap_test.c build/hashmap.o test/Unity/unity.c -o bin/test -g

.SILENT:
run-app: bin/app
	./bin/app $(path)
run-test: bin/test
	./bin/test
run-debug: bin/app
	gdb ./bin/app $(path) --silent
