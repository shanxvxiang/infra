cmake_minimum_required(VERSION 3.24)
project(infra)

set(ANTLR_JAR_LOCATION ${PROJECT_SOURCE_DIR}/lib/antlr4-4.11.1-complete.jar)
set(PARSE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/parse)
set(PARSE_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/include/parse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -O2 -lpthread -Wno-deprecated")

include_directories(
    ${PROJECT_SOURCE_DIR}/third/antlr_include
    ${PARSE_OUTPUT_DIR}
)

link_directories(
    ${PROJECT_SOURCE_DIR}/lib
)

macro(generate_parse g4file)
    set(ANTLR_G4_LOCATION ${PARSE_SOURCE_DIR}/${g4file}.g4)
    set(ANTLR_OUTPUT_FILES
        ${PARSE_OUTPUT_DIR}/${g4file}BaseVisitor.cpp
        ${PARSE_OUTPUT_DIR}/${g4file}Lexer.cpp
        ${PARSE_OUTPUT_DIR}/${g4file}Parser.cpp
        ${PARSE_OUTPUT_DIR}/${g4file}Visitor.cpp
    )
    add_custom_command(
        OUTPUT ${ANTLR_OUTPUT_FILES}
        COMMAND java -jar ${ANTLR_JAR_LOCATION} -Dlanguage=Cpp -no-listener -visitor -o ${PARSE_OUTPUT_DIR} ${ANTLR_G4_LOCATION}
        DEPENDS ${ANTLR_G4_LOCATION}
        VERBATIM
    )	
    set(ALL_ANTLR_OUTPUT_FILES ${ALL_ANTLR_OUTPUT_FILES} ${ANTLR_OUTPUT_FILES})
endmacro()

generate_parse(ConfigureFile)

add_executable(infra infra.cpp ${ALL_ANTLR_OUTPUT_FILES} ) 

target_link_libraries(
        infra antlr4-runtime
)
