#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Exception.h"
#include "ShrdPtr.h"
#include "WeakPtr.h"

template <typename T>
class Node {
public:
    T value;
    WeakPtr<Node<T>> prev;  // Using WeakPtr for the backward reference
    ShrdPtr<Node<T>> next;  // Using ShrdPtr for the forward reference

public:
    // Constructor
    // explicit Node(const T& n_val = T(), WeakPtr<Node<T>> n_prev = WeakPtr<Node<T>>(), ShrdPtr<Node<T>> n_next = nullptr)
    //     : value(n_val), prev(n_prev), next(n_next) {}
    explicit Node(const T& n_val = T(), WeakPtr<Node<T>> n_prev = WeakPtr<Node<T>>(), ShrdPtr<Node<T>> n_next = ShrdPtr<Node<T>>(nullptr))// WeakPtr<Node<T>> n_prev = WeakPtr<Node<T>>() == nullptr
        : value(n_val), prev(n_prev), next(n_next) {}
    explicit Node(): value(T()), prev(), next(nullptr) {};


};

template <typename T>
class LinkedList {
private:
    int length;
    ShrdPtr<Node<T>> head;
    WeakPtr<Node<T>> tail;

private:
    ShrdPtr<Node<T>> getNode(const int index) const {
        if (index < 0 || index >= length || !head.get()) throw IndexOutOfRange();
        ShrdPtr<Node<T>> temp = head;
        for (int pos = 0; pos < index; ++pos) temp = temp->next;
        return temp;
    }

    void assertIndexCorrect(int index) const {
        if (index >= length || index < 0) throw IndexOutOfRange();
    }

    void assertListNotEmpty() const {
        if (!head.get()) throw EmptyListException();
    }

public:
    // Constructors
    LinkedList() : length(0), head(nullptr), tail() {}

    LinkedList(T* items, const int count) : length(0), head(nullptr), tail() {
        for (int i = 0; i < count; ++i) {
            append(items[i]);
        }
        length = count;
    }

    explicit LinkedList(const int size) : length(0), head(nullptr), tail() {
        if (size < 0) throw IndexOutOfRange();
        if (size > 0) {
            head = ShrdPtr<Node<T>>(new Node<T>);
            WeakPtr<Node<T>> tail(head);
            for (int i = 1; i < size; ++i) {
                tail->next = ShrdPtr<Node<T>>(new Node<T>);
                tail->next->prev = tail;  // Use weak_ptr for backward reference
                tail = tail->next;
            }
        }
        length = size;
    }

    LinkedList(const LinkedList<T>& other) : length(0), head(nullptr), tail() {
        ShrdPtr<Node<T>> temp = other.head;
        while (temp.get() != nullptr) {
            append(temp->value);
            temp = temp->next;
        }
        length = other.length;
    }
    
    ~LinkedList() = default;

    // Methods
    T& get(const int index) const{
        assertIndexCorrect(index);
        assertListNotEmpty();
        ShrdPtr<Node<T>> temp = head;
        for (int pos = 0; pos < index; ++pos) temp = temp->next;
        return temp->value;
        // return getNode(index)->value;
    }

    T& getFirst() const{
        assertListNotEmpty();
        return head->value;
    }

    T& getLast() const{
        assertListNotEmpty();
        return tail->value;
    }

    LinkedList<T>* getSubList(int startIndex, int endIndex) const {
        assertListNotEmpty();
        assertIndexCorrect(startIndex);
        assertIndexCorrect(endIndex);
        if (startIndex > endIndex) throw IndexOutOfRange();

        auto* sublist = new LinkedList<T>();
        ShrdPtr<Node<T>> temp = getNode(startIndex);
        for (int i = startIndex; i <= endIndex; i++) {
            sublist->append(temp->value);
            temp = temp->next;
        }
        return sublist;
    }

    int getLength() const {
        return length;
    }

    void append(const T& item) {
       // auto el = ShrdPtr<Node<T>>(new Node<T>(item, WeakPtr<Node<T>>(), nullptr));//!!!
       // auto el = ShrdPtr<Node<T>>(new Node<T>(item, WeakPtr<Node<T>>(), ShrdPtr<Node<T>>(nullptr)));
        auto el = ShrdPtr<Node<T>>(new Node<T>(item));
        if (!head.get()) {
            head = tail = el;
        } else {
            tail->next = el;
            el->prev = tail;
            tail = el;
        }
        length++;
    }

    void prepend(const T& item) {
        auto el = ShrdPtr<Node<T>>(new Node<T>(item, WeakPtr<Node<T>>(), head));//WeakPtr<Node<T>>() ???
        if (head.get()) {
            head->prev = el;
        } else {
            tail = el;
        }
        head = el;
        length++;
    }

    void set(int index, const T& item) {
        assertIndexCorrect(index);
        getNode(index)->value = item;
    }

    void insertAt(const T& item, int index) {
        if (index < 0 || index > length) throw IndexOutOfRange();

        if (index == 0) {
            prepend(item);
        } else if (index == length) {
            append(item);
        } else {
            ShrdPtr<Node<T>> curr = getNode(index);
            auto new_node = ShrdPtr<Node<T>>(new Node<T>(item, curr->prev, curr));
            auto prev_node = curr->prev.lock();
            if (prev_node.get()) {
                prev_node->next = new_node;
            }
            curr->prev = new_node;
            length++;
        }
    }

    LinkedList<T>* concat(const LinkedList<T>* list) {
        auto* new_list = new LinkedList<T>(*this);
        ShrdPtr<Node<T>> el2 = list->head;
        while (el2.get()) {
            new_list->append(el2->value);
            el2 = el2->next;
        }
        return new_list;
    }

    void print() const {
        ShrdPtr<Node<T>> temp = head;
        while (temp.get()) {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void clear() {
        if (this->getLength() == 0) return;
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    bool operator==(const LinkedList<T>& other) const {
        if (this == &other) return true;
        if (length == other.getLength()) {
            for (int i = 0; i < length; ++i) {
                if ((*this).get(i) != other.get(i)) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

#endif // LINKEDLIST_H
