all:
	mkdir -p ../bin
	gcc -Wall -pedantic -std=gnu99 -o ../bin/compass main.c

debug:
	mkdir -p ../bin
	gcc -Wall -pedantic -std=gnu99 -g -DDEBUG -o ../bin/compass main.c

test:
	mkdir -p ../bin
	gcc -Wall -pedantic --std=gnu99 -o ../bin/test test.c graphics.c
	../bin/test
	rm ../bin/test
