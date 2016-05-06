ALL: hostkit.exe

include common.mk

WRITER_SRC= writer/writers.c writer/writer_json.c writer/writer.c writer/writer_xml.c
WRITER_HDR= writer/writers.h writer/writer_json.h writer/writer.h writer/writer_xml.h

MODULES_SRC= modules/modules.c modules/basic/host_details.c
MODULES_HDR= modules/modules.h modules/basic/basic.h modules/standard/standard.h modules/full/full.h

HK_SRC= main.c arguments.c util.c service.c persist.c
HK_HDR= common.h arguments.h util.h service.h persist.h

COMMON_SRC= common/common.c
COMMON_HDR= common/common.h

hostkit.exe: $(HK_SRC) $(HK_HDR) writer.a modules.a common.a
	$(CC) $(CFLAGS) -o hostkit.exe $(HK_SRC) writer.a modules.a common.a $(LDFLAGS)

modules.a:  $(MODULES_SRC) $(WRITER_HDR)
	$(CC) $(CFLAGS) -c $(MODULES_SRC) $(LDFLAGS)
	$(AR) r modules.a *.o

writer.a:  $(WRITER_SRC) $(WRITER_HDR)
	$(CC) $(CFLAGS) -c $(WRITER_SRC) $(LDFLAGS)
	$(AR) r writer.a *.o

common.a: $(COMMON_SRC) $(COMMON_HDR)
	$(CC) $(CFLAGS) -c $(COMMON_SRC) $(LDFLAGS)
	$(AR) r common.a *.o

clean:
	cd writer && make clean
	rm -f *.o *.a
	rm -f hostkit.exe
