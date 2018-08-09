
ifeq ($(WIN32),yes)
	CC=i686-w64-mingw32-gcc
	CXX=i686-w64-mingw32-g++
	BUILDDIR=build32
else
	CC=x86_64-w64-mingw32-gcc
	CXX=x86_64-w64-mingw32-g++
	BUILDDIR=build64
endif

all:
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && CC=$(CC) CXX=$(CXX) cmake ../src && make

clean:
	rm -rf $(BUILDDIR)
