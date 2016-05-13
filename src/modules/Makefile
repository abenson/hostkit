include ../common.mk

MODULES_SRC= modules.c basic/host_details.c
MODULES_HDR= modules.h basic/basic.h standard/standard.h full/full.h

all: modules.a

test.exe:
	echo "No test suite built yet."

modules.a:  $(MODULES_SRC) $(MODULES_HDR)
	$(CC) $(CFLAGS) -c $(MODULES_SRC)
	$(AR) r modules.a *.o

clean:
	rm -f *.o
	rm -f *.a
	rm -f test.exe
