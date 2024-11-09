#pragma once

#include <stdexcept>
#include "MutableSequence.h"
#include "Sequence.h"
#include "LinkedList.h"
#include "ShrdPtr.h"

template <typename T>
class MutableListSequence: public MutableSequence<T> {
private:
    ShrdPtr<LinkedList<T>> list;

public:
    MutableListSequence(const T* items, int size): list(new LinkedList<T>(items, size)) {}
    MutableListSequence(): list(new LinkedList<T>()) {}
    MutableListSequence(int size): list(new LinkedList<T>(size)) {}
    MutableListSequence(const MutableListSequence<T>& other): list(new LinkedList<T>(*other.list)) {}
    MutableListSequence(const Sequence<T>& other): list(new LinkedList<T>(other)) {}
    MutableListSequence(const LinkedList<T>& other): list(new LinkedList<T>(other)) {}

    ~MutableListSequence() override {}

    T& operator [] (int index) {
        return (*list)[index];
    }

    const T& operator [] (int index) const override {
        return (*list)[index];
    }

    MutableListSequence<T>& operator=(const MutableListSequence<T>& other) {
        *list = *other.list;
        return *this;
    }

    const T& getFirst() const override {
        return list->getFirst();
    }

    const T& getLast() const override {
        return list->getLast();
    }

    const T& get(int index) const override {
        return (*list)[index];
    }

    T& getFirst() {
        return list->getFirst();
    }

    T& getLast(){
        return list->getLast();
    }

    T& get(int index) {
        return list->get(index);
    }

    void set(int index, const T& value) override {
        return list->set(index, value);
    }

    int getLength() const override {
        return list->getLength();
    }

    void append(const T& item) override {
        list->append(item);
    }

    void prepend(const T& item) override {
        list->prepend(item);
    }

    void insertAt(const T& item, int index) override {
        list->insertAt(item, index);
    }

    // MutableListSequence<T>* getSubsequence(int startIndex, int endIndex) const override {
    //     if (startIndex > endIndex || startIndex < 0 || endIndex >= this->getLength()) throw IndexOutOfRange();
    //     return new MutableListSequence<T>(*this->list->getSubsequence(startIndex, endIndex));
    // }

    MutableListSequence<T>* getSubsequence(int startIndex, int endIndex) const override {
        if (startIndex > endIndex || startIndex < 0 || endIndex >= this->getLength()) throw IndexOutOfRange();
        auto* subsequence = this->list->getSubsequence(startIndex, endIndex);
        return new MutableListSequence<T>(*subsequence);
    }
    //
    // MutableListSequence<T>* getSubSequence(int startIndex, int endIndex) const override {
    //
    //     // Получаем подсписок с помощью метода getSubList класса LinkedList
    //     ShrdPtr<LinkedList<T>> sub_list = ShrdPtr<LinkedList<T>>(this->seq_list->getSubsequence(startIndex, endIndex));
    //
    //     // Возвращаем подсписок как MutableListSequence
    //     return new MutableListSequence<T>(*sub_list);
    //
    // }

    MutableListSequence<T>* concat(const Sequence<T>& other) const override {
        LinkedList<T> bufList(other);
        return new MutableListSequence<T>(*list->concat(&bufList));
    }

    bool operator==(const MutableSequence<T>& other) const override{
            if (this == &other) return true;
            if (this->getLength() == other.getLength()){
                for (int i = 0; i < this->getLength(); ++i) {
                    if ((*this)[i] != (other)[i]) {
                        return false;
                    }
                }
                return true;
            }
            return false;
    }

    void print() const override{
        this->list->print();
    }

};