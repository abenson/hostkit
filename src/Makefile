ALL: hostkit.exe

include common.mk

HK_SRC= main.c arguments.c util.c service.c persist.c common.c
HK_HDR= common.h arguments.h util.h service.h persist.h common.h

hostkit.exe: $(HK_SRC) $(HK_HDR) writer/writer.a modules/modules.a
	$(CC) $(CFLAGS) -o hostkit.exe $(HK_SRC) writer/writer.a modules/modules.a $(LDFLAGS)

modules/modules.a:
	cd modules && make modules.a

writer/writer.a:
	cd writer && make writer.a

clean:
	cd writer && make clean
	cd modules && make clean
	rm -f *.o *.a
	rm -f hostkit.exe
