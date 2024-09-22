// #include <iostream>
// #include <chrono>
// #include <memory>
// #include <vector>
// #include <cassert>
// #include <cstdlib>
// #include <ctime>
//
// // Простой класс для тестирования
// class TestClass {
// public:
//     TestClass() { ++instance_count; }
//     ~TestClass() { --instance_count; }
//     static int get_instance_count() { return instance_count; }
// private:
//     static int instance_count;
// };
//
// int TestClass::instance_count = 0;
//
// // Время выполнения функции
// template <typename Func>
// auto measure_time(Func&& func) {
//     auto start = std::chrono::high_resolution_clock::now();
//     func();
//     auto end = std::chrono::high_resolution_clock::now();
//     return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
// }
//
// // Нагрузочные тесты для различных указателей
// void load_test() {
//     const size_t num_elements = 100000;
//
//     // shared_ptr
//     std::cout << "Testing std::shared_ptr...\n";
//     auto shared_ptr_time = measure_time([num_elements]() {
//         std::vector<std::shared_ptr<TestClass>> vec;
//         for (size_t i = 0; i < num_elements; ++i) {
//             vec.push_back(std::make_shared<TestClass>());
//         }
//     });
//     std::cout << "std::shared_ptr time: " << shared_ptr_time << " microseconds\n";
//
//     // unique_ptr
//     std::cout << "Testing std::unique_ptr...\n";
//     auto unique_ptr_time = measure_time([num_elements]() {
//         std::vector<std::unique_ptr<TestClass>> vec;
//         for (size_t i = 0; i < num_elements; ++i) {
//             vec.push_back(std::make_unique<TestClass>());
//         }
//     });
//     std::cout << "std::unique_ptr time: " << unique_ptr_time << " microseconds\n";
//
//     // weak_ptr (сначала создаем shared_ptr объекты)
//     std::vector<std::shared_ptr<TestClass>> shared_vec(num_elements);
//     for (size_t i = 0; i < num_elements; ++i) {
//         shared_vec[i] = std::make_shared<TestClass>();
//     }
//
//     std::cout << "Testing std::weak_ptr...\n";
//     auto weak_ptr_time = measure_time([&shared_vec]() {
//         std::vector<std::weak_ptr<TestClass>> vec;
//         for (const auto& sp : shared_vec) {
//             vec.push_back(sp);
//         }
//     });
//     std::cout << "std::weak_ptr time: " << weak_ptr_time << " microseconds\n";
//
//     // raw pointers
//     std::cout << "Testing raw pointers...\n";
//     auto raw_ptr_time = measure_time([num_elements]() {
//         std::vector<TestClass*> vec;
//         for (size_t i = 0; i < num_elements; ++i) {
//             vec.push_back(new TestClass());
//         }
//         for (auto ptr : vec) {
//             delete ptr;
//         }
//     });
//     std::cout << "Raw pointers time: " << raw_ptr_time << " microseconds\n";
// }
//
// // int main() {
// //     std::cout << "Starting load tests...\n";
// //     load_test();
// //     std::cout << "Load tests completed.\n";
// //     return 0;
// // }