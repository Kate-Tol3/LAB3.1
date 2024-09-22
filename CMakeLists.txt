cmake_minimum_required(VERSION 3.29)
project(3_1LAB)

set(CMAKE_CXX_STANDARD 20)

add_executable(3_1LAB cmake-build-debug/main.cpp
        ShrdPtr1.cpp
        ShrdPtr1.h
        cmake-build-debug/UnqPtr.h
        cmake-build-debug/WeakPtr.h
        cmake-build-debug/WeakPtrTest.cpp
        cmake-build-debug/WeakPtrTest.h
        cmake-build-debug/UnqPtrTest.cpp
        cmake-build-debug/UnqPtrTest.h
        LoadTest.cpp
        LoadTest.h
        cmake-build-debug/ShrdPtr.h
        cmake-build-debug/Test.cpp
        cmake-build-debug/Test.h
        cmake-build-debug/ShrdPtrTest.cpp
        cmake-build-debug/ShrdPtrTest.h
)
