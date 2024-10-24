#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include "ShrdPtr.h"
#include "UnqPtr.h"
#include "WeakPtr.h"

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


void test_shared(int n) {
    std::vector<ShrdPtr<int>> vec;
    for (int i = 0; i < n; ++i) {
        vec.push_back(ShrdPtr<int>(new int(i)));
    }
   // std::cout << "Test for ShrdPtr with " << n << " objects completed." << std::endl;
}

void test_unique(int n) {
    std::vector<UnqPtr<int>> vec;
    for (int i = 0; i < n; ++i) {
        vec.push_back(UnqPtr<int>(new int(i)));
    }
    //std::cout << "Test for UnqPtr with " << n << " objects completed." << std::endl;
}

void test_weak(int n) {
    std::vector<WeakPtr<int>> vec;
    for (int i = 0; i < n; ++i) {
        ShrdPtr<int> sptr(new int(i));
        vec.push_back(WeakPtr<int>(sptr));
    }
   // std::cout << "Test for WeakPtr with " << n << " objects completed." << std::endl;
}

void show_results() {
    // Количество объектов для тестов
    std::vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000};

    // Заголовки таблицы
    std::cout << "Size, ShrPtr, std::shared_ptr, UnqPtr, std::unique_ptr, WeakPtr, std::weak_ptr" << std::endl;

    for (int n : sizes) {
        long long time_shrd = 0, time_shrd_std = 0;
        long long time_unq = 0, time_unq_std = 0;
        long long time_weak = 0, time_weak_std = 0;

        // Тесты для кастомных указателей
        MEASURE_TIME(test_shared(n), time_shrd);
        MEASURE_TIME(test_unique(n), time_unq);
        MEASURE_TIME(test_weak(n), time_weak);

        // Тесты для стандартных указателей
        MEASURE_TIME(test_std_shared(n), time_shrd_std);
        MEASURE_TIME(test_std_unique(n), time_unq_std);
        MEASURE_TIME(test_std_weak(n), time_weak_std);

        // Вывод результатов
        std::cout << n << ", " << time_shrd << ", " << time_shrd_std << ", "
                  << time_unq << ", " << time_unq_std << ", "
                  << time_weak << ", " << time_weak_std << std::endl;
    }
    std::cout << "All load tests passed!" << std::endl;

}
};




