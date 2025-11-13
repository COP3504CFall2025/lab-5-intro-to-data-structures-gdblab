#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() : list() {}

    // Insertion
    void enqueue(const T& item) override{
        list.addTail(item);
    }

    // Deletion
    T dequeue() override{
        if (getSize() == 0){
            throw underflow_error("Empty");
        }
        T deq = list.getHead()->data;
        list.removeHead();
        return deq;
    }

    // Access
    T peek() const override{
        if (getSize() == 0){
            throw underflow_error("Empty");
        }
        return list.getHead()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

    void printForward() const{
        list.printForward();
    }

    void printReverse() const{
        list.printReverse();
    }

    ~LLQ() noexcept {
        list.clear();
    }

};