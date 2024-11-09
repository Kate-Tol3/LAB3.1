
#include "SharedPtrAtomicTest.h"
#include <atomic>
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>
#include "SharedPtrAtomic.h"
#include "WeakPtrAtomic.h"

class TestAccessClass{
public:
    static bool check() {
        return true;
    }
};

void SharedPtrAtomicTest::testConstructors() {
    int a = 500;
    SharedPtrAtomic<int> p1;
    assert(p1.get() == nullptr);//empty

    SharedPtrAtomic<int> p2(new int (a));
    assert(*p2.get() == a);//from ptr

    SharedPtrAtomic<int> p3(p2);
    assert(p3.get() == p2.get());;
    assert(*p3.get()==a && *p2.get() == a); // copy

    SharedPtrAtomic<int> p4(std::move(p2));
    assert(p2.isNull() && *p4.get() == a);//move

    WeakPtrAtomic<int> w_p (new int (a));//from weak
    SharedPtrAtomic<int> p5 (w_p);
    assert(p5.get() == w_p.get());

}

void SharedPtrAtomicTest::testOperators() {
    //*
    int a = 5;
    SharedPtrAtomic<int> p1(new int(a));
    assert(*p1.get() == *p1);
    assert(*p1.get() == a);

    //->
    SharedPtrAtomic<TestAccessClass> p2(new TestAccessClass());
    assert(p2 -> check());

}

void SharedPtrAtomicTest::testGet() {
    int a = 5;
    SharedPtrAtomic<int> p1(new int(a));
    assert(*p1.get() == a);
}

void SharedPtrAtomicTest::testIsNull() {
    SharedPtrAtomic<int> p1;
    assert(p1.isNull());
}

void SharedPtrAtomicTest::testUseCount() {
    int a = 5;
    SharedPtrAtomic<int> p1(new int(a));
    assert(p1.useCount() == 1);
    SharedPtrAtomic<int> p2(p1);
    assert(p1.useCount() == 2 && p2.useCount() == 2);
}

void SharedPtrAtomicTest::testRelease() {
    int a = 5;
    SharedPtrAtomic<int> p1(new int(a));
    WeakPtrAtomic<int> p2(p1);
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p1.release();
    assert(p1.useCount() == 0 && p2.useCount() == 1);
    assert(p1.get() == nullptr);
    p2.release();
    assert(p1.useCount() == 0 && p2.useCount() == 0);
}

void SharedPtrAtomicTest::testCopyOperator() {
    int a = 5;
    SharedPtrAtomic<int> p1(new int(a));
    SharedPtrAtomic<int> p2(new int());
    assert(p2.get() != p1.get());
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p2 = p1;
    assert(p2.get() == p1.get() && *p2.get() == a);
    assert(p1.useCount() == p2.useCount() && p2.useCount() == 2);
}

void SharedPtrAtomicTest::testMoveOperator() {
    int a = 5;
    SharedPtrAtomic<int> p1(new int(a));
    SharedPtrAtomic<int> p2(new int());
    assert(p2.get() != p1.get());
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p2 = std::move(p1);
    assert(*p2.get() == a && p1.get() == nullptr);
    assert(p1.useCount() == 0 && p2.useCount() == 1);
}

void SharedPtrAtomicTest::testSwap() {
    int a = 15, b = 500;
    SharedPtrAtomic<int> p1(new int(a));
    SharedPtrAtomic<int> p2(new int(b));
    SharedPtrAtomic<int> p3(p2);
    SharedPtrAtomic<int> p4(p3);
    SharedPtrAtomic<int> p5(p1);
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

void SharedPtrAtomicTest::testUnique() {
    int a = 15;
    SharedPtrAtomic<int> p1(new int(a));
    SharedPtrAtomic<int> p2(new int());
    assert(p1.unique());
    p2 = p1;
    assert(!p1.unique());
    assert(!p2.unique());
    p2.release();
    assert(p1.unique());
}

//тесты для Atomic
void SharedPtrAtomicTest::testThreading() {
    SharedPtrAtomic<int> sp(new int(100));

    auto thread_func = [&sp]() {
        // В каждом потоке копируем указатель
        SharedPtrAtomic<int> temp = sp;
        assert(*temp == 100);
    };

    // Создаем несколько потоков
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(thread_func));
    }

    // Ждём завершения потоков
    for (auto& t : threads) {
        t.join();
    }

    // После завершения всех потоков счётчик ссылок должен быть 1
    assert(sp.useCount() == 1);
}

void SharedPtrAtomicTest::testAssignmentTreading() {
    SharedPtrAtomic<int> sp1(new int(200));

    auto thread_func = [&sp1]() {
        SharedPtrAtomic<int> sp2;
        sp2 = sp1;
        assert(*sp2 == 200);
    };

    // Создаем несколько потоков
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(thread_func));
    }

    // Ждём завершения потоков
    for (auto& t : threads) {
        t.join();
    }
    assert(sp1.useCount() == 1);
}

void SharedPtrAtomicTest::test() {
    testThreading();
    testAssignmentTreading();
    testConstructors();
    testGet();
    testSwap();
    testOperators();
    testUnique();
    testRelease();
    testCopyOperator();
    testMoveOperator();
    testIsNull();
    testUseCount();
    testRelease();
    std::cout << "All SharedPtrAtomic tests passed!" << std::endl;
}