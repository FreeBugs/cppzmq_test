cmake_minimum_required(VERSION 3.17)
project(zmq_test)
set(CMAKE_CXX_STANDARD 17)

include(cmake/conan.cmake)
conan_cmake_run(REQUIRES
        gtest/1.10.0
        cppzmq/4.7.1
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

add_executable(main main.cpp Publisher.cpp Publisher.hpp SubscriberWorker.cpp SubscriberWorker.hpp)
target_link_libraries(main ${CONAN_LIBS})
target_include_directories(main PUBLIC ${CONAN_INCLUDE_DIRS_CPPZMQ} ${CONAN_INCLUDE_DIRS_ZEROMQ})
target_link_directories(main PUBLIC ${CONAN_LIB_DIRS})

if (WIN32)
    set_target_properties(main PROPERTIES COMPILE_FLAGS "/DZMQ_STATIC")
endif (WIN32)