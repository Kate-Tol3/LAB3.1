#pragma once

template <typename T>
struct ControlBlock {
    T* s_ptr;           // Указатель на управляемый объект
    int ref_count;      // Счётчик сильных ссылок (ShrdPtr)
    int weak_count;     // Счётчик слабых ссылок (WeakPtr)

    // Конструктор для инициализации контрольного блока
    ControlBlock(T* ptr = nullptr) : s_ptr(ptr), ref_count(1), weak_count(0) {}

    // Уничтожение объекта, но не самого контрольного блока
    void deleteObject() {
        delete s_ptr;
        s_ptr = nullptr;
    }
};

template <typename T>
class WeakPtr;  // Объявляем заранее

template <typename T>
class ShrdPtr {
private:
    ControlBlock<T>* control_block;  // Указатель на контрольный блок

public:

    // Конструктор с выделением нового объекта
    explicit ShrdPtr(T* p = nullptr) : control_block(p ? new ControlBlock<T>(p) : nullptr) {}

    // Копирующий конструктор
    ShrdPtr(const ShrdPtr& other) : control_block(other.control_block) {
        if (control_block) {
            ++(control_block->ref_count);
        }
    }

    // Перемещающий конструктор
    ShrdPtr(ShrdPtr&& other) noexcept : control_block(other.control_block) {
        other.control_block = nullptr;
    }

    ShrdPtr(const WeakPtr<T>& weak) : control_block(weak.control_block) {
        if (control_block) {
            ++control_block->ref_count;
        }
    }

    // Деструктор
    ~ShrdPtr() {
        release();
    }

    // Копирующее присваивание
    ShrdPtr& operator=(const ShrdPtr& other) {
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
    ShrdPtr& operator=(ShrdPtr&& other) noexcept {
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
        }
    }

    // Доступ к объекту
    const T& operator*() const { return *control_block->s_ptr;}
    const T* operator->() const { return control_block->s_ptr; }

    T& operator*() { return *control_block->s_ptr;}
    T* operator->() { return control_block->s_ptr; }

    //bool operator!() { return control_block->s_ptr == nullptr;}//???


    const T* get() const { return control_block ? control_block->s_ptr : nullptr; }
    T* get() { return control_block ? control_block->s_ptr : nullptr; }

    // Проверка количества сильных ссылок
    const int useCount() const { return control_block ? control_block->ref_count : 0; }
    int useCount() { return control_block ? control_block->ref_count : 0; }

    // Проверка, является ли указатель нулевым
    const bool isNull() const { return control_block == nullptr || control_block->s_ptr == nullptr; }
    bool isNull() { return control_block == nullptr || control_block->s_ptr == nullptr; }

    void swap(ShrdPtr& other) noexcept {
        T* temp_ptr = control_block->s_ptr;
        control_block->s_ptr = other.control_block->s_ptr;
        other.control_block->s_ptr = temp_ptr;

    }

    // Проверка на единственность
    const bool unique() const {
        return control_block && control_block->ref_count == 1;
    }

    //Доступ к weak_ptr (дружба с WeakPtr не нужна)
    friend class WeakPtr<T>;

};

