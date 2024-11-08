#pragma once

#include <iostream>
#include <stdexcept>
#include "Sequence.h"
#include "LinkedList.h" pu

template <typename T>
class DynamicArray {
protected:
    int size;
    T* array = nullptr;
public:
    DynamicArray(const T* arrayToCopy, int size): size(size) {
        if (size < 0) throw IndexOutOfRange();
        array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = arrayToCopy[i];
        }
    }

    DynamicArray(int size): size(size) {
        if (size < 0) throw IndexOutOfRange();
        array = new T[size];
    }

    DynamicArray(const DynamicArray<T>& other): size(other.getSize()), array(new T[other.getSize()]) {
        for (int i = 0; i < size; ++i) {
            set(i, other.get(i));
        }
    }

    DynamicArray(const LinkedList<T>& other): size(other.getLength()), array(new T[other.getLength()]) {
        for (int i = 0; i < size; ++i) {
            set(i, other.get(i));
        }
    }

    DynamicArray(const Sequence<T>& other): size(other.getLength()), array(new T[other.getLength()]) {
        for (int i = 0; i < size; ++i) {
            set(i, other.get(i));
        }
    }

    ~DynamicArray() {
        delete[] array;
    }

    T& operator[](int index) {
        if (index >= size || index < 0) throw IndexOutOfRange();
        return array[index];
    }

    const T& operator[](int index) const {
        if (index >= size || index < 0) throw IndexOutOfRange();
        return const_cast<T&>(array[index]);
    }

    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        delete array;
        array = new T[other.getSize()];
        for (int i = 0; i < other.getSize(); ++i) {
            array[i] = other.get(i);
        }
        size = other.size;
        return *this; // возвращаем обновленный *this как rvalue;
    }

    T get(int index) const { // возвращает rvalue
        if (index >= size || index < 0) throw IndexOutOfRange();
        return array[index];
    }

    int getSize() const {
        return size;
    }
    void set(int index, const T& value) {
        // исключение выбросит конструкция (*this)[index]
        (*this)[index] = value; // здесь все нормально, происходит стандартное присваивание. Т.е. value копируется в array[index]
    }

    void resize(int newSize) {
        if (newSize < 0) throw IndexOutOfRange();
        T* helpArray = new T[newSize];
        int minSize = newSize < size ? newSize : size;
        for (int i = 0; i < minSize; ++i) {
            helpArray[i] = array[i];
        }
        delete[] array;
        array = helpArray;
        size = newSize;
        if (size == 0) {
            delete[] array;
            array = nullptr;
        }
    }

    void append(const T& item) {
        resize(size + 1);
        array[size - 1] = item;
    }

    void prepend(const T& item) {
        T* helpArray = new T[size + 1];
        helpArray[0] = item;
        for (int i = 0; i < size; ++i) {
            helpArray[i + 1] = array[i];
        }
        delete[] array;
        array = helpArray;
        size = size + 1;
    }

    void insertAt(int index, const T& item) {
        if (index < 0 || index > size) throw IndexOutOfRange();
        T* helpArray = new T[size + 1];
        int i = 0;
        for (; i < index; ++i) {
            helpArray[i] = array[i];
        }
        helpArray[i++] = item;
        for (; i < size + 1; ++i) {
            helpArray[i] = array[i - 1];
        }
        delete[] array;
        array = helpArray;
        size = size + 1;
    }

    friend std::ostream& operator << (std::ostream& os, const DynamicArray<T>& value) {
        int i = 0;
        for (; i < value.getSize() - 1; ++i) {
            os << value[i] << " ";
        }
        os << value[i] << "\n";
        return os;
    }
};