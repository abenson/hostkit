CC32=i686-w64-mingw32-gcc
CC64=x86_64-w64-mingw32-gcc

AR32=i686-w64-mingw32-ar
AR64=x86_64-w64-mingw32-ar

CFLAGS=-municode -DUNICODE -D_UNICODE
LDFLAGS=-lnetapi32

ifdef X64
	CC=$(CC64)
	AR=$(AR64)
else
	CC=$(CC32)
	AR=$(AR32)
endif

