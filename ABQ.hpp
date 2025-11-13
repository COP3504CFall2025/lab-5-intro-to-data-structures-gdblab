#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <iostream>
using namespace std;

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t size_;
    T* data_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() : capacity_(1), size_(0), data_(new T[1]) {}
    explicit ABQ(const size_t capacity)
        : capacity_(capacity), size_(0), data_(new T[capacity]) {}

    ABQ(const ABQ& other)
        : capacity_(other.capacity_), size_(other.size_), data_(new T[other.capacity_]){
        for(size_t i = 0; i < other.size_; i++){
            this->data_[i] = other.data_[i];
        }

    }

    ABQ& operator=(const ABQ& rhs){
        if (this == &rhs) {return *this;}
        T* nData = new T[rhs.capacity_];

        for(size_t i = 0; i < rhs.size_; i++){
            nData[i] = rhs.data_[i];
        }

        delete[] this->data_;
        this->capacity_ = rhs.capacity_;
        this->size_ = rhs.size_;
        this->data_ = nData;

    
        return *this;
    }
    ABQ(ABQ&& other) noexcept
        : capacity_(other.capacity_), size_(other.size_), data_(other.data_) {
        
        other.capacity_ = 0;
        other.size_ = 0;
        other.data_ = nullptr;

    }

    ABQ& operator=(ABQ&& rhs) noexcept{
        if (this == &rhs) {return *this;}
        delete[] this->data_;

        this->capacity_ = rhs.capacity_;
        this->size_ = rhs.size_;
        this->data_ = rhs.data_;

        rhs.data_ = nullptr;
        rhs.size_ = 0;
        rhs.capacity_ = 0;
    
        return *this;
    }
    ~ABQ() noexcept{
        delete[] data_;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override{
        return size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept{
        return capacity_;
    }
    [[nodiscard]] T* getData() const noexcept{
        return data_;
    }

    // Insertion
    void enqueue(const T& data) override{
        if (size_ == capacity_){
            size_t nCap = capacity_ * scale_factor_;
            T* nData = new T[nCap];
            for (size_t i = 0; i < capacity_; i++){
                nData[i] = data_[i];
            }

            delete[] data_;
            data_ = nData;
            capacity_ = nCap;
        }
        data_[size_] = data;
        size_++;
    }

    // Access
    T peek() const override{
        if(size_ == 0) {throw underflow_error("Empty"); }
        return data_[0];
    }

    // Deletion
    T dequeue() override{
        if(size_ == 0) {throw underflow_error("Empty
        T rem = data_[0];
        for (size_t i = 0; i < size_-1; i++){
                data_[i] = data_[i+1];
        }
        size_--;
        return rem;
    }

    void printForward() const{
        if (size_ == 0) {return;}
		for(size_t i = 0; i < size_; i++){
			cout << data_[i]<<endl;
		}
	}
	void printReverse() const{
        if (size_ == 0) {return;}
		for(size_t i = size_ - 1; i < size_; i--){
			cout << data_[i] <<endl;
            if (i == 0){
                break;
            }
		}
	}

};
