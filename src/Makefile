ALL: hostkit.exe 

include common.mk

WRITER_SRC= writer/writers.c writer/writer_json.c writer/writer.c writer/writer_xml.c
WRITER_HDR= writer/writers.h writer/writer_json.h writer/writer.h writer/writer_xml.h

MODULES_SRC= modules/modules.c
MODULES_HDR= modules/mdoules.h

HK_SRC= main.c arguments.c util.c service.c persist.c
HK_HDR= common.h arguments.h util.h service.h persist.h

hostkit.exe: $(HK_SRC) $(HK_HDR) writer/writer.a modules/modules.a
	$(CC) -o hostkit.exe $(HK_SRC) writer.a

modules/modules.a:  $(MODULES_SRC) $(WRITER_HDR)
	cd modules
	$(CC) -c $(MODULES_SRC)
	$(AR) r modules.a *.o

writer/writer.a:  $(WRITER_SRC) $(WRITER_HDR)
	cd writer
	$(CC) -c $(WRITER_SRC)
	$(AR) r writer.a *.o

clean:
	cd writer && make clean
	rm -f *.o *.a
	rm -f hostkit.exe
