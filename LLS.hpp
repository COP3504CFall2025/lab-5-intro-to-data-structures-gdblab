#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() : list() {}

    LLS(const LLS&) = default;
    LLS& operator=(const LLS&) = default;

    LLS(LLS&& other) noexcept : list (move(other.list)) {}

    LLS operator=(LLS&& other) noexcept {
        if (this == &other) {return *this;}

        list = move(other.list);
        return *this;
    }

    // Insertion
    void push(const T& item) override{
        list.addHead(item);
    }

    // Deletion
    T pop() override{
        if (getSize() == 0){
            throw underflow_error("Empty");
        }
        T pop = list.getHead()->data;
        list.removeHead();
        return pop;
    }

    // Access
    T peek() const override{
        if (getSize() == 0){
            throw underflow_error("Empty");
        }
        return list.getHead()->data;
    }

    //Getters
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }

    void printForward() const{
        list.printForward();
    }

    void printReverse() const{
        list.printReverse();
    }
    

    ~LLS() noexcept {
        list.clear();
    }

};