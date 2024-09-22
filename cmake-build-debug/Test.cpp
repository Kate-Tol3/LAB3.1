//
// Created by Kate on 19.09.2024.
//

#include "Test.h"

#include "ShrdPtr.h"
#include "UnqPtrTest.h"


void Test::testAll() {
    testUnqPtr();
    // testShrdPtr();
    // testWeakPtr();

}

void Test::testUnqPtr() {
    UnqPtrTest u_ptr;
    u_ptr.test();
}

// void Test::testShrdPtr() {
//     ShrdPtrTest shrd_ptr;
//     shrd_ptr.test();
// }
//
// void Test::testWeakPtr() {
//     WeakPtrTest weak_ptr;
//     weak_ptr.test();
// }


