file(GLOB_RECURSE HEADER_FILES
        *.hpp)

file(GLOB_RECURSE SOURCE_FILES
        *.cpp)

add_library(JohnsonLib STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(JohnsonLib PUBLIC FibonacciHeap)

target_include_directories(JohnsonLib PUBLIC Algorithm)
set_target_properties(JohnsonLib PROPERTIES LINKER_LANGUAGE CXX)