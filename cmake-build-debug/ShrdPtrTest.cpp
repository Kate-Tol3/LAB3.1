
#include "ShrdPtrTest.h"

class TestAccessClass{
public:
    static bool check() {
        return true;
    }
};

void ShrdPtrTest::testConstructors() {
    int a = 500;
    ShrdPtr<int> p1;
    assert(p1.get() == nullptr);//empty

    ShrdPtr<int> p2(new int (a));
    assert(*p2.get() == a);//from ptr

    ShrdPtr<int> p3(p2);
    assert(p3.get() == p2.get());;
    assert(*p3.get()==a && *p2.get() == a); // copy

    ShrdPtr<int> p4(std::move(p2));
    assert(p2.isNull() && *p4.get() == a);//move

    WeakPtr<int> w_p (new int (a));//from weak
    ShrdPtr<int> p5 (w_p);
    assert(p5.get() == w_p.get());

}

void ShrdPtrTest::testOperators() {
    //*
    int a = 5;
    ShrdPtr<int> p1(new int(a));
    assert(*p1.get() == *p1);
    assert(*p1.get() == a);

    //->
    ShrdPtr<TestAccessClass> p2(new TestAccessClass());
    assert(p2 -> check());

}

void ShrdPtrTest::testGet() {
    int a = 5;
    ShrdPtr<int> p1(new int(a));
    assert(*p1.get() == a);
}

void ShrdPtrTest::testIsNull() {
    ShrdPtr<int> p1;
    assert(p1.isNull());
}

void ShrdPtrTest::testUseCount() {
    int a = 5;
    ShrdPtr<int> p1(new int(a));
    assert(p1.useCount() == 1);
    ShrdPtr<int> p2(p1);
    assert(p1.useCount() == 2 && p2.useCount() == 2);
}

void ShrdPtrTest::testRelease() {
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

void ShrdPtrTest::testCopyOperator() {
    int a = 5;
    ShrdPtr<int> p1(new int(a));
    ShrdPtr<int> p2(new int());
    assert(p2.get() != p1.get());
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p2 = p1;
    assert(p2.get() == p1.get() && *p2.get() == a);
    assert(p1.useCount() == p2.useCount() && p2.useCount() == 2);
}

void ShrdPtrTest::testMoveOperator() {
    int a = 5;
    ShrdPtr<int> p1(new int(a));
    ShrdPtr<int> p2(new int());
    assert(p2.get() != p1.get());
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p2 = std::move(p1);
    assert(*p2.get() == a && p1.get() == nullptr);
    assert(p1.useCount() == 0 && p2.useCount() == 1);
}

void ShrdPtrTest::testSwap() {
    int a = 15, b = 500;
    ShrdPtr<int> p1(new int(a));//кошечка
    ShrdPtr<int> p2(new int(b));//собачка
    ShrdPtr<int> p3(p2);
    ShrdPtr<int> p4(p3);
    ShrdPtr<int> p5(p1);
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

void ShrdPtrTest::testUnique() {
    int a = 15;
    ShrdPtr<int> p1(new int(a));
    ShrdPtr<int> p2(new int());
    assert(p1.unique());
    p2 = p1;
    assert(!p1.unique());
    assert(!p2.unique());
    p2.release();
    assert(p1.unique());
}

void ShrdPtrTest::test() {
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
}





