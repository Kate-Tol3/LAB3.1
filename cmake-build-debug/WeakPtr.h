#pragma once

#include "ShrdPtr.h"

template <typename T>
class WeakPtr {
private:
    ControlBlock<T>* control_block;  // Указатель на контрольный блок

public:

    // Конструктор с выделением нового объекта
    // explicit WeakPtr(T* p = nullptr) : control_block(p ? new ControlBlock<T>(p) : nullptr) {
    //     if (control_block) {
    //         ++(control_block->weak_count);
    //     }
    // }
    WeakPtr() : control_block(){}

    // Конструктор из ShrdPtr
    WeakPtr(const ShrdPtr<T>& shrd_ptr) : control_block(shrd_ptr.control_block) {
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
        }
    }

    // Проверка, доступен ли объект
    const bool expired() const {
        return !control_block || control_block->weak_count == 0; // ref_count ??
    }

    bool expired() {
        return !control_block || control_block->weak_count == 0; // ref_count ??
    }

    // Преобразование в ShrdPtr
    ShrdPtr<T> lock() {
        if (!expired()) {
            return ShrdPtr<T>(*this);  // Создаём ShrdPtr, если объект ещё существует
        }
        return ShrdPtr<T>(nullptr);  // Возвращаем пустой ShrdPtr, если объект уже удалён
    }

    const ShrdPtr<T> lock() const {
        if (!expired()) {
            return ShrdPtr<T>(*this);  // Создаём ShrdPtr, если объект ещё существует
        }
        return ShrdPtr<T>(nullptr);  // Возвращаем пустой ShrdPtr, если объект уже удалён
    }

    void swap(WeakPtr& other) noexcept {
        T* temp_ptr = control_block->s_ptr;
        control_block->s_ptr = other.control_block->s_ptr;
        other.control_block->s_ptr = temp_ptr;
    }

    const int useCount() const { return control_block ? control_block->weak_count : 0; }
    int useCount()  { return control_block ? control_block->weak_count : 0; }

    // Проверка, является ли указатель нулевым
    const bool isNull() const { return !control_block  || control_block->s_ptr == nullptr; }
    bool isNull() { return !control_block  || control_block->s_ptr == nullptr; }


    // // Доступ к объекту
    const T& operator*() const { return *control_block->s_ptr;}
    const T* operator->() const { return control_block->s_ptr; }
    const T* get() const { return control_block ? control_block->s_ptr : nullptr; }

    T& operator*() { return *control_block->s_ptr;}
    T* operator->() { return control_block->s_ptr; }
    T* get() { return control_block ? control_block->s_ptr : nullptr; }

    // Проверка на единственность
    const bool unique() const {
        return control_block && control_block->weak_count == 1;
    }
    bool unique() {
        return control_block && control_block->weak_count == 1;
    }

    friend class ShrdPtr<T>;

};