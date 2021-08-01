CFLAGS=-g -O0 -I include -I Resources/C/Unity/

all: bin/test bin/app build/ordered_array.o

clean:
	$(RM) -rf bin/*
	$(RM) -rf build/*
	@echo "Rimossi i file"

build/ordered_array.o: src/ordered_array.c include/ordered_array.h
	@mkdir -p "build"
	$(CC) $(CFLAGS) -c src/ordered_array.c -o build/ordered_array.o

	
bin/test: test/ordered_array_test.c build/ordered_array.o include/ordered_array.h
	@mkdir -p "bin"
	$(CC) $(CFLAGS)  test/ordered_array_test.c build/ordered_array.o Resources/C/Unity/unity.c -o bin/test


bin/app: include/ordered_array.h build/ordered_array.o app/ordered_array_app.c
	@mkdir -p "bin"
	$(CC) $(CFLAGS) -o bin/ordered_array_app build/ordered_array.o app/ordered_array_app.c

.SILENT:
run-app: bin/ordered_array_app
	bin/ordered_array_app data/records.csv
