#pragma once
#include <cassert>
#include <iostream>
#include <memory>
#include "ShrdPtr.h"
#include "WeakPtr.h"
#include "ShrdPtrAtomic.h"

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
    void testAtomic();
    void testAssignmentTreading();
    void testThreading();
};

