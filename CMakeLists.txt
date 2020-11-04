cmake_minimum_required (VERSION 3.5)

set(VERSION 1.0.2)

set(pjname "jsmpeg-vnc")
project (${pjname} VERSION ${VERSION})

SET(_HEADERS 
src/app.h
src/encoder.h
src/grabber.h
src/jskeycode2x11keycode.h
src/server.h
)

SET(_SOURCES
src/app.c
src/encoder.c
src/grabber.c
src/jskeycode2x11keycode.c
src/jsmpeg-vnc.c
src/server.c
)

add_subdirectory(libwebsockets/)

add_executable(${pjname} ${_HEADERS} ${_SOURCES}) 
target_link_libraries(${pjname} websockets avcodec avutil swscale X11 Xtst z)
