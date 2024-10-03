gi#pragma once

template <typename T>
class UnqPtr {
private:
    T* u_ptr;

public:


    explicit UnqPtr(T* p = nullptr) : u_ptr(p) {}

    ~UnqPtr() {
        delete u_ptr;
    }

    // Disable copy constructor and copy assignment
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

    // Override raw pointer operators
    T& operator*() const { return *u_ptr; }
    T* operator->() const { return u_ptr; }

    bool isNull() const { return u_ptr == nullptr; }

    // Get the raw pointer
    T* get() const { return u_ptr; }

    // Release the ownership of the managed object
    T* release() {
        T* temp = u_ptr;
        u_ptr = nullptr;
        return temp;
    }

    // Reset the pointer to a new resource
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


