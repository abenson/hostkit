ALL: hostkit.exe writer.a

include common.mk

HK_SRC= main.c arguments.c
HK_HDR= common.h arguments.h

WRITER_SRC= writer/writers.c writer/writer_json.c writer/writer.c writer/writer_xml.c
WRITER_HDR= writer/writers.h writer/writer_json.h writer/writer.h writer/writer_xml.h

hostkit.exe: $(HK_SRC) $(HK_HDR) writer.a
	$(CC) -o hostkit.exe $(HK_SRC) writer.a

writer.a:  $(WRITER_SRC) $(WRITER_HDR)
	$(CC) -c $(WRITER_SRC)
	$(AR) r writer.a writer*.o

clean:
	cd writer && make clean
	rm -f *.o *.a
	rm -f hostkit.exe
