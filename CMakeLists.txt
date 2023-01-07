cmake_minimum_required(VERSION 3.24)
project(infra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -O3 -lpthread -rdynamic -g -no-pie")
# -rdynamic -g -no-pie for debug with addr2line

include_directories(
#    ${PROJECT_SOURCE_DIR}/third/antlr
)

link_directories(
#    ${PROJECT_SOURCE_DIR}/lib
)

macro(generate_parse perfix)
	set(PARSE_FILE_LOCATION ${PROJECT_SOURCE_DIR}/parse/${perfix})
	add_custom_command(
		OUTPUT ${PARSE_FILE_LOCATION}.bison.c
		COMMAND bison -d ${PARSE_FILE_LOCATION}.y -o ${PARSE_FILE_LOCATION}.bison.c
		DEPENDS ${PARSE_FILE_LOCATION}.y
		VERBATIM
    )	
  add_custom_command(
		OUTPUT ${PARSE_FILE_LOCATION}.flex.c
		COMMAND flex --outfile=${PARSE_FILE_LOCATION}.flex.c  ${PARSE_FILE_LOCATION}.l
		DEPENDS ${PARSE_FILE_LOCATION}.l
		VERBATIM
   )	
	set(ALL_PARSE_FILES ${PARSE_FILE_LOCATION}.bison.c ${PARSE_FILE_LOCATION}.flex.c)
endmacro()

generate_parse(configfile)
# generate_parse(Puml)

add_executable(infra  ${ALL_PARSE_FILES}) 
# infra.cpp


