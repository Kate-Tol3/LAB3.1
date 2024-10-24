cmake_minimum_required(VERSION 3.29)
project(3_1LAB)

set(CMAKE_CXX_STANDARD 20)

add_executable(3_1LAB cmake-build-debug/main.cpp
        cmake-build-debug/UnqPtr.h
        cmake-build-debug/WeakPtr.h
        cmake-build-debug/WeakPtrTest.cpp
        cmake-build-debug/WeakPtrTest.h
        cmake-build-debug/UnqPtrTest.cpp
        cmake-build-debug/UnqPtrTest.h
        cmake-build-debug/ShrdPtr.h
        cmake-build-debug/Test.cpp
        cmake-build-debug/Test.h
        cmake-build-debug/ShrdPtrTest.cpp
        cmake-build-debug/ShrdPtrTest.h
        "cmake-build-debug/Atomic Pointers/ShrdPtrAtomic.h"
        "cmake-build-debug/Atomic Pointers/ShrdPtrAtomicTest.cpp"
        "cmake-build-debug/Atomic Pointers/ShrdPtrAtomicTest.h"
        "cmake-build-debug/Atomic Pointers/WeakPtrAtomicTest.cpp"
        "cmake-build-debug/Atomic Pointers/WeakPtrAtomicTest.h"
        "cmake-build-debug/Atomic Pointers/WeakPtrAtomic.h"
        cmake-build-debug/LoadTest.cpp
        cmake-build-debug/LoadTest.h
        cmake-build-debug/LinkedListTest.cpp
        cmake-build-debug/LinkedListTest.h
        cmake-build-debug/Exception.h
        cmake-build-debug/LinkedList.h
        cmake-build-debug/Sequence.h
        cmake-build-debug/MutableListSequence.h
        cmake-build-debug/MutableSequence.h
        cmake-build-debug/MutableSequenceTest.h
)
