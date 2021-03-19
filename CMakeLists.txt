cmake_minimum_required (VERSION 3.1)
project (visionpluginproject)

find_package(Threads REQUIRED)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -fPIC -g -Wno-psabi")
if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -D_GLIBCXX_USE_SCHED_YIELD -D_GLIBCXX_USE_NANOSLEEP")
endif()

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -ffast-math -Wall -std=c++11 -std=gnu++11  -march=armv7-a -fnon-call-exceptions -lcryptopp")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread --omit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fext-numeric-literals")

set(OpenCV_DIR "/usr/local/include/opencv4")


set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Vision.cpp
)

include_directories (
${CMAKE_CURRENT_SOURCE_DIR}/include/
/usr/local/include/opencv4
)

link_directories (
	${CMAKE_CURRENT_SOURCE_DIR}/lib
	/usr/lib
        /usr/local/lib
	)

add_library(acvisionplugin
SHARED
${SOURCES}
)

#target_link_libraries(acvisionplugin /usr/local/lib/libopencv_dnn.so.4.1.1) 

target_link_libraries (
	acvisionplugin
        #cpu_extension
	#opencv_core
	#opencv_highgui
	#opencv_video
	dl
	)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
