#pragma once
#include "ShrdPtrAtomic.h"

template <typename T>
class WeakPtrAtomic {
private:
    ControlBlockAtomic<T>* control_block;  // Указатель на контрольный блок

public:

    // Конструктор с выделением нового объекта
    explicit WeakPtrAtomic(T* p = nullptr) : control_block(p ? new ControlBlockAtomic<T>(p) : nullptr) {
        if (control_block) {
            control_block->weak_count->fetch_add(1, std::memory_order_relaxed);
        }

    }

    // Конструктор из ShrdPtrAtomic
    WeakPtrAtomic(const ShrdPtrAtomic<T>& shrd_ptr) : control_block(shrd_ptr.control_block) {
        if (control_block) {
            control_block->weak_count->fetch_add(1, std::memory_order_relaxed);
        }
    }

    // Копирующий конструктор
    WeakPtrAtomic(const WeakPtrAtomic& other) : control_block(other.control_block) {
        control_block->weak_count->fetch_add(1, std::memory_order_relaxed);
    }

    // Перемещающий конструктор
    WeakPtrAtomic(WeakPtrAtomic&& other) noexcept : control_block(other.control_block) {
        other.control_block = nullptr;
    }

    // Деструктор
    ~WeakPtrAtomic() {
        release();
    }

    // Копирующее присваивание
    WeakPtrAtomic& operator=(const WeakPtrAtomic& other) {
        if (this != &other) {
            release();
            control_block = other.control_block;
            if (control_block) {
                control_block->weak_count->fetch_add(1, std::memory_order_acq_rel);
            }
        }
        return *this;

    }

    // Перемещающее присваивание
    WeakPtrAtomic& operator=(WeakPtrAtomic&& other) noexcept {
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
            if (control_block->weak_count->fetch_sub(1, std::memory_order_acq_rel) == 1) {
                control_block->deleteObject();// Удаляем сам объект
                if (control_block->ref_count->load() == 0 && control_block->weak_count->load() == 0) {
                    delete control_block;  // Удаляем контрольный блок, если нет сильных и слабых ссылок
                }
            }
        }
    }

    // Проверка, доступен ли объект
    bool expired() const {
        return !control_block || control_block->ref_count->load() == 0;
    }

    // Преобразование в ShrdPtrAtomic
    ShrdPtrAtomic<T> lock() const {
        if (!expired()) {
            return ShrdPtrAtomic<T>(*this);  // Создаём ShrdPtrAtomic, если объект ещё существует
        }
        return ShrdPtrAtomic<T>(nullptr);  // Возвращаем пустой ShrdPtrAtomic, если объект уже удалён
    }

    void swap(WeakPtrAtomic& other) noexcept {
        T* temp_ptr = control_block->s_ptr;
        control_block->s_ptr = other.control_block->s_ptr;
        other.control_block->s_ptr = temp_ptr;
    }

    size_t useCount() const { return control_block ? control_block->weak_count->load() : static_cast<size_t>(0); }

    // Проверка, является ли указатель нулевым
    bool isNull() const { return control_block == nullptr || control_block->s_ptr == nullptr; }


    // // Доступ к объекту
    T& operator*() const { return *control_block->s_ptr;}
    T* operator->() const { return control_block->s_ptr; }
    T* get() const { return control_block ? control_block->s_ptr : nullptr; }

    // Проверка на единственность
    bool unique() const {
        return control_block && control_block->weak_count->load() == 1;
    }

    friend class ShrdPtrAtomic<T>;

};