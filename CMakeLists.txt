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
        SharedPtr.h
        Test.cpp
        Test.h
        SharedPtrTest.cpp
        SharedPtrTest.h
        "Atomic Pointers/SharedPtrAtomic.h"
        "Atomic Pointers/SharedPtrAtomicTest.cpp"
        "Atomic Pointers/SharedPtrAtomicTest.h"
        "Atomic Pointers/WeakPtrAtomicTest.cpp"
        "Atomic Pointers/WeakPtrAtomicTest.h"
        "Atomic Pointers/WeakPtrAtomic.h"
        LoadTest.h
        LinkedListTest.cpp
        LinkedListTest.h
        Exception.h
        LinkedList.h
        Sequence.h
        MutableListSequence.h
        MutableSequence.h
        MutableSequenceTest.h
        DynamicArray.h
        MutableArraysequence.h
        DynamicArrayTest.cpp
        DynamicArrayTest.h
        UI.cpp
        UI.h
        TestUI.cpp
        TestUI.h

)
