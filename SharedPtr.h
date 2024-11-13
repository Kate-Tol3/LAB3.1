#pragma once

#include <stdexcept>

template <typename T>
struct ControlBlock {
    T* s_ptr;           // Указатель на управляемый объект
    int ref_count;      // Счётчик сильных ссылок (SharedPtr)
    int weak_count;     // Счётчик слабых ссылок (WeakPtr)


    ControlBlock(T* ptr = nullptr) : s_ptr(ptr), ref_count(1), weak_count(0) {}

    // Уничтожение объекта, но не самого контрольного блока
    void deleteObject() {
        delete s_ptr;
        s_ptr = nullptr;
    }
};

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr {
private:
    ControlBlock<T>* control_block;

public:

    explicit SharedPtr(T* p = nullptr) : control_block(p ? new ControlBlock<T>(p) : nullptr) {}

    // Копирующий конструктор
    SharedPtr(const SharedPtr& other) : control_block(other.control_block) {
        if (control_block) {
            ++(control_block->ref_count);
        }
    }

    // Перемещающий конструктор
    SharedPtr(SharedPtr&& other) noexcept : control_block(other.control_block) {
        other.control_block = nullptr;
    }

    SharedPtr(const WeakPtr<T>& weak) : control_block(weak.control_block) {
        if (control_block) {
            ++control_block->ref_count;
        }
    }

    ~SharedPtr() {
        release();
    }

    // Копирующее присваивание
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            control_block = other.control_block;
            if (control_block) {
                ++(control_block->ref_count);

            }
        }
        return *this;
    }

    // Перемещающее присваивание
    SharedPtr& operator=(SharedPtr&& other) noexcept {
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
            if (--control_block->ref_count == 0) {
                control_block->deleteObject();  // Удаляем сам объект
                if (control_block->weak_count == 0) {
                    delete control_block;  // Удаляем и контрольный блок, если слабых ссылок больше нет
                }
            }
            control_block = nullptr;
        }
    }

    // Доступ к объекту
    const T& operator*() const {
        if (expired()) throw std::out_of_range("The pointer have expired.\n");
        return *control_block->s_ptr;
    }
    const T* operator->() const {
        if (expired()) throw std::out_of_range("The pointer have expired.\n");
        return control_block->s_ptr;
    }

    T& operator*() {
        if (expired()) throw std::out_of_range("The pointer have expired.\n");
        return *control_block->s_ptr;
    }
    T* operator->() {
        if (expired()) throw std::out_of_range("The pointer have expired.\n");
        return control_block->s_ptr;
    }


    const T* get() const { return control_block ? control_block->s_ptr : nullptr; }
    T* get() { return control_block ? control_block->s_ptr : nullptr; }

    const int useCount() const { return control_block ? control_block->ref_count : 0; }
    int useCount() { return control_block ? control_block->ref_count : 0; }

    const bool isNull() const { return control_block == nullptr || control_block->s_ptr == nullptr; }
    bool isNull() { return control_block == nullptr || control_block->s_ptr == nullptr; }

    void swap(SharedPtr& other) noexcept {
        T* temp_ptr = control_block->s_ptr;
        control_block->s_ptr = other.control_block->s_ptr;
        other.control_block->s_ptr = temp_ptr;

    }

    const bool expired() const {
        return !control_block || control_block->ref_count == 0;
    }

    const bool unique() const {
        return control_block && control_block->ref_count == 1;
    }

    friend class WeakPtr<T>;

};

