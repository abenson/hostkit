
all: win32 win64

win32:
	@echo "Building for i686"
	@meson setup build32 --cross-file cross/linux-mingw-w64-32bit.txt
	@meson compile -C build32

win64:
	@echo "Building for x86_64"
	@meson setup build64 --cross-file cross/linux-mingw-w64-64bit.txt
	@meson compile -C build64

clean:
	rm -rf build32 build64
