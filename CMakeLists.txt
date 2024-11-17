cmake_minimum_required(VERSION 3.5)
project(cstar)

# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMAC -std=c++11")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g -ggdb -ggnu-pubnames -std=c++11")

set(CMAKE_EXEC_LINKER_FLAGS "-static")
set(HEADERS cs_global.h cs_basic.h cs_block.h cs_compile.h cs_defines.h cs_errors.h
        cs_interpret.h cs_exec.h
        cs_PreBuffer.h)
set(SOURCE_FILES lexer.cpp
        errors.cpp
        interpret.cpp
        expression.cpp
        block.cpp
        statement.cpp
        program.cpp
        exec.cpp
        execlib.cpp
        displays.cpp)
set(COMPILE_FILES compile.cpp
        block.cpp
        displayc.cpp
        lexer.cpp
        errors.cpp
        statement.cpp
        expression.cpp
        initcompiler.cpp)
set(COMPILE_HDRS cs_compile.h)

add_executable(cstar ${SOURCE_FILES} ${HEADERS})

add_executable(cstc ${COMPILE_FILES} ${COMPILE_HDRS})

#add_executable(cstar main.cpp)
#        commdelay.cpp
#        interpret.cpp)
