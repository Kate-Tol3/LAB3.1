
#ifndef GUNPLOTGRAPHS_H
#define GUNPLOTGRAPHS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <gnuplot-iostream/gnuplot-iostream.h>



class GunplotGraphs {
public:


// Структура для хранения результатов тестов
struct TestResult {
    int size;
    long long shrd_atomic, std_shared, unq_atomic, std_unique, weak_atomic, std_weak;
};

// Функция для вывода таблицы
void printResults(const std::vector<TestResult>& results) {
    std::cout << "Size\tShrdPtrAtomic\tstd::shared_ptr\tUnqPtr\tstd::unique_ptr\tWeakPtrAtomic\tstd::weak_ptr\n";
    for (const auto& result : results) {
        std::cout << result.size << "\t"
                  << result.shrd_atomic << "\t"
                  << result.std_shared << "\t"
                  << result.unq_atomic << "\t"
                  << result.std_unique << "\t"
                  << result.weak_atomic << "\t"
                  << result.std_weak << "\n";
    }
}

// Функция для построения графика с использованием gnuplot
void plotResults(const std::vector<TestResult>& results) {
    Gnuplot gp;

    // Подготовка данных для графика
    std::vector<int> sizes;
    std::vector<long long> shrd_atomic, std_shared, unq_atomic, std_unique, weak_atomic, std_weak;

    for (const auto& result : results) {
        sizes.push_back(result.size);
        shrd_atomic.push_back(result.shrd_atomic);
        std_shared.push_back(result.std_shared);
        unq_atomic.push_back(result.unq_atomic);
        std_unique.push_back(result.std_unique);
        weak_atomic.push_back(result.weak_atomic);
        std_weak.push_back(result.std_weak);
    }

    // Построение графика
    gp << "set title 'Performance Comparison'\n";
    gp << "set xlabel 'Size'\n";
    gp << "set ylabel 'Time (microseconds)'\n";
    gp << "plot '-' with lines title 'ShrdPtrAtomic', "
          "'-' with lines title 'std::shared_ptr', "
          "'-' with lines title 'UnqPtr', "
          "'-' with lines title 'std::unique_ptr', "
          "'-' with lines title 'WeakPtrAtomic', "
          "'-' with lines title 'std::weak_ptr'\n";

    gp.send1d(std::make_pair(sizes, shrd_atomic));
    gp.send1d(std::make_pair(sizes, std_shared));
    gp.send1d(std::make_pair(sizes, unq_atomic));
    gp.send1d(std::make_pair(sizes, std_unique));
    gp.send1d(std::make_pair(sizes, weak_atomic));
    gp.send1d(std::make_pair(sizes, std_weak));
}

    int printPlot() {
        // Пример данных
        std::vector<TestResult> results = {
            {10, 150, 120, 90, 80, 170, 140},
            {100, 250, 200, 190, 150, 280, 230},
            {1000, 900, 850, 700, 650, 950, 850},
            {10000, 1800, 1700, 1500, 1400, 2000, 1800},
            {100000, 3000, 2900, 2700, 2500, 3500, 3200}
        };

        // Вывод таблицы
        printResults(results);

        // Построение графика
        plotResults(results);
    }



};



#endif //GUNPLOTGRAPHS_H
