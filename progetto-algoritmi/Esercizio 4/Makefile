CFLAGS=-g -O0
path = ""

clean:
	$(RM) -rf bin
	$(RM) -rf build
	@echo "All files have been removed!"

build/graphlib.o: src/graphlib.c include/graphlib.h
	@mkdir -p "build"
	$(CC) $(CFLAGS) -c src/graphlib.c -o build/graphlib.o

bin/app: include/graphlib.h build/graphlib.o app/app.c
	@mkdir -p "bin"
	$(CC) $(CFLAGS) -o bin/app build/graphlib.o app/app.c -g

bin/test: test/oalib_test.c build/oalib.o include/oalib.h
	@mkdir -p "bin"
	$(CC) $(CFLAGS) test/oalib_test.c build/oalib.o test/Unity/unity.c -o bin/test -g

build/graph.o: src/graph.c include/graph.h
	@mkdir -p "build"
	$(CC) $(CFLAGS) -c src/graph.c -o build/graph.o
	
bin/app2: app/app2.c build/graph.o
	@mkdir -p "bin"
	$(CC) $(CFLAGS) -g app/app2.c build/graph.o -o bin/oc


.SILENT:
run-app: bin/app
	./bin/app $(path)
	
comp-app2: bin/app2
	
run-test: bin/test
	./bin/test
	
run-debug: bin/app
	gdb ./bin/app $(path) --silent
