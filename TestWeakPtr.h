
#include <cassert>
#include <iostream>
#include <memory>

// Тесты для WeakPtr
void testWeakPtr() {
    {
        // Создаем объект с shared_ptr
        std::shared_ptr<int> sp1 = std::make_shared<int>(30);
        std::weak_ptr<int> wp1 = sp1;

        // Проверяем, что weak_ptr может получить shared_ptr
        std::shared_ptr<int> sp2 = wp1.lock();
        assert(sp2 != nullptr); // Проверяем, что объект все еще существует
        assert(*sp2 == 30); // Проверяем значение

        // Уничтожаем оригинальный shared_ptr
        sp1.reset();
        std::shared_ptr<int> sp3 = wp1.lock();
        assert(sp3 == nullptr); // После уничтожения объекта weak_ptr не должен указывать на валидный объект
    }
    // Здесь объект должен быть уничтожен, нет необходимости в дополнительных проверках
}

// int main() {
//     testWeakPtr();
//     std::cout << "Все тесты для WeakPtr прошли успешно.\n";
//     return 0;
// }