#pragma once
#include "ShrdPtrTest.h"
#include "UnqPtrTest.h"
#include "WeakPtrTest.h"
#include "ShrdPtrAtomicTest.h"
#include "WeakPtrAtomicTest.h"

class Test {
public:
    void testUnqPtr();
    void testShrdPtr();
    void testWeakPtr();
    void testShrdPtrAtomic();
    void testWeakPtrAtomic();
    void testAll();
};

