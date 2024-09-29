#include "UnqPtrTest.h"


class TestAccessClass{
public:
    static bool check() {
        return true;
    }
};

void UnqPtrTest::testConstructors(){
    int a = 6;
    UnqPtr<int> p1;//empty constructor
    assert(p1.get() == nullptr);
    UnqPtr<int> p2(new int(a));//from ptr contructor
    assert(*(p2.get()) == a);
    UnqPtr<int> p3(std::move(p2));//move constuctor
    assert(*(p3.get()) == a);
    assert(p2.get() == nullptr);

}

void UnqPtrTest::testOperators() {
    //*
    int a = 12;
    UnqPtr<int> p1(new int(a));
    assert(*(p1.get()) == *p1);
    assert(*(p1.get()) == a);
    //->
    UnqPtr<TestAccessClass> p2(new TestAccessClass());
    assert(p2->check);
}

void UnqPtrTest::testGet() {
    int a = 400;
    UnqPtr<int> p1(new int(a));
    assert(*(p1.get()) == a);
}

void UnqPtrTest::testIsNull() {
    UnqPtr<int> p1;
    assert(p1.isNull());
}

void UnqPtrTest::testMoveOperator() {
    int a = 500, b = 600;
    UnqPtr<int> p1(new int(a));
    UnqPtr<int> p2(new int(b));
    assert(*p1.get() == a);
    assert(*p2.get() == b);

    p1 = std::move(p1);
    assert(!p1.isNull());

    p2 = std::move(p1);
    assert(p1.isNull());
    assert(*p2.get() == a);
}

void UnqPtrTest::testRelease() {
    int a = 13;
    UnqPtr<int> p1(new int(a));
    assert(*(p1.get()) == a);
    UnqPtr<int> p2(p1.release());
    assert(*(p2.get()) == a);
    assert(p1.get() == nullptr);
}

void UnqPtrTest::testReset() {
    int a = 15, b = 200;
    UnqPtr<int> p1(new int(a));
    assert(*(p1.get()) == a);
    p1.reset(new int(b));
    assert(*(p1.get()) == b);
}

void UnqPtrTest::testSwap() {
    int a = 15, b = 500;
    UnqPtr<int> p1(new int(a));
    UnqPtr<int> p2(new int(b));
    assert(*(p1.get()) == a);
    assert(*(p2.get()) == b);
    p1.swap(p2);
    assert(*(p1.get()) == b);
    assert(*(p2.get()) == a);
}

void UnqPtrTest::test() {
    testConstructors();
    testOperators();
    testGet();
    testIsNull();
    testMoveOperator();
    testRelease();
    testReset();
    testSwap();
    std::cout << "All UnqPtr tests passed!" << std::endl;
}