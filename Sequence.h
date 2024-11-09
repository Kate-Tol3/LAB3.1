
#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "SharedPtr.h"

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

    virtual Sequence<T>* getSubsequence(int startIndex, int endIndex) const = 0;
    virtual Sequence<T>* concat(const Sequence<T>& secondSequence) const = 0;
    virtual void print() const = 0;
    virtual const T& operator[](int index) const = 0;

};

#endif //SEQUENCE_H
