include ../common.mk

WRITER_SRC= writers.c writer_json.c writer.c writer_xml.c writer_ruby.c
WRITER_HDR= writers.h writer_json.h writer.h writer_xml.h writer_ruby.h

all: writer.a

test: test.exe
	wine test.exe

test.exe: writer.a main.c
	$(CC) $(CFLAGS) -o test.exe main.c writer.a ../common.c $(LDFLAGS)

writer.a:  $(WRITER_SRC) $(WRITER_HDR)
	$(CC) $(CFLAGS) -c $(WRITER_SRC)
	$(AR) r writer.a *.o

clean:
	rm -f *.o
	rm -f *.a
	rm -f test.exe
