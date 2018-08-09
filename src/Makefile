ALL: hostkit.exe 

include common.mk

SOURCE = writer/writers.c                             \
         writer/writer_json.c                         \
         writer/writer.c                              \
         writer/writer_xml.c                          \
         modules/modules.c                            \
         modules/basic/host_details.c                 \
         arguments.c                                  \
         util.c                                       \
         service.c                                    \
         persist.c                                    \
         main.c

HEADER = common.h                                     \
         arguments.h                                  \
         util.h                                       \
         service.h                                    \
         persist.h writer/writers.h                   \
         writer/writer_json.h                         \
         writer/writer.h                              \
         writer/writer_xml.h                          \
         modules/modules.h                            \
         modules/basic/basic.h                        \
         modules/standard/standard.h                  \
         modules/full/full.h

hostkit.exe: $(HEADER) $(SOURCE)
	$(CC) $(CFLAGS) -o hostkit.exe $(SOURCE) $(LDFLAGS)

clean:
	rm -f *.o *.a
	rm -f hostkit.exe
