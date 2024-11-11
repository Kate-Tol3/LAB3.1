#pragma once

template <typename T>
class UnqPtr {
private:
    T* u_ptr;

public:

    explicit UnqPtr(T* p = nullptr) : u_ptr(p) {}

    ~UnqPtr() {
        delete u_ptr;
    }

    UnqPtr(const UnqPtr&) = delete;
    UnqPtr& operator=(const UnqPtr&) = delete;

    // Move constructor
    UnqPtr(UnqPtr&& other) noexcept : u_ptr(other.u_ptr) {
        other.u_ptr = nullptr;
    }

    // Move assignment operator
    UnqPtr& operator=(UnqPtr&& other) noexcept {
        if (this != &other) {
            delete u_ptr;
            u_ptr = other.u_ptr;
            other.u_ptr = nullptr;
        }
        return *this;
    }


    T& operator*() {
        if (this->get() == nullptr) throw std::out_of_range("The pointer have expired.\n");
        return *u_ptr;
    }
    T* operator->() {
        if (this->get() == nullptr) throw std::out_of_range("The pointer have expired.\n");
        return u_ptr;
    }

    const T& operator*() const {
        if (this->get() == nullptr) throw std::out_of_range("The pointer have expired.\n");
        return *u_ptr;
    }
    const T* operator->() const {
        if (this->get() == nullptr) throw std::out_of_range("The pointer have expired.\n");
        return u_ptr;
    }

    const bool isNull() const { return u_ptr == nullptr; }
    bool isNull() {return u_ptr == nullptr; }

    // Get the raw pointer
    const T* get() const {
        return u_ptr;
    }
    T* get() {
        return u_ptr;
    }


    T* release() {
        T* temp = u_ptr;
        u_ptr = nullptr;
        return temp;
    }

    void reset(T* other = nullptr) {
        delete u_ptr;
        u_ptr = other;
    }

    void swap(UnqPtr& other) noexcept{
        T* temp = u_ptr;
        u_ptr = other.u_ptr;
        other.u_ptr = temp;
    }
};


