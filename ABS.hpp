#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
using namespace std;
// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS(): capacity_(1), size_(0), data_(new T[1]) {}

    explicit ABS(const size_t capacity): capacity_(capacity), size_(0), data_(new T[capacity]) {}

    ABS(const ABS& other)
        : capacity_(other.capacity_), size_(other.size_), data_(new T[other.capacity_]){

        for(size_t i = 0; i < other.size_; i++){
            this->data_[i] = other.data_[i];
        }
    }

    ABS& operator=(const ABS& rhs){

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

    ABS(ABS&& other) noexcept
        : capacity_(other.capacity_), size_(other.size_), data_(other.data_) {
        
        other.capacity_ = 0;
        other.size_ = 0;
        other.data_ = nullptr;

    }

    ABS& operator=(ABS&& rhs) noexcept{
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

    ~ABS() noexcept{
        delete[] data_;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override{
        return size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept{
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept{
        return data_;
    }

    // Push item onto the stack
    void push(const T& data) override{
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

    T peek() const override{
        if(size_ == 0) {throw underflow_error("Empty"); }
        return data_[size_-1];
    }

    T pop() override{
        if(size_ == 0) {throw underflow_error("Empty"); }
        if (capacity_ > 1 && size_ <= capacity_ / 4){
            size_t nCap = capacity_ / scale_factor_;
            T* nData = new T[nCap];
            for (size_t i = 0; i < size_; i++){
                nData[i] = data_[i];
            }

            delete[] data_;
            data_ = nData;
            capacity_ = nCap;
        }
        T pop = data_[size_ - 1]; 
        size_--;
        return pop;
    }

private:
    size_t capacity_;
    size_t size_;
    T* data_;
    static constexpr size_t scale_factor_ = 2;
};
