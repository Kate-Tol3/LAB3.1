#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <iomanip>
#include "SharedPtr.h"
#include "UnqPtr.h"
#include "WeakPtr.h"

class LoadTest {
public:
    // Функция для измерения времени выполнения
    template <typename Func>
    static long long measureTime(Func func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    template <typename PtrType>
    void testPointer(int n) {
        std::vector<PtrType> vec;
        for (int i = 0; i < n; ++i) {
            vec.push_back(PtrType(new int(i)));
        }
    }

    void show_results() {
        std::vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000};
        const int width = 15;
        const std::string separator = "+" + std::string(width * 7 + 8, '-') + "+";

        // Заголовок таблицы
        std::cout << separator << "\n";
        std::cout << "| " << std::setw(width - 1) << "Size"
                  << " | " << std::setw(width - 1) << "SharePtr"
                  << " | " << std::setw(width - 1) << "std::shared_ptr"
                  << " | " << std::setw(width - 1) << "UnqPtr"
                  << " | " << std::setw(width - 1) << "std::unique_ptr"
                  << " | " << std::setw(width - 1) << "WeakPtr"
                  << " | " << std::setw(width - 1) << "std::weak_ptr" << " |\n";
        std::cout << separator << "\n";


        for (int n : sizes) {
            long long time_Shared = measureTime([this, n]() { testPointer<SharedPtr<int>>(n); });
            long long time_Shared_std = measureTime([this, n]() { testPointer<std::shared_ptr<int>>(n); });
            long long time_unq = measureTime([this, n]() { testPointer<UnqPtr<int>>(n); });
            long long time_unq_std = measureTime([this, n]() { testPointer<std::unique_ptr<int>>(n); });
            long long time_weak = measureTime([this, n]() {
                std::vector<WeakPtr<int>> vec;
                for (int i = 0; i < n; ++i) {
                    SharedPtr<int> sptr(new int(i));
                    vec.push_back(WeakPtr<int>(sptr));
                }
            });
            long long time_weak_std = measureTime([this, n]() {
                std::vector<std::weak_ptr<int>> vec;
                for (int i = 0; i < n; ++i) {
                    std::shared_ptr<int> sptr = std::make_shared<int>(i);
                    vec.push_back(std::weak_ptr<int>(sptr));
                }
            });


            std::cout << "| " << std::setw(width - 1) << n
                      << " | " << std::setw(width - 1) << time_Shared
                      << " | " << std::setw(width - 1) << time_Shared_std
                      << " | " << std::setw(width - 1) << time_unq
                      << " | " << std::setw(width - 1) << time_unq_std
                      << " | " << std::setw(width - 1) << time_weak
                      << " | " << std::setw(width - 1) << time_weak_std << " |\n";
        }

        std::cout << separator << "\n";
        std::cout << "All load tests completed!\n";
    }
};
