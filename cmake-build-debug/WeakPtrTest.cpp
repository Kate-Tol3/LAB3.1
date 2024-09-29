
#include "WeakPtrTest.h"

class TestAccessClass{
public:
    static bool check() {
        return true;
    }
};

void WeakPtrTest::testConstructors() {
    int a = 50;
    WeakPtr<int> p1;
    assert(p1.get() == nullptr);//empty

    WeakPtr<int> p2(new int (a));
    assert(*p2.get() == a);//from ptr

    WeakPtr<int> p3(p2);
    assert(p3.get() == p2.get());;
    assert(*p3.get()==a && *p2.get() == a); // copy

    WeakPtr<int> p4(std::move(p2));
    assert(p2.isNull() && *p4.get() == a);//move

    ShrdPtr<int> s_p (new int (a));
    WeakPtr<int> p5 (s_p);
    assert(p5.get() == s_p.get());
}

void WeakPtrTest::testOperators() {
    //*
    int a = 5;
    WeakPtr<int> p1(new int(a));
    assert(*p1.get() == *p1);
    assert(*p1.get() == a);

    //->
    WeakPtr<TestAccessClass> p2(new TestAccessClass());
    assert(p2 -> check());
}

void WeakPtrTest::testRelease() {
    int a = 5;
    ShrdPtr<int> p1(new int(a));
    WeakPtr<int> p2(p1);
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p1.release();
    assert(p1.useCount() == 0 && p2.useCount() == 1);
    assert(p1.get() == nullptr);
    p2.release();
    assert(p1.useCount() == 0 && p2.useCount() == 0);
}

void WeakPtrTest::testSwap() {
    // int a = 15, b = 500;
    // WeakPtr<int> p1(new int(a));
    // WeakPtr<int> p2(new int(b));
    // WeakPtr<int> p3(p2);
    // assert(*p1.get() == a);
    // assert(*p2.get() == b);
    // assert(*p3.get() == a);
    // assert((p1.useCount() == 1) && (p2.useCount() == 2) && (p3.useCount() == 2));
    // p1.swap(p2);
    // assert(*p1.get() == b);
    // assert(*p2.get() == a);
    // assert(*p3.get() == a);
    // assert((p1.useCount() == 2) && (p2.useCount() == 1) && (p3.useCount() == 2));

    int a = 15, b = 500;
    WeakPtr<int> p1(new int(a));//кошечка
    WeakPtr<int> p2(new int(b));//собачка
    WeakPtr<int> p3(p2);
    WeakPtr<int> p4(p3);
    WeakPtr<int> p5(p1);
    assert(*p1.get() == a);
    assert(*p2.get() == b);
    assert(*p3.get() == b);
    assert(*p4.get() == b);
    assert(*p5.get() == a);
    assert((p1.useCount() == 2) && (p2.useCount() == 3) && (p3.useCount() == 3) && (p4.useCount() == 3) && (p5.useCount() == 2));
    p1.swap(p2);
    assert(*p1.get() == b);
    assert(*p2.get() == a);
    assert(*p3.get() == a);
    assert(*p4.get() == a);
    assert(*p5.get() == b);
    assert((p1.useCount() == 2) && (p2.useCount() == 3) && (p3.useCount() == 3) && (p4.useCount() == 3) && (p5.useCount() == 2));
}

void WeakPtrTest::testCopyAssignment() {
    int a = 5;
    WeakPtr<int> p1(new int(a));
    WeakPtr<int> p2(new int());
    assert(p2.get() != p1.get());
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p2 = p1;
    assert(p2.get() == p1.get() && *p2.get() == a);
    assert(p1.useCount() == p2.useCount() && p2.useCount() == 2);
}

void WeakPtrTest::testMoveAssignment() {
    int a = 5;
    WeakPtr<int> p1(new int(a));
    WeakPtr<int> p2(new int());
    assert(p2.get() != p1.get());
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p2 = std::move(p1);
    assert(*p2.get() == a && p1.get() == nullptr);
    assert(p1.useCount() == 0 && p2.useCount() == 1);
}

void WeakPtrTest::testIsNull() {
    WeakPtr<int> p1;
    assert(p1.isNull());
}

void WeakPtrTest::testUseCount() {
    int a = 5;
    ShrdPtr<int> p1(new int(a));
    WeakPtr<int> p2(p1);
    assert(p2.useCount() == 1 && p1.useCount() == 1);
    WeakPtr<int> p3(p1);
    assert(p3.useCount() == 2 && p1.useCount() == 1 && p2.useCount() == 2);
}

void WeakPtrTest::testGet() {
    int a = 5;
    WeakPtr<int> p1(new int(a));
    assert(*p1.get() == a);
}

void WeakPtrTest::testUnique() {
    int a = 15;
    WeakPtr<int> p1(new int(a));
    WeakPtr<int> p2(new int());
    assert(p1.unique());
    p2 = p1;
    assert(!p1.unique());
    assert(!p2.unique());
    p2.release();
    assert(p1.unique());
}

void WeakPtrTest::testExpired() {
    int a = 40;
    ShrdPtr<int> p1(new int(a));
    WeakPtr<int> p2(p1);
    assert(!p2.expired());
    p2.release();
    assert(p2.expired());
}

void WeakPtrTest::testLock() {
    int a = 100;
    ShrdPtr<int> p1(new int(a));
    WeakPtr<int> p2(p1);
    ShrdPtr<int> p3;
    ShrdPtr<int> p4;
    p3 = p2.lock();
    assert(p3.get() == p1.get());
    assert(p3.useCount() == 2);

    p1.release();
    p2.release();
    p3.release();
    assert(p2.expired());
    p4 = p2.lock();
    assert(p4.isNull());
    assert(p4.useCount() == 0);
}

void WeakPtrTest::test() {
    testConstructors();
    testOperators();
    testRelease();
    testSwap();
    testExpired();
    testCopyAssignment();
    testMoveAssignment();
    testIsNull();
    testUseCount();
    testGet();
    testUnique();
    testLock();
    std::cout << "All WeakPtr tests passed!" << std::endl;
}