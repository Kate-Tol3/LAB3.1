#pragma once
#include <cassert>
#include <iostream>
#include <memory>


// void testUnqPtr() {
//     {
//         // Создаем объект с unique_ptr
//         std::unique_ptr<int> up1 = std::make_unique<int>(20);
//         assert(*up1 == 20); // Проверяем значение
//
//         // Передаем ownership другому unique_ptr
//         std::unique_ptr<int> up2 = std::move(up1);
//         assert(up1 == nullptr); // Первоначальный указатель теперь равен nullptr
//         assert(*up2 == 20); // Новый указатель содержит тот же объект
//
//         // Очищаем указатель
//         up2.reset();
//         // Здесь объект должен быть уничтожен, нет необходимости в дополнительных проверках
//     }
//     // Здесь мы можем проверить, что объект действительно был уничтожен (если нужно, используя пользовательские деструкторы и т.д.)
// }

class UnqPtrTest {
    void testConstructors();
    void testOperators();
    void testMoveOperator();
    void testGet();
    void testIsNull();
    void testRelease();
    void testReset();
    void testSwap();

    void test();
};
