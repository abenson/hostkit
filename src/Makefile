CC32=i686-w64-mingw32-gcc
CC64=x86_64-w64-mingw32-gcc

CFLAGS=-municode -DUNICODE -D_UNICODE
LDFLAGS=-lnetapi32

HK_SRC= main.c arguments.c util.c service.c persist.c common.c
HK_HDR= common.h arguments.h util.h service.h persist.h common.h

MODULES_SRC= modules/modules.c modules/basic/host_details.c modules/basic/disk_details.c
MODULES_HDR= modules/modules.h modules/basic/basic.h modules/standard/standard.h modules/full/full.h

WRITER_SRC= writer/writers.c writer/writer_json.c writer/writer.c writer/writer_xml.c writer/writer_ruby.c
WRITER_HDR= writer/writers.h writer/writer_json.h writer/writer.h writer/writer_xml.h writer/writer_ruby.h

all: hostkit32.exe hostkit64.exe

hostkit32.exe: $(HK_SRC) $(HK_HDR) $(MODULES_SRC) $(MODULES_HDR) $(WRITER_HDR) $(WRITER_SRC)
	$(CC32) $(CFLAGS) -o hostkit32.exe $(HK_SRC) $(MODULES_SRC) $(WRITER_SRC) $(LDFLAGS)

hostkit64.exe: $(HK_SRC) $(HK_HDR) $(MODULES_SRC) $(MODULES_HDR) $(WRITER_HDR) $(WRITER_SRC)
	$(CC64) $(CFLAGS) -o hostkit64.exe $(HK_SRC) $(MODULES_SRC) $(WRITER_SRC) $(LDFLAGS)

clean:
	rm -f *.o *.a
	rm -f *.exe
