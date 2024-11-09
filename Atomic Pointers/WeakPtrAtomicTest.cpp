#include "WeakPtrAtomicTest.h"
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include "SharedPtrAtomic.h"
#include "WeakPtrAtomic.h"

class TestAccessClass{
public:
    static bool check() {
        return true;
    }
};

void WeakPtrAtomicTest::testConstructors() {
    int a = 50;
    WeakPtrAtomic<int> p1;
    assert(p1.get() == nullptr);//empty

    WeakPtrAtomic<int> p2(new int (a));
    assert(*p2.get() == a);//from ptr

    WeakPtrAtomic<int> p3(p2);
    assert(p3.get() == p2.get());;
    assert(*p3.get()==a && *p2.get() == a); // copy

    WeakPtrAtomic<int> p4(std::move(p2));
    assert(p2.isNull() && *p4.get() == a);//move

    SharedPtrAtomic<int> s_p (new int (a));
    WeakPtrAtomic<int> p5 (s_p);
    assert(p5.get() == s_p.get());
}

void WeakPtrAtomicTest::testOperators() {
    //*
    int a = 5;
    WeakPtrAtomic<int> p1(new int(a));
    assert(*p1.get() == *p1);
    assert(*p1.get() == a);

    //->
    WeakPtrAtomic<TestAccessClass> p2(new TestAccessClass());
    assert(p2 -> check());
}

void WeakPtrAtomicTest::testRelease() {
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

void WeakPtrAtomicTest::testSwap() {

    int a = 15, b = 500;
    WeakPtrAtomic<int> p1(new int(a));
    WeakPtrAtomic<int> p2(new int(b));
    WeakPtrAtomic<int> p3(p2);
    WeakPtrAtomic<int> p4(p3);
    WeakPtrAtomic<int> p5(p1);
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

void WeakPtrAtomicTest::testCopyAssignment() {
    int a = 5;
    WeakPtrAtomic<int> p1(new int(a));
    WeakPtrAtomic<int> p2(new int());
    assert(p2.get() != p1.get());
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p2 = p1;
    assert(p2.get() == p1.get() && *p2.get() == a);
    assert(p1.useCount() == p2.useCount() && p2.useCount() == 2);
}

void WeakPtrAtomicTest::testMoveAssignment() {
    int a = 5;
    WeakPtrAtomic<int> p1(new int(a));
    WeakPtrAtomic<int> p2(new int());
    assert(p2.get() != p1.get());
    assert(p1.useCount() == 1 && p2.useCount() == 1);
    p2 = std::move(p1);
    assert(*p2.get() == a && p1.get() == nullptr);
    assert(p1.useCount() == 0 && p2.useCount() == 1);
}

void WeakPtrAtomicTest::testIsNull() {
    WeakPtrAtomic<int> p1;
    assert(p1.isNull());
}

void WeakPtrAtomicTest::testUseCount() {
    int a = 5;
    SharedPtrAtomic<int> p1(new int(a));
    WeakPtrAtomic<int> p2(p1);
    assert(p2.useCount() == 1 && p1.useCount() == 1);
    WeakPtrAtomic<int> p3(p1);
    assert(p3.useCount() == 2 && p1.useCount() == 1 && p2.useCount() == 2);
}

void WeakPtrAtomicTest::testGet() {
    int a = 5;
    WeakPtrAtomic<int> p1(new int(a));
    assert(*p1.get() == a);
}

void WeakPtrAtomicTest::testUnique() {
    int a = 15;
    WeakPtrAtomic<int> p1(new int(a));
    WeakPtrAtomic<int> p2(new int());
    assert(p1.unique());
    p2 = p1;
    assert(!p1.unique());
    assert(!p2.unique());
    p2.release();
    assert(p1.unique());
}

void WeakPtrAtomicTest::testLock() {
    int a = 100;
    SharedPtrAtomic<int> p1(new int(a));
    WeakPtrAtomic<int> p2(p1);
    SharedPtrAtomic<int> p3;
    SharedPtrAtomic<int> p4;
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

// Функция для проверки валидности WeakPtr в нескольких потоках
void WeakPtrAtomicTest::testThreading() {
    SharedPtrAtomic<int> sp(new int(100));
    WeakPtrAtomic<int> wp = sp;

    auto thread_func = [&wp]() {
        // Каждый поток пытается создать SharedPtr из WeakPtr
        SharedPtrAtomic<int> temp = wp.lock();  // lock пытается получить SharedPtr
        if (temp.get()) {
            assert(*temp == 100);  // Если объект существует, проверяем значение
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(thread_func));
    }

    // Ждём завершения потоков
    for (auto& t : threads) {
        t.join();
    }

}

// Функция для тестирования уничтожения объекта, на который указывает WeakPtr
void WeakPtrAtomicTest::testExpiration() {
    WeakPtrAtomic<int> wp;

    {
        SharedPtrAtomic<int> sp(new int(200));
        wp = sp;
        assert(!wp.expired());

        SharedPtrAtomic<int> sp_from_wp = wp.lock();
        assert(sp_from_wp.get());               // Указатель должен быть валидным
        assert(*sp_from_wp == 200);
    }


    assert(wp.expired());
    SharedPtrAtomic<int> sp_from_wp = wp.lock();
    assert(!sp_from_wp.get());

}

// Функция для многопоточного присваивания WeakPtr
void WeakPtrAtomicTest::testAssignmentInThreads() {
    SharedPtrAtomic<int> sp(new int(300));
    WeakPtrAtomic<int> wp1 = sp;

    auto thread_func = [&wp1]() {
        WeakPtrAtomic<int> wp2;
        wp2 = wp1;
        SharedPtrAtomic<int> sp_from_wp = wp2.lock();
        if (sp_from_wp.get()) {
            assert(*sp_from_wp == 300);
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(thread_func));
    }

    for (auto& t : threads) {
        t.join();
    }

    assert(sp.useCount() == 1);
    assert(!wp1.expired());
}

void WeakPtrAtomicTest::test() {
    testConstructors();
    testOperators();
    testRelease();
    testSwap();
    testCopyAssignment();
    testMoveAssignment();
    testIsNull();
    testUseCount();
    testGet();
    testUnique();
    testLock();
    testThreading();
    testExpiration();
    testAssignmentInThreads();

    std::cout << "All WeakPtrAtomic tests passed!" << std::endl;
}




