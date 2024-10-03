//
// Created by Kate on 14.05.2024.
//

#ifndef LAB2_IMMUTABLESEQUENCE_H
#define LAB2_IMMUTABLESEQUENCE_H

#include "cmake-build-debug/Sequence.h"

template <class T>
class ImmutableSequence: public Sequence<T> {
public:
    //destructor
    virtual ~ImmutableSequence() = default;

    //methods
    virtual ImmutableSequence<T> *getSubSequence(int startIndex, int endIndex) = 0;
    virtual ImmutableSequence<T> *append(const T& item) = 0;
    virtual ImmutableSequence<T> *prepend(const T& item) = 0;
    virtual ImmutableSequence<T> *insertAt(const T& item, int index) = 0;
    virtual ImmutableSequence<T> *concat(const Sequence <T>&) = 0;
    virtual ImmutableSequence<T> *set(int index,const T& item) = 0;
    virtual bool operator==(const ImmutableSequence<T>& other) = 0;

};


#endif //LAB2_IMMUTABLESEQUENCE_H
