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
        LoadTest1.cpp
        LoadTest1.h
        cmake-build-debug/ShrdPtr.h
        cmake-build-debug/Test.cpp
        cmake-build-debug/Test.h
        cmake-build-debug/ShrdPtrTest.cpp
        cmake-build-debug/ShrdPtrTest.h
        forUselessStuff.h
        cmake-build-debug/ShrdPtrAtomic.h
        cmake-build-debug/ShrdPtrAtomicTest.cpp
        cmake-build-debug/ShrdPtrAtomicTest.h
        cmake-build-debug/WeakPtrAtomicTest.cpp
        cmake-build-debug/WeakPtrAtomicTest.h
        cmake-build-debug/WeakPtrAtomic.h
        cmake-build-debug/LoadTest.cpp
        cmake-build-debug/LoadTest.h
        LinkedList1.h
        cmake-build-debug/LinkedListTest.cpp
        cmake-build-debug/LinkedListTest.h
        cmake-build-debug/Exception.h
        cmake-build-debug/LinkedList.h
        cmake-build-debug/Sequence.h
        ImmutableListSequence.h
        cmake-build-debug/MutableListSequence.h
        ImmutableSequence.h
        cmake-build-debug/MutableSequence.h
        cmake-build-debug/MutableSequenceTest.h
)
