#ifndef LAB2_MUTABLELISTSEQUENCE_H
#define LAB2_MUTABLELISTSEQUENCE_H

#include "LinkedList.h"
#include "MutableSequence.h"
#include "Exception.h"

template <class T>
class MutableListSequence: public MutableSequence<T> {
private:
    ShrdPtr<LinkedList<T>> seq_list;

public:
    // Constructors
    MutableListSequence(): seq_list(new LinkedList<T>()) {};
    MutableListSequence(T* items, int count): seq_list(new LinkedList<T>(items, count)) {};
    explicit MutableListSequence(const int count): seq_list(new LinkedList<T>(count)) {};
    explicit MutableListSequence(const LinkedList<T>& list): seq_list(new LinkedList<T>(list)) {};
    
    MutableListSequence(const MutableListSequence<T>& other): seq_list(new LinkedList<T>(*other.seq_list)) {};

    // Methods
    const T& getFirst() const override {
        return seq_list->getFirst();
    }

    const T& getLast() const override {
        return seq_list->getLast();
    }

    const T& get(int index) const override {
        return seq_list->get(index);
    }

    int getLength() const override {
        return seq_list->getLength();
    }

    ShrdPtr<Sequence<T>> getSubSequence(int startIndex, int endIndex) override {

        // Получаем подсписок с помощью метода getSubList класса LinkedList
        ShrdPtr<LinkedList<T>> sub_list = ShrdPtr<LinkedList<T>>(this->seq_list->getSubList(startIndex, endIndex));

        // Возвращаем подсписок как MutableListSequence
        return ShrdPtr<Sequence<T>>(new MutableListSequence<T>(*sub_list));

    }

    void append(const T& item) override {
        seq_list->append(item);
    }

    void prepend(const T& item) override {
        seq_list->prepend(item);
    }

    void insertAt(const T& item, int index) override {
        seq_list->insertAt(item, index);
    }

    void set(int index, const T& item) override {
        seq_list->set(index, item);
    }

    ShrdPtr<Sequence<T>> concat(const Sequence<T>& other) override {
        const auto* otherMutableSeq = dynamic_cast<const MutableListSequence<T>*>(&other);

        // Используем метод concat класса LinkedList для создания нового списка
        ShrdPtr<LinkedList<T>> new_list = ShrdPtr<LinkedList<T>>(this->seq_list->concat(otherMutableSeq->seq_list.get()));

        // Возвращаем новый список как MutableListSequence
        return ShrdPtr<Sequence<T>>(new MutableListSequence<T>(*new_list));
    }

    T& operator[](int index) const override {
        return seq_list->get(index);
    }

    bool operator==(const MutableSequence<T>& other) const override {
      //  return (*seq_list == *dynamic_cast<const MutableListSequence<T>&>(other).seq_list); // приводит объект other ( типа MutableSequence<T>) к  типу MutableListSequence<T>.
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

    bool operator==(const MutableListSequence<T>& other) const {
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

    void print() const override {
        seq_list->print();
    }
};

#endif // LAB2_MUTABLELISTSEQUENCE_H
