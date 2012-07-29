ALL: hostkit.exe

HK_SRC= main.c
HK_HDR= 


CC=i686-w64-mingw32-gcc

hostkit.exe: $(HK_SRC) $(HK_HDR)
	$(CC) -o hostkit.exe $(HK_SRC)

clean:
	rm -f *.o
	rm -f hostkit.exe
