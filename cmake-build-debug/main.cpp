#include <iostream>
#include "WeakPtr.h"
#include "ShrdPtr.h"
#include "Test.h"
#include "LoadTest.h"

int main() {
    Test test;
    test.testAll();
    LoadTest l_test;
    l_test.show_results();
    return 0;
}
