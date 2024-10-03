
#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <iostream>
#include "cmake-build-debug/ShrdPtrAtomic.h"

template <typename T>
class Node{
public:
        T value;
        Node<T> *prev;
        Node<T> *next;
public:
    explicit Node(const T &n_val = 0, Node<T> *n_prev = nullptr, Node<T> *n_next = nullptr):
        value(n_val), prev(n_prev), next(n_next){};
};

template <class T>
class LinkedList{
private:
    int length;
    Node<T>* head;
    Node<T>* tail;

private:
    Node<T>* getNode (int index) const{
        if (index<0 || index >=  length || head == nullptr) throw std::out_of_range("Index is out of range");
        Node<T>* temp = head;
        for (int pos = 0; pos < index; ++pos) temp = temp->next;
        return temp;
    }

    void assertIndexCorrect(int index) const  {
        if (index >= length || index < 0) throw std::out_of_range("Index is out of range");
    }

    void assertListNotEmpty() const{
        if (head == nullptr) throw std::out_of_range("LinkedList is empty");
    }

public:

    //constructors
    LinkedList():  length(0), head(nullptr), tail(nullptr) {};

    LinkedList(T* items, const int count): length(0), head(nullptr), tail(nullptr){
        if (count > 0) {
            head = nullptr;
            tail = nullptr;
            for (int i = 0; i < count; ++i) {
                append(items[i]);
            }
            length = count;
        }
    }

    explicit LinkedList(const int size):length(0), head(nullptr), tail(nullptr) {
        if (size < 0) throw std::invalid_argument("Invalid size");
        if (size > 0) {

            head = new Node<T>;
            tail = head;
            for (int i = 1; i < size; ++i) {
                tail->next = new Node<T>;
                tail = tail->next;
            }
        }
        length = size;
    };

    LinkedList(const LinkedList<T> &other): length(0), head(nullptr), tail(nullptr) {
        Node<T> *temp = other.head;
        while (temp != nullptr) {
            append(temp->value);
            temp = temp->next;
        }
        length = other.length;
    }

    //destructor
    ~LinkedList() {
        Node<T> *curr = head;
        while (curr) {
            Node<T> *temp = curr->next;
            delete curr;
            curr = temp;
        }
    }

    //methods
    T& get(const int index) const{
        assertIndexCorrect(index);
        assertListNotEmpty();
        Node<T> *temp = head;
        for (int pos = 0; pos < index; ++pos) temp = temp->next;
        return temp->value;
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
        if (startIndex > endIndex) throw std::out_of_range("startIndex > endIndex");

        auto *sublist = new LinkedList<T>();
        Node<T> *temp = getNode(startIndex);
        for (int i = startIndex; i <= endIndex;i++) {
            sublist->append(temp->value);
            temp = temp->next;
        }
        delete temp;
        return sublist;
    }

    int getLength() const{
        return length;
    }

    void append(const T& item) {
        auto *el = new Node<T>(item, nullptr, nullptr);
        if(head == nullptr) {
            head = tail = el;
            length++;
            return ;
        }
        tail->next = el;
        el->prev = tail;
        tail = el;
        length++;
    }

    void prepend(const T& item) {
        auto *el = new Node<T>(item, nullptr, head);
        if (head != nullptr) {
            head->prev = el;
        }
        else {tail = el;}
        head = el;
        length++;
    }

    void set(const int index,const T& item) {
        assertIndexCorrect(index);

        Node<T> *curr = head;
        for(int pos = 0; pos < index; ++pos) curr = curr->next;
        curr->value = item;

        delete curr;

    }

    void insertAt(const T& item,const int index) { // inserts node on stated index before previous
        if (index<0 || index >  length ) throw std::out_of_range("index > length");

        if (index == 0) {
            prepend(item);
        }
        else if (index == length) {
            append(item);
        }
        else {
            Node<T>* curr = head;
            auto *new_node = new Node<T>(item, nullptr, nullptr);
            for (int pos = 0; pos < index ; pos++) curr= curr->next;
            new_node->prev= curr->prev;
            curr->prev = new_node;
            new_node->next = curr;
            new_node->prev->next = new_node;
            length++;
        }
    }

    LinkedList<T>* concat(LinkedList<T> *list) {
        auto *new_list = new LinkedList<T>(*this);
        Node<T> *el1 = new_list->head;
        Node<T> *el2 = list->head;
        while (el1->next != nullptr) el1 = el1->next;

        while (el1->next!=nullptr) {
            el1->next = new Node<T>(el2->value);
            el1->next->prev = el1;
            el1 = el1->next;
            el2 = el2->next;
            ++new_list->length;
        }
        delete el1;
        delete el2;
        return new_list;

    }

    void print(){
        Node<T> *temp = head;
        int pos = 0;
        if (length == 1) {std::cout << head->value; return;}
        while (temp != nullptr){
            if (temp != head) std::cout<< " ";
            std::cout<< this->get(pos);
            temp = temp->next;
            pos++;
        }
        delete temp;//
    }

    //
    // const T& operator [] (int index) const{
    //     assertIndexCorrect(index);
    //     Node<T> *el = head;
    //     for (int i = 0; i < index; i++) el = el->next;
    //     return el->value;
    // }
    //
    // T& operator [] (int index) {
    //     assertIndexCorrect(index);
    //     Node<T> *el = head;
    //     for (int i = 0; i < index; i++) el = el->next;
    //     return el->value;
    // }

    bool operator==(const LinkedList<T>& other) {
        if (this == &other) return true;
        if (length == other.getLength()){
            for (int i = 0; i < length; ++i) {
                if ((*this).get(i) != (other).get(i)) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

};





#endif //LINKEDLIST_H

