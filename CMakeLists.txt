cmake_minimum_required(VERSION 3.9)
project(cap)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DUSE_WEBSOCKET)
add_definitions(-DNO_SSL_DL)

find_package(WinSock)
if (WINSOCK_FOUND)
    target_link_libraries(c-library WINSOCK::WINSOCK)
endif ()

find_package(Threads)

find_package(OpenSSL)
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(
        cap

        src/Main.cpp
        src/Defs.h

        src/html/HTML.hpp
        src/Partials.hpp

        src/handlers/HandlerIndex.cpp src/handlers/HandlerIndex.h
        src/handlers/HandlerWebSocket.cpp src/handlers/HandlerWebSocket.h


        src/civet/civetweb.c src/civet/civetweb.h
        src/civet/CivetServer.cpp src/civet/CivetServer.h

        src/civet/handle_form.inl src/civet/md5.inl src/civet/sha1.inl


        src/plog/Init.h src/plog/Log.h src/plog/Logger.h src/plog/Record.h src/plog/Severity.h src/plog/Util.h src/plog/WinApi.h

        src/plog/Appenders/ColorConsoleAppender.h src/plog/Appenders/ConsoleAppender.h src/plog/Appenders/DebugOutputAppender.h src/plog/Appenders/EventLogAppender.h src/plog/Appenders/IAppender.h src/plog/Appenders/RollingFileAppender.h

        src/plog/Converters/NativeEOLConverter.h src/plog/Converters/UTF8Converter.h

        src/plog/Formatters/CsvFormatter.h src/plog/Formatters/FuncMessageFormatter.h src/plog/Formatters/MessageOnlyFormatter.h src/plog/Formatters/TxtFormatter.h
)

target_link_libraries(cap ${OPENSSL_LIBRARIES})
target_link_libraries(cap ${CMAKE_THREAD_LIBS_INIT})