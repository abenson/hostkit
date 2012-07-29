ALL: hostkit.exe

include common.mk

HK_SRC= main.c
HK_HDR= 


hostkit.exe: $(HK_SRC) $(HK_HDR)
	$(CC) -o hostkit.exe $(HK_SRC)

clean:
	cd writer && make clean
	rm -f *.o
	rm -f hostkit.exe
