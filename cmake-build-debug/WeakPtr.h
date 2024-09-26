#pragma once

#include "ShrdPtr.h"
// template <typename T>
// struct ControlBlock {
//     T* s_ptr;           // Указатель на управляемый объект
//     int ref_count;      // Счётчик сильных ссылок (ShrdPtr)
//     int weak_count;     // Счётчик слабых ссылок (WeakPtr)
//
//     // Конструктор для инициализации контрольного блока
//     ControlBlock(T* ptr = nullptr) : s_ptr(ptr), ref_count(1), weak_count(0) {}
//
//     // Уничтожение объекта, но не самого контрольного блока
//     void deleteObject() {
//         delete s_ptr;
//         s_ptr = nullptr;
//     }
// };
//
// template <typename T>
// class WeakPtr;  // Объявляем заранее
//
// template <typename T>
// class ShrdPtr {
// private:
//     ControlBlock<T>* control_block;  // Указатель на контрольный блок
//
// // protected:
// //     ControlBlock<T>* getControlBlock() {
// //         return control_block;
// //     }
//
// public:
//
//     // Конструктор с выделением нового объекта
//     explicit ShrdPtr(T* p = nullptr) : control_block(p ? new ControlBlock<T>(p) : nullptr) {}
//
//     // Копирующий конструктор
//     ShrdPtr(const ShrdPtr& other) : control_block(other.control_block) {
//        ++(control_block->ref_count);
//     }
//
//     // Перемещающий конструктор
//     ShrdPtr(ShrdPtr&& other) noexcept : control_block(other.control_block) {
//         other.control_block = nullptr;
//     }
//
//     ShrdPtr(const WeakPtr<T>& weak) : control_block(weak.control_block) {
//         if (control_block) {
//             ++control_block->ref_count;
//         }
//     }
//
//     // Деструктор
//     ~ShrdPtr() {
//         release();
//     }
//
//     // Копирующее присваивание
//     ShrdPtr& operator=(const ShrdPtr& other) {
//         if (this != &other) {
//             release();
//             control_block = other.control_block;
//             if (control_block) {
//                 ++(control_block->ref_count);
//             }
//         }
//         return *this;
//     }
//
//     // Перемещающее присваивание
//     ShrdPtr& operator=(ShrdPtr&& other) noexcept {
//         if (this != &other) {
//             release();
//             control_block = other.control_block;
//             other.control_block = nullptr;
//         }
//         return *this;
//     }
//
//     // Освобождение ресурса
//     void release() {
//         if (control_block) {
//             if (--control_block->ref_count == 0) {
//                 control_block->deleteObject();  // Удаляем сам объект
//                 if (control_block->weak_count == 0) {
//                     delete control_block;  // Удаляем и контрольный блок, если слабых ссылок больше нет
//                 }
//             }
//         }
//     }
//
//     // Доступ к объекту
//     T& operator*() const { return *control_block->s_ptr;}
//     T* operator->() const { return control_block->s_ptr; }
//     T* get() const { return control_block ? control_block->s_ptr : nullptr; }
//
//     // Проверка количества сильных ссылок
//     int useCount() const { return control_block ? control_block->ref_count : 0; }
//
//     // Проверка, является ли указатель нулевым
//     bool isNull() const { return control_block == nullptr || control_block->s_ptr == nullptr; }
//
//     void swap(ShrdPtr& other) noexcept {
//         T* temp_ptr = control_block->s_ptr;
//         int* temp_count = control_block->ref_count;
//         control_block->s_ptr = other.control_block->s_ptr;
//         control_block->ref_count = other.control_block->ref_count;
//         other.control_block->s_ptr = temp_ptr;
//         other.control_block->ref_count = temp_count;
//     }
//
//     // Проверка на единственность
//     bool unique() const {
//         return control_block && control_block->ref_count == 1;
//     }
//
//     //Доступ к weak_ptr (дружба с WeakPtr не нужна)
//   friend class WeakPtr<T>;
// };

template <typename T>
class WeakPtr {
private:
    ControlBlock<T>* control_block;  // Указатель на контрольный блок

public:

    // Конструктор с выделением нового объекта
    explicit WeakPtr(T* p = nullptr) : control_block(p ? new ControlBlock<T>(p) : nullptr) {
        if (control_block) {
            ++(control_block->weak_count);
        }
    }

    // Конструктор из ShrdPtr
    WeakPtr(const ShrdPtr<T>& shrd_ptr) : control_block(shrd_ptr.control_block) {
        if (control_block) {
            ++(control_block->weak_count);
        }
    }

    // Копирующий конструктор
    WeakPtr(const WeakPtr& other) : control_block(other.control_block) {
        ++(control_block->weak_count);
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
    bool expired() const {
        return !control_block || control_block->ref_count == 0;
    }

    // Преобразование в ShrdPtr
    ShrdPtr<T> lock() const {
        if (!expired()) {
            return ShrdPtr<T>(*this);  // Создаём ShrdPtr, если объект ещё существует
        }
        return ShrdPtr<T>(nullptr);  // Возвращаем пустой ShrdPtr, если объект уже удалён
    }

    void swap(WeakPtr& other) noexcept {
        T* temp_ptr = control_block->s_ptr;
        // int temp_w_count = control_block->weak_count;
        // int temp_r_count = control_block->ref_count;
        control_block->s_ptr = other.control_block->s_ptr;
        // control_block->weak_count = other.control_block->weak_count;
        // control_block->ref_count = other.control_block->ref_count;
        other.control_block->s_ptr = temp_ptr;
        // other.control_block->weak_count = temp_w_count;
        // other.control_block->ref_count = temp_r_count;
    }

    int useCount() const { return control_block ? control_block->weak_count : 0; }

    // Проверка, является ли указатель нулевым
    bool isNull() const { return control_block == nullptr || control_block->s_ptr == nullptr; }


    // // Доступ к объекту
    T& operator*() const { return *control_block->s_ptr;}
    T* operator->() const { return control_block->s_ptr; }
    T* get() const { return control_block ? control_block->s_ptr : nullptr; }

    // Проверка на единственность
    bool unique() const {
        return control_block && control_block->weak_count == 1;
    }

    friend class ShrdPtr<T>;

};