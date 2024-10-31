#include "LinkedListTest.h"

#include <cassert>
#include "LinkedList.h"
#include "Exception.h"

void LinkedListTest::testConstructors() {

    LinkedList<int> list1{};
    assert(list1.getLength() == 0);

    int elems[6] = { 0, 1, 2, 3, 4, 5 };
    LinkedList<int> list2(elems, 6);
    assert(list2.getLength() == 6);
    for (int i = 0; i < list2.getLength(); i++) {
        assert(list2.get(i) == elems[i]);
    }
    try {
        LinkedList<int> list_(elems, -1);
    } catch (IndexOutOfRange& ex) {}

    LinkedList<int> list3(list2);
    assert(list3.getLength() == list2.getLength());
    for (int i = 0; i < list3.getLength(); i++) {
        assert(list2.get(i) == list3.get(i));
    }
}

void LinkedListTest::testGet() {
    double elems[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    LinkedList<double> list(elems, 7);
    for (int i = 0; i < 7; ++i) {
        assert(list.get(i) == elems[i]);
    }
    try {
        list.get(-1);
    } catch (IndexOutOfRange& ex) {}
    try {
        list.get(7);
    } catch (IndexOutOfRange& ex) {}
}

void LinkedListTest::testGetSize() {
    double elems[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    LinkedList<double> arr(elems, 7);
    assert(arr.getLength() == 7);
}

void LinkedListTest::testGetFirst() {
    double elems[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    LinkedList<double> list(elems, 7);
    assert(list.getFirst() == elems[0]);

    LinkedList<double> list_;
    try {
        list_.getFirst();
    } catch (IndexOutOfRange& ex) {}
    catch (EmptyListException& ex) {}
}

void LinkedListTest::testGetLast() {
    double elems[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    LinkedList<double> list(elems, 7);
    assert(list.getLast() == elems[6]);

    LinkedList<double> list_;
    try {
        list_.getFirst();
    } catch (IndexOutOfRange& ex) {}
    catch (EmptyListException& ex) {}
}

void LinkedListTest::testAppend() {
    double elems[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    LinkedList<double> list(elems, 7);
    int val = 100;
    list.append(val);
    assert(list.getLength() == 8);
    for (int i = 0; i < 7; ++i) {
        assert(list.get(i) == elems[i]);
    }
    assert(list.get(7) == val);

    LinkedList<double> blank_list;
    blank_list.append(val);
    assert(blank_list.getLength() == 1);
    assert(blank_list.getLast() == val);
    assert(blank_list.getFirst() == val);
}

void LinkedListTest::testPrepend() {
    double elems[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    LinkedList<double> list(elems, 7);
    int val = 100;
    list.prepend(val);
    assert(list.getLength() == 8);
    assert(list.get(0) == val);
    for (int i = 1; i < 8; ++i) {
        assert(list.get(i) == elems[i - 1]);
    }

    LinkedList<double> blank_list;
    blank_list.prepend(val);
    assert(blank_list.getLength() == 1);
    assert(blank_list.getLast() == val);
    assert(blank_list.getFirst() == val);
}

void LinkedListTest::testInsertAt() {
    double elems[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    LinkedList<double> list(elems, 7);
    int val = 100; int ind1 = 0, ind2 = 3, ind3 = 6;
    list.insertAt(val, ind1);
    list.insertAt(val, ind2);
    list.insertAt(val, ind3);

    assert(list.getLength() == 10);
    for (int i = 0; i < list.getLength(); i++) {
        if (i == 0 || i == 3 || i == 6) {
            assert(list.get(i) == val);
        }
    }

    try {
        list.insertAt(100, -1);
    } catch (IndexOutOfRange& ex) {}
    catch (EmptyListException& ex) {}

    try {
        list.insertAt(100, 7);
    } catch (IndexOutOfRange& ex) {}
    catch (EmptyListException& ex) {}

    LinkedList<double> blank_list1;
    blank_list1.insertAt(val, 0);
    assert(blank_list1.getLength() == 1);
    assert(blank_list1.getLast() == val);
    assert(blank_list1.getFirst() == val);
}

void LinkedListTest::testGetSubList() {
    double elems[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    LinkedList<double> list(elems, 7);
    int startIndex = 2;
    int endIndex = 5;
    LinkedList<double>* result = list.getSubList(startIndex, endIndex);
    for (int i = startIndex; i <= endIndex; ++i) {
        assert(result->get(i - startIndex) == elems[i]);
    }
    try {
        list.getSubList(0, 7);
    } catch (IndexOutOfRange& ex) {}
    catch (EmptyListException& ex) {}
    try {
        list.getSubList(-1, 0);
    } catch (IndexOutOfRange& ex) {}
    catch (EmptyListException& ex) {}
    try {
        list.getSubList(1, 0);
    } catch (IndexOutOfRange& ex) {}
    catch (EmptyListException& ex) {}

}

void LinkedListTest::testConcat() {
    double elems1[7] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    LinkedList<double> list1(elems1, 7);
    double elems2[3] = { 7.0, 8.0, 9.0 };
    LinkedList<double> list2(elems2, 3);
    LinkedList<double>* result = list1.concat(&list2);
    double elems3[10] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    for (int i = 0; i < result->getLength(); i++) {
        assert(result->get(i) == elems3[i]);
    }

}

void LinkedListTest::testOperatorEqual() {
    double elems[6] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 };
    LinkedList<double> list1(elems, 6);
    LinkedList<double> list2(elems, 6);
    assert(list1 == list2);
}

void LinkedListTest::test() {
    testConstructors();
    testGet();
    testGetSize();
    testGetFirst();
    testGetLast();
    testAppend();
    testPrepend();
    testInsertAt();
    testGetSubList();
    testConcat();
    testOperatorEqual();

    std::cout << "All LinkedList tests passed!" << std::endl;
}
