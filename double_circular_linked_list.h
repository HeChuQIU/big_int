//
// Created by hechu on 23-11-20.
//

#ifndef INTEGER_CALCULATOR_DOUBLE_CIRCULAR_LINKED_LIST_H
#define INTEGER_CALCULATOR_DOUBLE_CIRCULAR_LINKED_LIST_H

#include <iterator>
#include <iostream>
#include <vector>

template<class T>
class double_circular_linked_list {
public:
    struct node {
    public:
        T value;
        node *prev;
        node *next;
        bool isHead = false;

        explicit node() = default;

        explicit node(T value) {
            this->value = value;
        }
    };

    struct iterator : public std::iterator<std::forward_iterator_tag, T> {
        typedef iterator Self;
        typedef T &reference;
        typedef T *pointer;

        node *currNode;

        explicit iterator(double_circular_linked_list &list) {
            this->currNode = list.head;
        }

        explicit iterator(struct node *node) {
            this->currNode = node;
        }

        Self &operator++() {
            currNode = currNode->next;
            return *this;
        }

        reference operator*() {
            return currNode->value;
        }

        bool operator!=(const Self &other) const {
            return currNode != other.currNode;
        }
    };

    node *head;

    iterator begin() const{
        return iterator(head->next);
    }

    iterator end() const{
        return iterator(head);
    }

    double_circular_linked_list() {
        head = new node();
        head->next = head;
        head->prev = head;
    }

    void insert(T v, int pos = 0) {
        auto curr = get_node(pos);
        auto newNode = new node(v);
        newNode->next = curr->next;
        newNode->prev = curr;
        newNode->next->prev = newNode;
        curr->next = newNode;
    }

    void remove(int pos) {
        auto curr = get_node(pos);
        curr->next = curr->next->next;
    }

    node *get_node(int pos) {
        auto curr = head;
        while (pos != 0) {
            if (pos > 0) {
                curr = curr->next;
                pos--;
            } else {
                curr = curr->prev;
                pos++;
            }
//            if (curr == head) return;
        }
        return curr;
    }

    T get(int pos) {
        return get_node(pos)->value;
    }

     size_t node_count() const {
        size_t i = 0;
        for (const auto &item: *this)
            i++;
        return i;
    }
};


#endif //INTEGER_CALCULATOR_DOUBLE_CIRCULAR_LINKED_LIST_H
