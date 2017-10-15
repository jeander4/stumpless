INCLUDEDIR = include
CFLAGS = -Wall -g -O0 -I $(INCLUDEDIR)/stumpless -I $(INCLUDEDIR)

all: stumpless.o stumplessd.o stumpless-test.o test-throughput.o target.o
	mkdir -p ./bin
	gcc -o ./bin/stumplessd stumplessd.o
	mkdir -p ./test/bin
	gcc -o ./test/bin/stumpless stumpless.o target.o stumpless-test.o
	gcc -o ./test/bin/throughput stumpless.o target.o throughput.o

test: all
	./bin/stumplessd &
	./test/bin/throughput
	./test/bin/stumpless
	pkill --signal SIGINT stumplessd

target.o: src/target.c $(INCLUDEDIR)/target.h
	scripts/headers_check.pl src/target.c
	gcc $(CFLAGS) -c src/target.c

stumpless.o: src/stumpless.c $(INCLUDEDIR)/stumpless/stumpless.h
	scripts/headers_check.pl src/stumpless.c
	gcc $(CFLAGS) -c src/stumpless.c

stumplessd.o: src/daemon/stumplessd.c $(INCLUDEDIR)/stumpless/stumpless.h
	scripts/headers_check.pl src/daemon/stumplessd.c
	gcc $(CFLAGS) -c src/daemon/stumplessd.c

stumpless-test.o: test/function/stumpless-test.c $(INCLUDEDIR)/stumpless/stumpless.h
	scripts/headers_check.pl test/function/stumpless-test.c
	gcc $(CFLAGS) -c test/function/stumpless-test.c

test-throughput.o: test/performance/throughput.c
	scripts/headers_check.pl test/performance/throughput.c
	gcc $(CFLAGS) -c test/performance/throughput.c

clean:
	rm -f *.o
	rm -f *.log
	rm -f *.csv
	rm -rf ./test/bin
	rm -rf ./bin
	if [ -e /tmp/stumplesstestpipe ]; then unlink /tmp/stumplesstestpipe ; fi
