include ../common.mk

WRITER_SRC= writers.c writer_json.c writer.c writer_xml.c
WRITER_HDR= writers.h writer_json.h writer.h writer_xml.h

all: writer.a

writer.a:  $(WRITER_SRC) $(WRITER_HDR)
	$(CC) -c $(WRITER_SRC)
	$(AR) r writer.a *.o

test.exe: writer.a
	$(CC) -o test.exe main.c writer.a

clean:
	rm -f *.o
	rm -f *.a
	rm -f test.exe
