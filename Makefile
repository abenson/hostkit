CC32=i686-w64-mingw32-gcc
CC64=x86_64-w64-mingw32-gcc

CFLAGS=-municode -DUNICODE -D_UNICODE -Iinclude
LDFLAGS=-lnetapi32

HOSTKIT_SRC=	src/main.c              \
				src/arguments.c         \
				src/util.c				\
				src/service.c			\
				src/persist.c

HOSTKIT_HDR=	include/arguments.h			\
				include/util.h				\
				include/service.h			\
				include/persist.h

MODULES_SRC=	src/modules/modules.c                \
				src/modules/common.c 				 \
				src/modules/basic/host_details.c     \
				src/modules/basic/disk_details.c     \
				src/modules/standard/enum_windir.c

MODULES_HDR=	include/modules/modules.h	\
				include/modules/modes.h

WRITERS_SRC=	src/writers/writers.c		\
				src/writers/writer_json.c	\
				src/writers/writer.c			\
				src/writers/writer_xml.c 	\
				src/writers/writer_ruby.c

WRITERS_HDR=	include/writers/writers.h 		\
				include/writers/writer_json.h 	\
				include/writers/writer.h 		\
				include/writers/writer_xml.h 	\
				include/writers/writer_ruby.h

all: bin/hostkit32.exe bin/hostkit64.exe

test: bin/writer_test32.exe bin/writer_test64.exe

bin/:
	mkdir -p bin/

bin/hostkit32.exe: bin/ $(HOSTKIT_SRC) $(HOSTKIT_HDR) $(MODULES_SRC) $(MODULES_HDR) $(WRITERS_HDR) $(WRITERS_SRC)
	$(CC32) $(CFLAGS) -o bin/hostkit32.exe $(HOSTKIT_SRC) $(MODULES_SRC) $(WRITERS_SRC) $(LDFLAGS)

bin/hostkit64.exe: bin/ $(HOSTKIT_SRC) $(HOSTKIT_HDR) $(MODULES_SRC) $(MODULES_HDR) $(WRITERS_HDR) $(WRITERS_SRC)
	$(CC64) $(CFLAGS) -o bin/hostkit64.exe $(HOSTKIT_SRC) $(MODULES_SRC) $(WRITERS_SRC) $(LDFLAGS)

bin/writer_test32.exe: bin/ $(WRITERS_SRC) $(WRITERS_HDR) src/writers/main.c src/common.c
	$(CC32) $(CFLAGS) -o bin/writer_test32.exe $(WRITERS_SRC) src/writers/main.c src/common.c $(LDFLAGS)

bin/writer_test64.exe: bin/ $(WRITERS_SRC) $(WRITERS_HDR) src/writers/main.c src/common.c
	$(CC64) $(CFLAGS) -o bin/writer_test64.exe $(WRITERS_SRC) src/writers/main.c src/common.c $(LDFLAGS)

clean:
	rm -rf bin/
