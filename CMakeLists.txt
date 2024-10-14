cmake_minimum_required(VERSION 3.28)
project(ScrapeWeb)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_FIND_LIBRARY_SUFFIXES .a .so .dylib)

include_directories(/usr/local/include/webdriverxx)
link_directories(/usr/local/lib)

add_executable(ScrapeWeb main.cpp)
# curl
find_package(CURL)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
#    target_link_libraries(ScrapeWeb INTERFACE ${CURL_LIBRARIES})
    message(STATUS "curl include dirs  " ${CURL_INCLUDE_DIRS})
    message(STATUS "curl libs  " ${CURL_LIBRARIES})
endif (CURL_FOUND)

target_link_libraries(ScrapeWeb webdriverxx ${CURL_LIBRARIES})
