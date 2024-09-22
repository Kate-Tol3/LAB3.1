#pragma once
#include <cassert>
#include <iostream>
#include <memory>
#include "UnqPtr.h"

class UnqPtrTest {
public:
    void testConstructors();
    void testOperators();
    void testMoveOperator();
    void testGet();
    void testIsNull();
    void testRelease();
    void testReset();
    void testSwap();

    void test();
};
