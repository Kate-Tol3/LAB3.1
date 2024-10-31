
#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "ShrdPtr.h"

template <class T>
class Sequence {
public:
    //destructor
    virtual ~Sequence() = default;

    //methods
    virtual const T& getFirst() const = 0;// 1 const ?
    virtual const T& getLast() const = 0;// 1 const ?

    virtual const T& get(int index) const = 0;// 1 const ?
    virtual int getLength() const = 0;

    virtual ShrdPtr<Sequence<T>> concat(const Sequence <T>&) = 0;
    virtual ShrdPtr<Sequence<T>> getSubSequence(int startIndex, int endIndex) = 0;
    virtual void print() const = 0;
    virtual const T& operator[](int index) const = 0;

};

#endif //SEQUENCE_H
