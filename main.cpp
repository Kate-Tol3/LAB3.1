#include <iostream>
#include "UI.h"
#include "TestUI.h"

int main() {

    std::cout << "Hello User! Select menu:" << std::endl;
    std::cout << "\nMenu to work with sequence --> type sequenceMenu\nMenu to run tests --> type testMenu" << std::endl;
    std::string menuType;
    do {
        std::cout << "\nEnter the menu type:\n-> ";
        std::cin >> menuType;
        if (menuType == "sequenceMenu") {
            showMenu();
        } else if (menuType == "testMenu") {
            printTestShowcase();
        } else if (menuType == "exit") {} else {
            std::cout << "unknown type.\n";
        }
    } while (menuType != "exit");

    std::cout << "The end of the program.\n";

    return 0;
}
