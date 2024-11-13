#pragma once

#include "SharedPtr.h"
#include <stdexcept>

template <typename T>
class WeakPtr {
private:
    ControlBlock<T>* control_block;

public:


    WeakPtr() : control_block(){}

    // Конструктор из SharedPtr
    WeakPtr(const SharedPtr<T>& Shared_ptr) : control_block(Shared_ptr.control_block) {
        if (control_block) {
            ++(control_block->weak_count);
        }
    }

    // Копирующий конструктор
    WeakPtr(const WeakPtr& other) : control_block(other.control_block) {
        if (control_block) {
            ++(control_block->weak_count);
        }

    }

    // Перемещающий конструктор
    WeakPtr(WeakPtr&& other) noexcept : control_block(other.control_block) {
        other.control_block = nullptr;
    }

    // Деструктор
    ~WeakPtr() {
        release();
    }

    // Копирующее присваивание
    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            release();
            control_block = other.control_block;
            if (control_block) {
                ++(control_block->weak_count);
            }
        }
        return *this;

    }

    // Перемещающее присваивание
    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            release();
            control_block = other.control_block;
            other.control_block = nullptr;
        }
        return *this;
    }

    // Освобождение ресурса
    void release() {
        if (control_block) {
            if (--control_block->weak_count == 0 && control_block->ref_count == 0) {
                delete control_block;  // Удаляем контрольный блок, если нет сильных и слабых ссылок
            }
            control_block = nullptr;
        }
    }

    // Проверка, доступен ли объект
    const bool expired() const {
        return !control_block || control_block->weak_count == 0;
    }

    // Преобразование в SharedPtr
    SharedPtr<T> lock() {
        if (!expired()) {
            return SharedPtr<T>(*this);
        }
        return SharedPtr<T>(nullptr);
    }

    const SharedPtr<T> lock() const {
        if (!expired()) {
            return SharedPtr<T>(*this);
        }
        return SharedPtr<T>(nullptr);
    }

    void swap(WeakPtr& other) noexcept {
        T* temp_ptr = control_block->s_ptr;
        control_block->s_ptr = other.control_block->s_ptr;
        other.control_block->s_ptr = temp_ptr;
    }

    const int useCount() const { return control_block ? control_block->weak_count : 0; }
    int useCount()  { return control_block ? control_block->weak_count : 0; }

    const bool isNull() const { return !control_block  || control_block->s_ptr == nullptr; }
    bool isNull() { return !control_block  || control_block->s_ptr == nullptr; }

    const T& operator*() const {
        if (expired()) throw std::out_of_range("The pointer have expired.\n");
        return *control_block->s_ptr;
    }
    const T* operator->() const {
        if (expired()) throw std::out_of_range("The pointer have expired.\n");
        return control_block->s_ptr;
    }
    const T* get() const {return control_block ? control_block->s_ptr : nullptr;}

    T& operator*() {
        if (expired()) throw std::out_of_range("The pointer have expired.\n");
        return *control_block->s_ptr;
    }
    T* operator->() {
        if (expired()) throw std::out_of_range("The pointer have expired.\n");
        return control_block->s_ptr;
    }
    T* get() { return control_block ? control_block->s_ptr : nullptr;}

    const bool unique() const {
        return control_block && control_block->weak_count == 1;
    }
    bool unique() {
        return control_block && control_block->weak_count == 1;
    }

    friend class SharedPtr<T>;

};