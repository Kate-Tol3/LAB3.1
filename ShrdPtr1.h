// #pragma once
// #include <queue>
//
// template <typename T>
// class ShrdPtr1 {
// private:
//     T* s_ptr;              // Raw pointer to the resource
//     int* ref_count;      // Reference count to track how many shared_ptrs point to the resource
//
// public:
//
//     explicit ShrdPtr1(T* p = nullptr) : s_ptr(p), ref_count(new int(1)) {}
//
//     // Copy constructor
//     ShrdPtr1(const ShrdPtr1& other) : s_ptr(other.s_ptr), ref_count(other.ref_count) {
//         (*ref_count)++;
//     }
//
//     // Move constructor
//     ShrdPtr1(ShrdPtr1&& other) noexcept : s_ptr(other.s_ptr), ref_count(other.ref_count) {
//         other.s_ptr = nullptr;
//         other.ref_count = nullptr;
//     }
//
//     // Destructor
//     ~ShrdPtr1() {
//         if (ref_count && --(*ref_count) == 0) { // we decrease ref_count and if after that it equals zero we delete shared_ptr
//             delete s_ptr;
//             delete ref_count;
//         }
//     }
//
//     // Copy assignment operator
//     ShrdPtr1& operator=(const ShrdPtr1& other) {
//         if (this != &other) {
//             // Decrease old resource's reference count
//             if (ref_count && --(*ref_count) == 0) {
//                  delete s_ptr;
//                  delete ref_count;
//             }
//
//             // Assign new resource and increase its reference count
//             s_ptr = other.s_ptr;
//             ref_count = other.ref_count;
//             (*ref_count)++;
//         }
//         return *this;
//     }
//
//     // Move assignment operator
//     ShrdPtr1& operator=(ShrdPtr1&& other) noexcept {
//         if (this != &other) {
//             // Decrease old resource's reference count
//             if (ref_count && --(*ref_count) == 0) {
//                 delete s_ptr;
//                 delete ref_count;
//             }
//
//             // Transfer ownership
//             s_ptr = other.s_ptr;
//             ref_count = other.ref_count;
//             other.s_ptr = nullptr;
//             other.ref_count = nullptr;
//         }
//         return *this;
//     }
//
//     void swap(ShrdPtr1& other) noexcept{
//         T* temp = s_ptr;
//         int* counter = ref_count;
//         s_ptr = other.s_ptr;
//         ref_count = other.ref_count;
//         other.s_ptr = temp;
//         other.ref_count = counter;
//     }
//
//     // Dereference operators
//     T& operator*() const { return *s_ptr; }
//     T* operator->() const { return s_ptr; }
//
//     // Get the raw pointer
//     T* get() const { return s_ptr; }
//
//     // Return the current reference count
//     int useCount() const { return *ref_count; }
//
//     bool isNull() const { return s_ptr == nullptr; }
// };
