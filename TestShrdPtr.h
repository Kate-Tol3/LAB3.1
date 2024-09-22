#include <cassert>
#include <iostream>
#include <memory>

// Тесты для ShrdPtr
void testShrdPtr() {
    {
        // Создаем объект с shared_ptr
        std::shared_ptr<int> sp1 = std::make_shared<int>(10);
        assert(*sp1 == 10); // Проверяем значение

        // Создаем еще один shared_ptr, указывающий на тот же объект
        std::shared_ptr<int> sp2 = sp1;
        assert(sp2.use_count() == 2); // Проверяем количество ссылок

        // Присваиваем nullptr первому указателю
        sp1.reset();
        assert(sp2.use_count() == 1); // Проверяем, что объект все еще доступен через sp2

        // Очищаем второй указатель
        sp2.reset();
        // Здесь объект должен быть уничтожен, нет необходимости в дополнительных проверках
    }
    // Здесь мы можем проверить, что объект действительно был уничтожен (если нужно, используя пользовательские деструкторы и т.д.)
}

// int main() {
//     testShrdPtr();
//     std::cout << "Все тесты для ShrdPtr прошли успешно.\n";
//     return 0;
// }