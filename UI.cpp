#include "Test.h"
#include "UI.h"
#include "LoadTest.h"
#include <iostream>
#include <cstring>

class UI {
private:
    Test test;
    LoadTest load;

public:
    void menu() {
        std::cout << "Enter the name of test. All commands names are accessible:\n";
        std::cout << "-runAllPointerTests\n-runLoadTests\n-testAllSequences\n-testUniquePtr\n-testSharedPtr\n";
        std::cout << "-testWeakPtr\n-testSharedAtomicPtr\n-testWeakAtomicPtr\n-testLinkedList\n-testDynamicArray\n";
        std::cout << "-testMutableSequence\n-finish\n\n";

        std::string command;
        
        do {
            std::cout << "\nEnter the command:\n-> ";
            std::cin >> command;
            if (command == "runAllPointerTests") {
                test.testUnqPtr();
                test.testWeakPtr();
                test.testSharedPtr();
            } else if (command == "runLoadTests") {
                load.show_results();
            } else if (command == "testAllSequences") {
                test.testLinkedList();
                test.testDynamicArray();
                test.testMutableSequence();
            } else if (command == "testUniquePtr") {
                test.testUnqPtr();
            } else if (command == "testSharedPtr") {
                test.testSharedPtr();
            } else if (command == "testWeakPtr") {
                test.testWeakPtr();
                std::cout << "The test are successful\n";
            } else if (command == "testSharedAtomicPtr") {
                test.testSharedPtrAtomic();
            } else if (command == "testWeakAtomicPtr") {
                test.testWeakPtrAtomic();
            } else if (command == "testLinkedList") {
                test.testLinkedList();
            } else if (command == "testDynamicArray") {
                test.testDynamicArray();
            } else if (command == "testMutableSequence") {
                test.testMutableSequence();
            } else if (command == "finish") {} else {
                std::cout << "unknown command.\n";
            }
        } while (command != "finish");
        
        std::cout << "The finish of program.\n";
    }
};

void showMenu() {
    UI ui{};
    ui.menu();
}
