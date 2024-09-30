#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Exception.h"
#include "ShrdPtrAtomic.h"  // Assuming ShrdPtrAtomic is similar to std::shared_ptr
#include "WeakPtrAtomic.h"  // Assuming WeakPtrAtomic is similar to std::weak_ptr

template <typename T>
class Node {
public:
    T value;
    WeakPtrAtomic<Node<T>> prev;  // Using WeakPtrAtomic for the backward reference
    ShrdPtrAtomic<Node<T>> next;  // Using ShrdPtrAtomic for the forward reference

public:
    // Constructor
    explicit Node(const T& n_val = T(), WeakPtrAtomic<Node<T>> n_prev = WeakPtrAtomic<Node<T>>(), ShrdPtrAtomic<Node<T>> n_next = nullptr)
        : value(n_val), prev(n_prev), next(n_next) {}
};

template <typename T>
class LinkedList {
private:
    int length;
    ShrdPtrAtomic<Node<T>> head;
    ShrdPtrAtomic<Node<T>> tail;

private:
    ShrdPtrAtomic<Node<T>> getNode(const int index) const {
        if (index < 0 || index >= length || !head.get()) throw IndexOutOfRange();
        ShrdPtrAtomic<Node<T>> temp = head;
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
    LinkedList() : length(0), head(nullptr), tail(nullptr) {}

    LinkedList(T* items, const int count) : length(0), head(nullptr), tail(nullptr) {
        for (int i = 0; i < count; ++i) {
            append(items[i]);
        }
        length = count;
    }

    explicit LinkedList(const int size) : length(0), head(nullptr), tail(nullptr) {
        if (size < 0) throw IndexOutOfRange();
        if (size > 0) {
            head = ShrdPtrAtomic<Node<T>>(new Node<T>);
            tail = head;
            for (int i = 1; i < size; ++i) {
                tail->next = ShrdPtrAtomic<Node<T>>(new Node<T>);
                tail->next->prev = tail;  // Use weak_ptr for backward reference
                tail = tail->next;
            }
        }
        length = size;
    }

    LinkedList(const LinkedList<T>& other) : length(0), head(nullptr), tail(nullptr) {
        ShrdPtrAtomic<Node<T>> temp = other.head;
        while (temp.get() != nullptr) {
            append(temp->value);
            temp = temp->next;
        }
        length = other.length;
    }

    // Destructor (smart pointers automatically manage memory)
    ~LinkedList() = default;

    // Methods
    T& get(int index) const {
        assertIndexCorrect(index);
        assertListNotEmpty();
        return getNode(index)->value;
    }

    T& getFirst() const {
        assertListNotEmpty();
        return head->value;
    }

    T& getLast() const {
        assertListNotEmpty();
        return tail->value;
    }

    LinkedList<T>* getSubList(int startIndex, int endIndex) const {
        assertListNotEmpty();
        assertIndexCorrect(startIndex);
        assertIndexCorrect(endIndex);
        if (startIndex > endIndex) throw IndexOutOfRange();

        auto* sublist = new LinkedList<T>();
        ShrdPtrAtomic<Node<T>> temp = getNode(startIndex);
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
        auto el = ShrdPtrAtomic<Node<T>>(new Node<T>(item, WeakPtrAtomic<Node<T>>(), ShrdPtrAtomic<Node<T>> ()));///
        if (!head.get()) {
            head = tail = el;
        } else {
            tail->next = el;
            el->prev = tail;  // Link the new node with the current tail
            tail = el;
        }
        length++;
    }

    void prepend(const T& item) {
        auto el = ShrdPtrAtomic<Node<T>>(new Node<T>(item, WeakPtrAtomic<Node<T>>(), head));
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
            ShrdPtrAtomic<Node<T>> curr = getNode(index);
            auto new_node = ShrdPtrAtomic<Node<T>>(new Node<T>(item, curr->prev, curr));
            auto prev_node = curr->prev.lock();
            if (prev_node.get()) {  // Lock the weak_ptr to get a strong pointer
                prev_node->next = new_node;
            }
            curr->prev = new_node;
            length++;
        }
    }

    LinkedList<T>* concat(LinkedList<T>* list) {
        auto* new_list = new LinkedList<T>(*this);
        ShrdPtrAtomic<Node<T>> el2 = list->head;
        while (el2.get()) {
            new_list->append(el2->value);
            el2 = el2->next;
        }
        return new_list;
    }

//    LinkedList<T>* concat(LinkedList<T> *list) {
//        auto *new_list = new LinkedList<T>(*this);
//        Node<T> *el1 = new_list->head;
//        Node<T> *el2 = list->head;
//        while (el1->next != nullptr) el1 = el1->next;
//
//        while (el1->next!=nullptr) {
//            el1->next = new Node<T>(el2->value);
//            el1->next->prev = el1;
//            el1 = el1->next;
//            el2 = el2->next;
//            ++new_list->length;
//        }
//        delete el1;
//        delete el2;
//        return new_list;


    void print() const {
        ShrdPtrAtomic<Node<T>> temp = head;
        while (temp) {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
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
