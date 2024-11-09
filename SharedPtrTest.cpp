#include "SharedPtrTest.h"
#include <cassert>
#include <iostream>
#include <memory>
#include "SharedPtr.h"
#include "WeakPtr.h"

class TestAccessClass{
public:
    static bool check() {
        return true;
    }
};

void SharedPtrTest::testConstructors() {
    int a = 500;
    SharedPtr<int> p1;
    assert(p1.get() == nullptr);//empty

    SharedPtr<int> p2(new int (a));
    assert(*p2.get() == a);//from ptr

    SharedPtr<int> p3(p2);
    assert(p3.get() == p2.get());;
    assert(*p3.get()==a && *p2.get() == a); // copy

    SharedPtr<int> p4(std::move(p2));
    assert(p2.isNull() && *p4.get() == a);//move

    SharedPtr<int> p6(new int (a));
    WeakPtr<int> w_p(p6);//from weak
    SharedPtr<int> p5 (w_p);
    assert(p5.get() == w_p.get());

}

void SharedPtrTest::testOperators() {
    //*
    int a = 5;
    SharedPtr<int> p1(new int(a));
    assert(*p1.get() == *p1);
    assert(*p1.get() == a);

    //->
    SharedPtr<TestAccessClass> p2(new TestAccessClass());
    assert(p2 -> check());

}

void SharedPtrTest::testGet() {
    int a = 5;
    SharedPtr<int> p1(new int(a));
    assert(*p1.get() == a);
}

void SharedPtrTest::testIsNull() {
    SharedPtr<int> p1;
    assert(p1.isNull());
}

void SharedPtrTest::testUseCount() {
    int a = 5;
    SharedPtr<int> p1(new int(a));
    assert(p1.useCount() == 1);
    SharedPtr<int> p2(p1);
    assert(p1.useCount() == 2 && p2.useCount() == 2);
}

void SharedPtrTest::testRelease() {
    int a = 5;
    SharedPtr<int> p1(new int(a));
    WeakPtr<int> p2(p1);
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p1.release();
    assert(p1.useCount() == 0 && p2.useCount() == 1);
    assert(p1.get() == nullptr);
    p2.release();
    assert(p1.useCount() == 0 && p2.useCount() == 0);
}

void SharedPtrTest::testCopyOperator() {
    int a = 5;
    SharedPtr<int> p1(new int(a));
    SharedPtr<int> p2(new int());
    assert(p2.get() != p1.get());
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p2 = p1;
    assert(p2.get() == p1.get() && *p2.get() == a);
    assert(p1.useCount() == p2.useCount() && p2.useCount() == 2);
}

void SharedPtrTest::testMoveOperator() {
    int a = 5;
    SharedPtr<int> p1(new int(a));
    SharedPtr<int> p2(new int());
    assert(p2.get() != p1.get());
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p2 = std::move(p1);
    assert(*p2.get() == a && p1.get() == nullptr);
    assert(p1.useCount() == 0 && p2.useCount() == 1);
}

void SharedPtrTest::testSwap() {
    int a = 15, b = 500;
    SharedPtr<int> p1(new int(a));
    SharedPtr<int> p2(new int(b));
    SharedPtr<int> p3(p2);
    SharedPtr<int> p4(p3);
    SharedPtr<int> p5(p1);
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

void SharedPtrTest::testUnique() {
    int a = 15;
    SharedPtr<int> p1(new int(a));
    SharedPtr<int> p2(new int());
    assert(p1.unique());
    p2 = p1;
    assert(!p1.unique());
    assert(!p2.unique());
    p2.release();
    assert(p1.unique());
}

void SharedPtrTest::test() {
    testConstructors();
    testOperators();
    testGet();
    testIsNull();
    testUseCount();
    testRelease();
    testCopyOperator();
    testMoveOperator();
    testSwap();
    testUnique();
    std::cout << "All SharedPtr tests passed!" << std::endl;
}



