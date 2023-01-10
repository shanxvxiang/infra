cmake_minimum_required(VERSION 3.10)
project(infra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -O3 -lpthread -rdynamic -g -no-pie")
# -rdynamic -g -no-pie for debug with addr2line

include_directories(
	/usr/include
	/usr/include/c++/9
#    ${PROJECT_SOURCE_DIR}/third/antlr
)

link_directories(
#    ${PROJECT_SOURCE_DIR}/lib
)

macro(generate_parse perfix)
	set(PARSE_FILE_LOCATION ${PROJECT_SOURCE_DIR}/parse/)
	add_custom_command(
		OUTPUT ${PARSE_FILE_LOCATION}${perfix}.bison.c ${PARSE_FILE_LOCATION}${perfix}.bison.h
		COMMAND bison -d ${PARSE_FILE_LOCATION}${perfix}.y -o ${PARSE_FILE_LOCATION}${perfix}.bison.c
		DEPENDS ${PARSE_FILE_LOCATION}${perfix}.y
		VERBATIM
    )	
	add_custom_command(
		OUTPUT ${PARSE_FILE_LOCATION}${perfix}.flex.c
		COMMAND flex --outfile=${PARSE_FILE_LOCATION}${perfix}.flex.c  ${PARSE_FILE_LOCATION}${perfix}.l
		DEPENDS ${PARSE_FILE_LOCATION}${perfix}.l
		VERBATIM
   )	
	set(ALL_PARSE_FILES ${ALL_PARSE_FILES} ${PARSE_FILE_LOCATION}${perfix}.bison.c ${PARSE_FILE_LOCATION}${perfix}.flex.c)
endmacro()

generate_parse(configfile)
generate_parse(classdefine)

# generate_parse(Puml)

add_executable(infra infra.cpp ${ALL_PARSE_FILES}) 



