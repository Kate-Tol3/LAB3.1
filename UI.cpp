#include <iostream>
#include "Sequence.h" // для функции printSubsequence
#include "MutableListSequence.h"
#include <string>
#include "UI.h"

template <typename T>
struct UserSequence {

private:

    MutableListSequence<T>* sequence = new MutableListSequence<T>;

public:

    ~UserSequence() {
        delete sequence;

    }

    UserSequence() = default;

    void setValue() {
        int index;
        std::string s_index;
        std::cout << "Enter the index of element: ";
        std::cin >> s_index;
        try {
            index = std::stoi(s_index);
        }
        catch (std::invalid_argument& ex) {
            std::cout << "Invalid type. Must be number. Try again.";
        }
        std::cout << "Enter the value:";
        try {
            std::cin >> (*sequence)[index];
        } catch (IndexOutOfRange& ex) {
            std::cout << "Invalid index. Try Again.\n\n";
            insertValue();
        }
        catch (EmptyListException& ex) {
            std::cout << "sequence is empty\n\n";
        }

        std::cout << "The value was successfully set\n\n";
    }

    void printValue() {

        int index;
        std::string s_index;
        std::cout << "Enter the index of element: ";
        std::cin >> s_index;
        try {
            index = std::stoi(s_index);
        }
        catch (std::invalid_argument& ex) {
            std::cout << "Invalid type. Must be number. Try again.";
        }
        try {
            std::cout << sequence->get(index) << std::endl;
        }
        catch (IndexOutOfRange& ex) {
            std::cout << "Invalid index.\n\n";
        }
        catch (EmptyListException& ex) {
            std::cout << "Sequence is empty\n\n";
        }
        std::cout << "\n\n";

    }

    void getLength() {
        std::cout << "Length of sequence is ";
        std::cout << sequence->getLength() << std::endl;
        std::cout << "\n\n";
    }

    void insertValue() {
        int index;
        std::string s_index;
        std::cout << "Enter index where insert: ";
        std::cin >> s_index;
        try {
            index = std::stoi(s_index);
        }
        catch (std::invalid_argument& ex) {
            std::cout << "Invalid type. Must be number. Try again.";
        }

        std::cout << "Enter the value:";
        try {
            T item;
            std::cin >> item;
            sequence->insertAt(item, index);
            std::cout << "The value was successfully inserted\n\n";
        } catch (IndexOutOfRange& ex) {
            std::cout << "Invalid index. Try Again.\n\n";
        }
        catch (EmptyListException& ex) {
            std::cout << "sequence is empty\n\n";
        }

    }

    void appendValue() {
        std::cout << "Enter the value of element: ";
        T item;
        std::cin >> item;
        sequence->append(item);
        std::cout << "\nThe value was successfully added\n\n";
    }

    void prependValue() {
        std::cout << "Enter the value of element: ";
        T item;
        std::cin >> item;
        sequence->prepend(item);
        std::cout << "\nThe value was successfully added\n\n";
    }

    void printFirst() {
        std::cout << "first element is: ";
        try {
            std::cout << sequence->getFirst();
        } catch(IndexOutOfRange& ex) {
            std::cout << "Invalid index.\n\n";
        }
        std::cout << "\n\n";

    }

    void printLast() {
        std::cout << "last element is: ";
        try {
            std::cout << sequence->getLast();
        } catch(std::out_of_range& ex) {
            std::cout << "Invalid index.\n\n";
        }
            std::cout << "\n\n";
    }

    void printSequence() {
        if (sequence->getLength() == 0) {
            std::cout << "Sequence is empty.\n\n";
            return;
        }
        std::cout << "Your Sequence:\n";
        sequence->print();
        std::cout << "\n\n";

    }

    void printSubsequence() {
        int start;
        int end;
        std::string s_index;

        std::cout << "Enter start index of your subsequence:";
        std::cin >> s_index;
        try {
            start = std::stoi(s_index);
        }
        catch (std::invalid_argument& ex) {
            std::cout << "Invalid type. Must be number. Try again.";
        }

        std::cout << "Enter end index of your subsequence:";
        std::cin >> s_index;
        try {
            end = std::stoi(s_index);
        }
        catch (std::invalid_argument& ex) {
            std::cout << "Invalid type. Must be number. Try again.";
        }


        try {
            Sequence<T>* subsequence = sequence->getSubsequence(start, end);
            subsequence->print();
            delete subsequence;
        } catch (IndexOutOfRange& ex) {
            std::cout << "Invalid index. Try Again.\n\n";
            printSubsequence();
        }
        catch (EmptyListException& ex) {
            std::cout << "sequence is empty\n\n";
        }
        std::cout << "\n";

    }

};

template <typename T>
class UI_Sequence {

private:

    void showList() {
        std::cout << "\nSelect action:\n"
            << "*** printSequence\n"
            << "*** printElement\n"
            << "*** printFirst\n"
            << "*** printLast\n"
            << "*** insertValue\n"
            << "*** appendValue\n"
            << "*** prependValue\n"
            << "*** setValue\n"
            << "*** printSubsequence\n"
            << "*** getLength\n"
            << "*** exit.\n";
    }

public:
    void menu() {

        showList();
        std::string command;

        UserSequence<T> userSequence;

        do {
            std::cout << "Enter the command:\n-> ";
            std::cin >> command;
            if (command == "printSequence") {
                userSequence.printSequence();
            } else if (command == "printElement") {
                userSequence.printValue();
            } else if (command == "printFirst") {
                userSequence.printFirst();
            } else if (command == "printLast") {
                userSequence.printLast();
            } else if (command == "insertValue") {
                userSequence.insertValue();
            } else if (command == "appendValue") {
                userSequence.appendValue();
            } else if (command == "prependValue") {
                userSequence.prependValue();
            } else if (command == "setValue") {
                userSequence.setValue();
            } else if (command == "printSubsequence") {
                userSequence.printSubsequence();
            } else if (command == "getLength") {
                userSequence.getLength();
            } else if (command == "exit") {} else {
                std::cout << "unknown command.\n";
            }
        } while (command != "exit");

        std::cout << "The end of the program.\n";
    }

};

void getArgument(int* i_arg) {
    std::string s_arg;
    std::cin >> s_arg;
    try {
        *i_arg = std::stoi(s_arg);
    }
    catch (std::invalid_argument& ex) {
        *i_arg = -10000000;
    }
}

int getElemsType() {
    std::string s_type;
    int i_type;
    std::cout << "Select the type of elements in your sequence:\n"
       << "int    --> enter 1\n"
       << "double --> enter 2\n"
       << "string --> enter 3.\n";
    getArgument(&i_type);

    while (i_type < 1 || i_type > 3) {
        std::cout << "\nInvalid element type. Try again.\n\n";
        getArgument(&i_type);
    }
    return i_type;
}

void showMenu() {
    std::cout << "This program allows you to operate Sequences. Let's start!\n\n";
    int sequenceType = getElemsType();
    if (sequenceType == 1) {
        UI_Sequence<int> ui;
        ui.menu();
    } else if (sequenceType == 2) {
        UI_Sequence<double> ui;
        ui.menu();
    } else if (sequenceType == 3) {
        UI_Sequence<std::string> ui;
        ui.menu();
    }
}
