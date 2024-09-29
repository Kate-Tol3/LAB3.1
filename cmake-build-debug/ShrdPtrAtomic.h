#pragma once
#include <atomic>

template <typename T>
struct ControlBlockAtomic {
    T* s_ptr;           // Указатель на управляемый объект
    std::atomic<unsigned long>* ref_count;      // Счётчик сильных ссылок (ShrdPtrAtomic)
    std::atomic<unsigned long>* weak_count;     // Счётчик слабых ссылок (WeakPtr)

    // Конструктор для инициализации контрольного блока
    explicit ControlBlockAtomic(T* ptr = nullptr) : s_ptr(ptr), ref_count(new std::atomic<unsigned long>(1)), weak_count(new std::atomic<unsigned long>(0)) {}

    // Уничтожение объекта, но не самого контрольного блока
    void deleteObject() {
        delete s_ptr;
        // delete ref_count;
        // delete weak_count;
        s_ptr = nullptr;
    }
};

template <typename T>
class WeakPtrAtomic;  // Объявляем заранее

template <typename T>
class ShrdPtrAtomic {
private:
    ControlBlockAtomic<T>* control_block;  // Указатель на контрольный блок

public:

    // Конструктор с выделением нового объекта
    explicit ShrdPtrAtomic(T* p = nullptr) : control_block(p ? new ControlBlockAtomic<T>(p) : nullptr) {}

    // Копирующий конструктор
    ShrdPtrAtomic(const ShrdPtrAtomic& other) : control_block(other.control_block) {
       (control_block->ref_count->fetch_add(1, std::memory_order_acq_rel));
    }

    // Перемещающий конструктор
    ShrdPtrAtomic(ShrdPtrAtomic&& other) noexcept : control_block(other.control_block) {
        other.control_block = nullptr;
    }

    ShrdPtrAtomic(const WeakPtrAtomic<T>& weak) : control_block(weak.control_block) {
        if (control_block) {
            (control_block->ref_count->fetch_add(1, std::memory_order_acq_rel));
        }
    }

    // Деструктор
    ~ShrdPtrAtomic() {
        release();
    }


    // Копирующее присваивание
    ShrdPtrAtomic& operator=(const ShrdPtrAtomic& other) {
        if (this != &other) {
            release();
            control_block = other.control_block;
            if (control_block) {
                control_block->ref_count->fetch_add(1, std::memory_order_acq_rel);
            }
        }
        return *this;
    }

    // Перемещающее присваивание
    ShrdPtrAtomic& operator=(ShrdPtrAtomic&& other) noexcept {
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
            if (control_block->ref_count->fetch_sub(1, std::memory_order_acq_rel) == 1) {
                control_block->deleteObject();  // Удаляем сам объект
                if (control_block->weak_count->load() == 0) {
                    delete control_block;  // Удаляем и контрольный блок, если слабых ссылок больше нет
                }
            }
        }
    }


    // Доступ к объекту
    T& operator*() const { return *control_block->s_ptr;}
    T* operator->() const { return control_block->s_ptr; }
    T* get() const { return control_block ? control_block->s_ptr : nullptr; }

    // Проверка количества сильных ссылок
    unsigned long useCount() const { return control_block ? control_block->ref_count->load() : static_cast<unsigned long>(0); }

    // Проверка, является ли указатель нулевым
    bool isNull() const { return control_block == nullptr || control_block->s_ptr == nullptr; }

    void swap(ShrdPtrAtomic& other) noexcept {
        // T* temp_ptr = control_block->s_ptr;
        // int temp_count = control_block->ref_count; ///
        // control_block->s_ptr = other.control_block->s_ptr;
        // control_block->ref_count = other.control_block->ref_count;
        // other.control_block->s_ptr = temp_ptr;
        // other.control_block->ref_count = temp_count;

        T* temp_ptr = control_block->s_ptr;
//        int temp_w_count = control_block->weak_count;
//        int temp_r_count = control_block->ref_count;
        control_block->s_ptr = other.control_block->s_ptr;
        // control_block->weak_count = other.control_block->weak_count;
        // control_block->ref_count = other.control_block->ref_count;
        other.control_block->s_ptr = temp_ptr;
        // other.control_block->weak_count = temp_w_count;
        // other.control_block->ref_count = temp_r_count;
    }

    // Проверка на единственность
    bool unique() const {
        return control_block && control_block->ref_count->load() == 1;
    }

    //Доступ к weak_ptr (дружба с WeakPtr не нужна)
  friend class WeakPtrAtomic<T>;
};



