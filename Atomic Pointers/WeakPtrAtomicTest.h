#pragma once

class WeakPtrAtomicTest {
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
    void testThreading();
    void testExpiration();
    void testAssignmentInThreads();
    void test();
};

