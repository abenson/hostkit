
ifeq ($(WIN32),yes)
	CC=i686-w64-mingw32-gcc
	AR=i686-w64-mingw32-ar
else
	CC=x86_64-w64-mingw32-gcc
	AR=x86_64-w64-mingw32-ar
endif

CFLAGS=-static
LDFLAGS=