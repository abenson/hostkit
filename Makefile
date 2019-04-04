
ifdef WIN32
	CC=i686-w64-mingw32-gcc
	CXX=i686-w64-mingw32-g++
	RC=i686-w64-mingw32-windres
	BUILDDIR=build32
else
	CC=x86_64-w64-mingw32-gcc
	CXX=x86_64-w64-mingw32-g++
	RC=x86_64-w64-mingw32-windres
	BUILDDIR=build64
endif

all:
ifdef WIN32
	@echo "Building for i686"
else
	@echo "Building for x86_64"
endif
	@mkdir -p $(BUILDDIR)
	@cd $(BUILDDIR) && CC=$(CC) CXX=$(CXX) RC=$(RC) cmake ../src && make

clean:
	rm -rf $(BUILDDIR)
