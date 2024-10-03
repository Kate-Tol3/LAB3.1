
#ifndef LISTSEQUENCE_H
#define LISTSEQUENCE_H

#include "cmake-build-debug/LinkedList.h"
#include "ImmutableSequence.h"
#include "Exceptions.h"

template <class T>
class ImmutableListSequence: public virtual ImmutableSequence<T> {
private:
    LinkedList<T> *seq_list;
public:
    //constructors
    ImmutableListSequence(): seq_list(new LinkedList<T>()){};
    ImmutableListSequence(T* items, int count): seq_list(new LinkedList<T>(items, count)){};
    explicit ImmutableListSequence(const int count):seq_list(new LinkedList<T>(count)){};
    explicit ImmutableListSequence(const LinkedList<T> &list): seq_list(new LinkedList<T>(list)){};
    ImmutableListSequence(const ImmutableListSequence<T>& other): seq_list(new LinkedList<T>(*(other.seq_list))){};
    explicit ImmutableListSequence(const Sequence<T>& other): seq_list(new LinkedList<T>(other)) {}

    //destructor
    virtual ~ImmutableListSequence() {
        delete seq_list;
    }

    //methods
    const T& getFirst() const override {
        if (seq_list->getLength() == 0) throw IndexOutOfRange();
        return seq_list->getFirst();
    }

    const T& getLast() const override {
        if (seq_list->getLength() == 0) throw IndexOutOfRange();
        return seq_list->getLast();
    }

    const T& get(int index) const override {
        if (seq_list->getLength() == 0 || seq_list->getLength() <= index || index < 0) throw IndexOutOfRange();
        return seq_list->get(index);
    }

    int getLength() const override {
        return seq_list->getLength();
    }

    ImmutableListSequence<T> *getSubSequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || startIndex >= seq_list->getLength()|| endIndex >= seq_list->getLength()) throw IndexOutOfRange();
        auto *new_list = seq_list->getSubList(startIndex, endIndex);
        return new ImmutableListSequence<T>(*new_list);
    }

    ImmutableListSequence<T> *append(const T& item) override {
        auto *new_list = new ImmutableListSequence<T>(*seq_list);
        new_list->seq_list->append(item);
        return new_list;
    }

    ImmutableListSequence<T> *prepend(const T& item) override {
        auto *new_list = new ImmutableListSequence<T>(*seq_list);
        new_list->seq_list->prepend(item);
        return new_list;
    }

    ImmutableListSequence<T> * insertAt(const T& item, int index) override {
        auto *new_list = new ImmutableListSequence<T>(*seq_list);
        new_list->seq_list->insertAt(item,index);
        return new_list;
    }

     ImmutableListSequence<T> *concat(const Sequence<T> &list) override {
        auto *new_list = new ImmutableListSequence<T>(*seq_list);
        int size1 = new_list->getLength(), size2 =  list.getLength();
        int len = size1 + size2;
        for (int i = size1; i < len; i++){
            new_list->seq_list->append(list.get(i - size1));
        }
        return  new_list;
     }

    ImmutableListSequence<T> *set(int index,const T& item) override{
        auto *new_list = new ImmutableListSequence<T>(*this);
        new_list->seq_list->set(item, index);
        return new_list;

    }

     void print() const{
        this->seq_list->print();
    }

    const T& operator[] (int index) const override{
        return (seq_list->get(index));
    }

    T& operator[] (int index){
        return (seq_list->get(index));
    }

    bool operator==(const ImmutableSequence<T>& other)override{
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
};

#endif //LISTSEQUENCE_H
