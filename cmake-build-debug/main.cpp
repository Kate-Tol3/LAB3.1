#include <iostream>
#include "WeakPtr.h"
#include "ShrdPtr.h"
#include "Test.h"

int main() {
    Test test;
    test.testAll();
    // int a = 10;
    // int b = 5;

    // ShrdPtr<int> shrd_ptr1(new int());
    // *shrd_ptr1 = a;
    //
    // WeakPtr<int> weak_ptr(shrd_ptr1);
    //
    //
    // std::cout << *shrd_ptr1 << std::endl;
    // std::cout << *weak_ptr << std::endl;
    // std::cout << shrd_ptr1.useCount()  << " " << weak_ptr.useCount() << std::endl;
    //
    // std::cout << std::endl;
    //
    // std::cout << *shrd_ptr1 << std::endl;
    // std::cout << *weak_ptr << std::endl;
    // std::cout << shrd_ptr1.useCount()  << " " << weak_ptr.useCount() << std::endl;
    // std::cout << std::endl;
    // auto ptr = weak_ptr.lock();
    // std::cout << *weak_ptr << std::endl;
    // std::cout << shrd_ptr1.useCount()  << " " << weak_ptr.useCount() << std::endl;



    return 0;
}
