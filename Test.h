#pragma once
#include "ShrdPtrTest.h"
#include "UnqPtrTest.h"
#include "WeakPtrTest.h"
#include "Atomic Pointers/ShrdPtrAtomicTest.h"
#include "Atomic Pointers/WeakPtrAtomicTest.h"
#include "MutableSequenceTest.h"

class Test {
public:
    void testUnqPtr();
    void testShrdPtr();
    void testWeakPtr();
    void testShrdPtrAtomic();
    void testWeakPtrAtomic();
    void testLinkedList();
    void testMutableSequence();
    void testAll();
};

