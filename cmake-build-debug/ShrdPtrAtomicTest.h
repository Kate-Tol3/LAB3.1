#pragma once
#include <atomic>
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>
#include "ShrdPtrAtomic.h"
#include "WeakPtrAtomic.h"


class ShrdPtrAtomicTest {
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
    void testAssignmentTreading();
    void testThreading();
    void test();
};

