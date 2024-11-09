#pragma once
#include <cassert>
#include <iostream>
#include <memory>
#include "ShrdPtr.h"
#include "WeakPtr.h"

class ShrdPtrTest {
public:
    void testConstructors();
    void testOperators();
    void testMoveOperator();
    void testCopyOperator();
    void testGet();
    void testIsNull();
    void testRelease();
    void testUseCount();
    void testSwap();
    void testUnique();
    void test();
};

