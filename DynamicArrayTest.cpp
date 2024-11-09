#include "Exception.h"
#include "DynamicArray.h"
#include <cassert>
#include "DynamicArrayTest.h"


void DynamicArrayTest::testConstructors(){

    double elems[6] = { 0.0, 1, 2.0, 3.0, 4.0, 5.0 };

    DynamicArray<double> arr2(7);
    assert(arr2.getSize() == 7);
    try {
        DynamicArray<double> arr_(-1);
    }
    catch (IndexOutOfRange& ex) {}


    DynamicArray<double> arr3(elems, 6);
    assert(arr3.getSize() == 6);
    for (int i = 0; i < arr3.getSize(); i++) {
        assert(arr3.get(i) == elems[i]);
    }
    try {
        DynamicArray<double> arr_(elems, -1);
        // ;
    }
    catch (IndexOutOfRange& ex) {}


    DynamicArray<double> arr4(arr3);
    assert(arr4.getSize() == arr3.getSize());
    for (int i = 0; i < arr4.getSize(); i++) {
        assert((arr4.get(i) - arr3.get(i)) < 0.000001);
    }

}

void DynamicArrayTest::testSet() {

    double elems[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    DynamicArray<double> arr1(elems, 7);
    int ind1 = 0, ind2 = 6, ind3 = 3;
    double val = 20.0;
    arr1.set(ind1, val);
    arr1.set(ind2, val);
    arr1.set(ind3, val);
    assert(arr1.get(ind1) == val && arr1.get(ind2) == val && arr1.get(ind3) == val);
    try {
        arr1.set(-20, 100.20);
    }
    catch (IndexOutOfRange& ex) {}

    try {
        arr1.set(7, 100.20);
    }
    catch (IndexOutOfRange& ex) {}
}

void DynamicArrayTest::testGet() {
    double elems[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    DynamicArray<double> arr(elems, 7);
    for (int i = 0; i < 7; ++i) {
        assert(arr.get(i) == elems[i]);
    }
    try {
        arr.get(-1);
    }
    catch (IndexOutOfRange& ex) {}
    try {
        arr.get(7);
    }
    catch (IndexOutOfRange& ex) {}
}

void DynamicArrayTest::testGetSize() {
    double elems[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    DynamicArray<double> arr(elems, 7);
    assert(arr.getSize() == 7);
}

void DynamicArrayTest::testResize() {
    double elems[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    DynamicArray<double> arr(elems, 7);
    try {
        arr.resize(-1);
    }
    catch (IndexOutOfRange& ex) {}

    arr.resize(11);
    assert(arr.getSize() == 11);
    for (int i = 0; i < 7; ++i) {
        assert(arr.get(i) == elems[i]);
    }
    arr.resize(3);
    assert(arr.getSize() == 3);
    for (int i = 0; i < 3; ++i) {
        assert(arr.get(i) == elems[i]);
    }
}

void DynamicArrayTest::testOperatorAccess() {
    double elems[6] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 };
    DynamicArray<double> array(elems, 6);
    assert(array[2] == array.get(2));
}

void DynamicArrayTest::test() {

    testConstructors();
    testSet();
    testGet();
    testGetSize();
    testResize();
    testOperatorAccess();

    std::cout << "All DynamicArray tests passed!" << std::endl;
}