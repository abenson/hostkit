cmake_minimum_required(VERSION 3.12)

project(HostKit)

set(SOURCES
	writer/writers.c
	writer/writer_json.c
	writer/writer.c
	writer/writer_xml.c
	modules/modules.c
	modules/basic/host_details.c
	arguments.c
	util.c
	service.c
	persist.c
	main.c
)

set(HEADERS
	common.h
	modules/basic/basic.h
	modules/full/full.h
	modules/modules.h
	modules/standard/standard.h
	persist.h
	service.h
	util.h
	writer/writer.h
	writer/writer_json.h
	writer/writer_xml.h
	writer/writers.h
	arguments.h
)

link_libraries(-static)

add_executable(HostKit.exe ${SOURCES} ${HEADERS})
