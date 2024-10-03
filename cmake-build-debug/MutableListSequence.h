#ifndef LAB2_MUTABLELISTSEQUENCE_H
#define LAB2_MUTABLELISTSEQUENCE_H

#include "LinkedList.h"
#include "MutableSequence.h"
#include "Exception.h"

template <class T>
class MutableListSequence: public MutableSequence<T> {
private:
    ShrdPtrAtomic<LinkedList<T>> seq_list;

public:
    // Constructors
    MutableListSequence(): seq_list(new LinkedList<T>()) {};
    MutableListSequence(T* items, int count): seq_list(new LinkedList<T>(items, count)) {};
    explicit MutableListSequence(const int count): seq_list(new LinkedList<T>(count)) {};
    explicit MutableListSequence(const LinkedList<T>& list): seq_list(new LinkedList<T>(list)) {};
    
    MutableListSequence(const MutableListSequence<T>& other): seq_list(new LinkedList<T>(*other.seq_list)) {};

    // Methods
    T& getFirst() const override {
        return seq_list->getFirst();
    }

    T& getLast() const override {
        return seq_list->getLast();
    }

    T& get(int index) const override {
        return seq_list->get(index);
    }

    int getLength() const override {
        return seq_list->getLength();
    }

    ShrdPtrAtomic<Sequence<T>> getSubSequence(int startIndex, int endIndex) override {
        // // Проверка на корректность индексов
        // if (startIndex < 0 || endIndex >= seq_list->getLength() || startIndex > endIndex) {
        //     throw IndexOutOfRange();  // Исключение, если индексы некорректны
        // }
        //
        // ShrdPtrAtomic<LinkedList<T>> sublist = ShrdPtrAtomic<LinkedList<T>>(seq_list->getSubList(startIndex, endIndex));
        // this->seq_list = sublist;
        //
        // return ShrdPtrAtomic<Sequence<T>>(sublist);

        // ShrdPtrAtomic<LinkedList<T>> sub_list = ShrdPtrAtomic<LinkedList<T>>(this->seq_list->getSubList(startIndex, endIndex));
        // this->seq_list = sub_list;
        // return ShrdPtrAtomic<Sequence<T>>(sub_list);
        //
        // ShrdPtrAtomic<LinkedList<T>> sub_list = this->seq_list->getSubList(startIndex, endIndex);
        //
        // // Modify the current object to the new subsequence
        // this->seq_list = sub_list;  // Update current list
        //
        // // Return the new subsequence as ShrdPtrAtomic<Sequence<T>>
        // return ShrdPtrAtomic<Sequence<T>>(sub_list.get());
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

    ShrdPtrAtomic<Sequence<T>> concat(const Sequence<T>& list) override {

        // MutableListSequence<T>* temp_seq = dynamic_cast<const MutableListSequence<T>*>(&list);
        //
        // ShrdPtrAtomic<LinkedList<T>> new_list = ShrdPtrAtomic<LinkedList<T>>(this->seq_list->concat(temp_seq->seq_list.get()));
        //
        // this->seq_list = new_list;
        //
        // return ShrdPtrAtomic<Sequence<T>>(new_list);
        //
        // const MutableListSequence<T>* otherList = dynamic_cast<const MutableListSequence<T>*>(&list);
        // if (!otherList) {
        //     throw std::invalid_argument("Invalid sequence type for concatenation.");
        // }
        //
        // // Use the concat method from the LinkedList class
        // ShrdPtrAtomic<LinkedList<T>> new_list = this->seq_list->concat(otherList->seq_list.get());
        //
        // // Modify the current object to the new list
        // this->seq_list = new_list;  // Update current list
        //
        // // Return new list as ShrdPtrAtomic<Sequence<T>>
        // return ShrdPtrAtomic<Sequence<T>>(new_list.get());
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
