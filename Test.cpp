#include "Test.h"
#include "LinkedListTest.h"
#include "MutableListSequence.h"
#include "MutableArraySequence.h"


void Test::testAll() {
    testUnqPtr();
    testShrdPtr();
    testWeakPtr();
    testShrdPtrAtomic();
    testWeakPtrAtomic();
    testLinkedList();
    testMutableSequence();
}

void Test::testUnqPtr() {
    UnqPtrTest u_ptr;
    u_ptr.test();
}

void Test::testShrdPtr() {
    ShrdPtrTest shrd_ptr;
    shrd_ptr.test();
}

void Test::testWeakPtr() {
    WeakPtrTest weak_ptr;
    weak_ptr.test();
}

void Test::testShrdPtrAtomic() {
    ShrdPtrAtomicTest shrd_ptr_atom;
    shrd_ptr_atom.test();
}

void Test::testWeakPtrAtomic() {
    WeakPtrAtomicTest wk_ptr_atom;
    wk_ptr_atom.test();
}

void Test::testLinkedList() {
    LinkedListTest ll_t;
    ll_t.test();
}

void Test::testMutableSequence() {
    std::cout << "\ntesting MutableListSequence..." << std::endl;
    MutableSequenceTest<MutableListSequence> mls;
    mls.test();

    std::cout << "testing MutableArraySequence..." << std::endl;
    MutableSequenceTest<MutableArraySequence> mas;
    mas.test();
}
