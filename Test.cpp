#include "Test.h"
#include "LinkedListTest.h"
#include "MutableListSequence.h"
#include "MutableArraySequence.h"
#include "SharedPtrTest.h"
#include "UnqPtrTest.h"
#include "WeakPtrTest.h"
#include "Atomic Pointers/SharedPtrAtomicTest.h"
#include "Atomic Pointers/WeakPtrAtomicTest.h"
#include "MutableSequenceTest.h"


void Test::testAll() {
    testUnqPtr();
    testSharedPtr();
    testWeakPtr();
    testSharedPtrAtomic();
    testWeakPtrAtomic();
    testLinkedList();
    testMutableSequence();
}

void Test::testUnqPtr() {
    UnqPtrTest u_ptr;
    u_ptr.test();
}

void Test::testSharedPtr() {
    SharedPtrTest Shared_ptr;
    Shared_ptr.test();
}

void Test::testWeakPtr() {
    WeakPtrTest weak_ptr;
    weak_ptr.test();
}

void Test::testSharedPtrAtomic() {
    SharedPtrAtomicTest Shared_ptr_atom;
    Shared_ptr_atom.test();
}

void Test::testWeakPtrAtomic() {
    WeakPtrAtomicTest wk_ptr_atom;
    wk_ptr_atom.test();
}

void Test::testLinkedList() {
    LinkedListTest ll_t;
    ll_t.test();
}

void Test::testDynamicArray() {

}


void Test::testMutableSequence() {
    std::cout << "\ntesting MutableListSequence..." << std::endl;
    MutableSequenceTest<MutableListSequence> mls;
    mls.test();

    std::cout << "testing MutableArraySequence..." << std::endl;
    MutableSequenceTest<MutableArraySequence> mas;
    mas.test();
}
