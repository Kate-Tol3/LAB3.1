
#ifndef TESTMUTABLESEQUENCE_H
#define TESTMUTABLESEQUENCE_H

#include "Exception.h"
#include "MutableSequence.h"
#include "Sequence.h"
#include <cassert>

#include "MutableListSequence.h"

template<template<class> class MutableSequence>
class MutableSequenceTest {
public:

    void testConstructors() {
        double elems[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

        MutableSequence<double> mut_seq;
        assert(mut_seq.getLength() == 0);

        MutableSequence<double> mut_seq1(6);
        assert(mut_seq1.getLength() == 6);
        try {
            MutableSequence<double> mut_seq_(-1);
        } catch (IndexOutOfRange &ex) {}
        catch (EmptyListException &ex){}

        MutableSequence<double> mut_seq2(elems, 6);
        assert(mut_seq2.getLength() == 6);
        for (int i = 0; i < mut_seq2.getLength(); ++i) {
            assert(mut_seq2.get(i) == elems[i]);
        }
        try {
            MutableSequence<double> mut_seq_(elems, -1);
            // ;
        } catch (IndexOutOfRange &ex) {}


        MutableSequence<double> mut_seq3(mut_seq2);
        assert(mut_seq3.getLength() == mut_seq2.getLength());
        for (int i = 0; i < mut_seq3.getLength(); ++i) {
            assert(mut_seq3.get(i) == mut_seq2.get(i));
        }
    }

    void testGet() {
        double elems[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
        MutableSequence<double> mut_seq(elems, 6);
        for (int i = 0; i < 6; ++i) {
            assert(mut_seq.get(i) == elems[i]);
        }
        try {
            mut_seq.get(-1);
            // ;
        } catch (IndexOutOfRange &ex) {}
        try {
            mut_seq.get(6);
            // ;
        } catch (IndexOutOfRange &ex) {}
    }

    void testGetFirst() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        MutableSequence<int> mut_seq(m, length);
        assert(mut_seq.getFirst() == m[0]);
        try {
            MutableSequence<int> mut_seq_except;
            mut_seq_except.getFirst();
            assert(false);
        } catch (IndexOutOfRange&) {}
        catch (EmptyListException&) {}
    }

    void testGetLast() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        MutableSequence<int> mut_seq(m, length);
        assert(mut_seq.getLast() == m[6]);
        try {
            MutableSequence<int> mut_seq_except;
            mut_seq_except.getLast();
            assert(false);
        } catch (IndexOutOfRange&) {}
        catch (EmptyListException&) {}
    }

    void testGetLength() {
        double elems[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
        MutableSequence<double> mut_seq(elems, 6);
        assert(mut_seq.getLength() == 6);
    }

    void testAppend() {
        double elems[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
        MutableSequence<double> mut_seq(elems, 6);
        double val = 100;
        mut_seq.append(val);
        assert(mut_seq.getLength() == 7);
        for (int i = 0; i < 6; ++i) {
            assert(mut_seq.get(i) == elems[i]);
        }
        assert(mut_seq.get(6) == val);

        MutableSequence<double> mut_seq2;
        mut_seq2.append(val);
        assert(mut_seq2.getLength() == 1);
        assert(mut_seq2.getFirst() == val);
        assert(mut_seq2.getLast() == val);
    }

    void testPrepend() {
        double elems[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
        MutableSequence<double> mut_seq(elems, 6);
        double val = 100;
        mut_seq.prepend(val);
        assert(mut_seq.getLength() == 7);
        assert(mut_seq.get(0) == val);
        for (int i = 1; i < 7; ++i) {
            assert(mut_seq.get(i) == elems[i - 1]);
        }

        MutableSequence<double> mut_seq2;
        mut_seq2.prepend(val);
        assert(mut_seq2.getLength() == 1);
        assert(mut_seq2.getFirst() == val);
        assert(mut_seq2.getLast() == val);
    }

    void testInsertAt() {

        double elems[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
        MutableSequence<double> mut_seq(elems, 6);
        double val = 100;
        double ind1 = 0, ind2 = 3, ind3 = 5;

        mut_seq.insertAt(val, ind1);
        mut_seq.insertAt(val, ind2);
        mut_seq.insertAt(val, ind3);
        assert(mut_seq.getLength() == 9);

        for (int i = 0 ; i< mut_seq.getLength(); i++){
            if (i == 0 || i == 3 || i == 5){
                assert(mut_seq.get(i) == val);
            }
        }
        double ins_ind;

        try {
            ins_ind = -1;
            mut_seq.insertAt(ins_ind, 10);
            // ;
        } catch (IndexOutOfRange &ex) {}
        try {
            ins_ind = 6;
            mut_seq.insertAt(ins_ind, 10);
            // ;
        } catch (IndexOutOfRange &ex) {}

        MutableSequence<double> mut_seq2;
        mut_seq2.insertAt(val, 0);
        assert(mut_seq2.getLength() == 1);
        assert(mut_seq2.getFirst() == val);
        assert(mut_seq2.getLast() == val);
    }

    void testGetSubsequence() {
        int length = 7;
        int m[7] = {0, 1, 2, 3, 4, 5, 6};
        MutableSequence<int> mut_seq(m, length);
        int startIndex = 2;
        int endIndex = 5;
        MutableSequence<int>* result = mut_seq.getSubsequence(startIndex, endIndex);
        for (int i = startIndex; i <= endIndex; ++i) {
            assert(result->get(i - startIndex) == m[i]);
        }
        try {
            mut_seq.getSubsequence(0, length);
            assert(false);
        } catch (IndexOutOfRange&) {}
        try {
            mut_seq.getSubsequence(-1, 0);
            assert(false);
        } catch (IndexOutOfRange&) {}
        try {
            mut_seq.getSubsequence(1, 0);
            assert(false);
        } catch (IndexOutOfRange&) {}
    }

    void testConcat() {
        double elems1[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
        double elems2[3] = {6.0, 7.0, 8.0};
        double elems3[9] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
        MutableSequence<double> mut_seq2(elems2, 3);
        MutableSequence<double> mut_seq1(elems1, 6);
        SharedPtr<Sequence<double>> result(mut_seq1.concat(mut_seq2));
        assert(result->getLength() == 9);
        for (int i =0; i < 9; i++){
            assert(result->get(i) == elems3[i]);
        }
    }

    void testOperatorAccess() {
        double elems[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
        MutableSequence<double> mut_seq2(elems, 6);
        assert(mut_seq2[2] == mut_seq2.get(2));
    }

    void test() {
        testConstructors();
        testGet();
        testGetLength();
        testAppend();
        testPrepend();
        testInsertAt();
        testConcat();
        testGetSubsequence();
        testGetFirst();
        testGetLast();
        testOperatorAccess();

        std:: cout << "All MutableSequence tests passsed!" <<  std:: endl;
    }
};

#endif //TESTMUTABLESEQUENCE_H
