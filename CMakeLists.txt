cmake_minimum_required(VERSION 3.29)
project(3_1LAB)

set(CMAKE_CXX_STANDARD 20)

add_executable(3_1LAB main.cpp
        UnqPtr.h
        WeakPtr.h
        WeakPtrTest.cpp
        WeakPtrTest.h
        UnqPtrTest.cpp
        UnqPtrTest.h
        ShrdPtr.h
        Test.cpp
        Test.h
        ShrdPtrTest.cpp
        ShrdPtrTest.h
        "Atomic Pointers/ShrdPtrAtomic.h"
        "Atomic Pointers/ShrdPtrAtomicTest.cpp"
        "Atomic Pointers/ShrdPtrAtomicTest.h"
        "Atomic Pointers/WeakPtrAtomicTest.cpp"
        "Atomic Pointers/WeakPtrAtomicTest.h"
        "Atomic Pointers/WeakPtrAtomic.h"
        LoadTest.cpp
        LoadTest.h
        LinkedListTest.cpp
        LinkedListTest.h
        Exception.h
        LinkedList.h
        Sequence.h
        MutableListSequence.h
        MutableSequence.h
        MutableSequenceTest.h

)
