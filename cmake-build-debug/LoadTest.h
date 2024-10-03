#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include "ShrdPtrAtomic.h"
#include "UnqPtr.h"
#include "WeakPtrAtomic.h"

class LoadTest {
public:
    // Макрос для измерения времени выполнения
#define MEASURE_TIME(operation, result) {                               \
    auto start = std::chrono::high_resolution_clock::now();             \
    operation;                                                          \
    auto end = std::chrono::high_resolution_clock::now();               \
    result = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();  \
}

// Тесты для стандартных указателей
void test_std_shared(int n) {
    std::vector<std::shared_ptr<int>> vec;
    for (int i = 0; i < n; ++i) {
        vec.push_back(std::make_shared<int>(i));
    }
}

void test_std_unique(int n) {
    std::vector<std::unique_ptr<int>> vec;
    for (int i = 0; i < n; ++i) {
        vec.push_back(std::unique_ptr<int>(new int(i)));
    }
}

void test_std_weak(int n) {
    std::vector<std::weak_ptr<int>> vec;
    for (int i = 0; i < n; ++i) {
        std::shared_ptr<int> sptr = std::make_shared<int>(i);
        vec.push_back(std::weak_ptr<int>(sptr));
    }
}


void test_shared_atomic(int n) {
    std::vector<ShrdPtrAtomic<int>> vec;
    for (int i = 0; i < n; ++i) {
        vec.push_back(ShrdPtrAtomic<int>(new int(i)));
    }
   // std::cout << "Test for ShrdPtrAtomic with " << n << " objects completed." << std::endl;
}

void test_unique_atomic(int n) {
    std::vector<UnqPtr<int>> vec;
    for (int i = 0; i < n; ++i) {
        vec.push_back(UnqPtr<int>(new int(i)));
    }
    //std::cout << "Test for UnqPtr with " << n << " objects completed." << std::endl;
}

void test_weak_atomic(int n) {
    std::vector<WeakPtrAtomic<int>> vec;
    for (int i = 0; i < n; ++i) {
        ShrdPtrAtomic<int> sptr(new int(i));
        vec.push_back(WeakPtrAtomic<int>(sptr));
    }
   // std::cout << "Test for WeakPtrAtomic with " << n << " objects completed." << std::endl;
}

void show_results() {
    // Количество объектов для тестов
    std::vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000};

    // Заголовки таблицы
    std::cout << "Size, ShrPtrAtomic, std::shared_ptr, UnqPtr, std::unique_ptr, WeakPtrAtomic, std::weak_ptr" << std::endl;

    for (int n : sizes) {
        long long time_shrd_atomic = 0, time_shrd_std = 0;
        long long time_unq_atomic = 0, time_unq_std = 0;
        long long time_weak_atomic = 0, time_weak_std = 0;

        // Тесты для кастомных указателей
        MEASURE_TIME(test_shared_atomic(n), time_shrd_atomic);
        MEASURE_TIME(test_unique_atomic(n), time_unq_atomic);
        MEASURE_TIME(test_weak_atomic(n), time_weak_atomic);

        // Тесты для стандартных указателей
        MEASURE_TIME(test_std_shared(n), time_shrd_std);
        MEASURE_TIME(test_std_unique(n), time_unq_std);
        MEASURE_TIME(test_std_weak(n), time_weak_std);

        // Вывод результатов
        std::cout << n << ", " << time_shrd_atomic << ", " << time_shrd_std << ", "
                  << time_unq_atomic << ", " << time_unq_std << ", "
                  << time_weak_atomic << ", " << time_weak_std << std::endl;



        // std::cout << std::format("{}: {} -- {} -- {} -- {} -- {} -- {} -- {}\n", n,
        //     time_shrd_atomic, time_shrd_std,time_unq_atomic, time_unq_std,  time_weak_atomic, time_weak_std, time_unq_std);
        //     std::cout << std::format("Hello {}!\n", "world");
    }
    std::cout << "All load tests passed!" << std::endl;

}
};




