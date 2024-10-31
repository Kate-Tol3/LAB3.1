#pragma once
#include <cassert>
#include <iostream>
#include <memory>
#include "WeakPtr.h"
#include "ShrdPtr.h"

class WeakPtrTest {
public:
    void testConstructors();
    void testOperators();
    void testGet();
    void testCopyAssignment();
    void testMoveAssignment();
    void testRelease();
    void testExpired();
    void testIsNull();
    void testLock();
    void testSwap();
    void testUseCount();
    void testUnique();
    void test();
};