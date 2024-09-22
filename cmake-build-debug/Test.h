#pragma once
#include "ShrdPtrTest.h"
#include "UnqPtrTest.h"
#include "WeakPtrTest.h"

class Test {
public:
    void testUnqPtr();
    void testShrdPtr();
    void testWeakPtr();
    void testAll();
};

