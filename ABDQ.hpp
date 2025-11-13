#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ(): capacity_(1), size_(0), data_(new T[1]), front_(0), back_(0) {}
    explicit ABDQ(std::size_t capacity) : capacity_(capacity), size_(0), data_(new T[capacity]), front_(0), back_(0) {}

    ABDQ(const ABDQ& other)
        : capacity_(other.capacity_), size_(other.size_), data_(new T[other.capacity_]), front_(other.front_), back_(other.back_) {

        for(size_t i = 0; i < other.size_; i++){
            this->data_[i] = other.data_[i];
        }

    }

    ABDQ(ABDQ&& other) noexcept
        : capacity_(other.capacity_), size_(other.size_), data_(other.data_), front_(other.front_), back_(other.back_) {
        
        other.front_ = 0;
        other.back_ = 0;
        other.capacity_ = 0;
        other.size_ = 0;
        other.data_ = nullptr;
  
    }

    ABDQ& operator=(const ABDQ& other){
        if (this == &other) {return *this;}
        T* nData = new T[other.capacity_];

        for(size_t i = 0; i < other.size_; i++){
            nData[i] = other.data_[i];
        }

        delete[] this->data_;
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->data_ = nData;
        this->front_ = other.front_;
        this->back_ = other.back_;

        return *this;
    }
    
    ABDQ& operator=(ABDQ&& other) noexcept{
        if (this == &other) {return *this;}
        delete[] this->data_;

        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->data_ = other.data_;
        this->front_ = other.front_;
        this->back_ = other.back_;
    

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    
        return *this;
    }

    ~ABDQ() noexcept{
        delete[] data_;
    }

    // Insertion
    void pushFront(const T& item) override{
        if (size_ == capacity_){
            size_t nCap = capacity_ * SCALE_FACTOR;
            T* nData = new T[nCap];
            for (size_t i = 0; i < size_; i++){
                nData[i] = data_[(front_ + i) % capacity_];
            }

            delete[] data_;
            data_ = nData;
            capacity_ = nCap;
            front_ = 0;
            back_ = size_;
        }

        front_ = (front_ == 0) ? capacity_ - 1 : front_ - 1;
        data_[front_] = item;
        ++size_;

    }
    
    void pushBack(const T& item) override{
        if (size_ == capacity_){
            size_t nCap = capacity_ * SCALE_FACTOR;
            T* nData = new T[nCap];
            for (size_t i = 0; i < size_; i++){
                nData[i] = data_[(front_ + i) % capacity_];
            }

            delete[] data_;
            data_ = nData;
            capacity_ = nCap;
            front_ = 0;
            back_ = size_;
        }

        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        ++size_;
    }

    // Deletion
    T popFront() override{
        if(size_ == 0) {throw underflow_error("Empty"); }
        T pop = data_[front_];
        size_--;

        front_ = (front_ + 1) % capacity_;
        if (capacity_ > 1 && size_ <= capacity_ / 4){
            size_t nCap = capacity_ / SCALE_FACTOR;
            T* nData = new T[nCap];
            for (size_t i = 0; i < size_; i++){
                nData[i] = data_[(front_ + i) % capacity_];
            }

            delete[] data_;
            data_ = nData;
            capacity_ = nCap;
            front_ = 0;
            back_ = size_;
        } 
        return pop;
    }

    T popBack() override{
        if(size_ == 0) {throw underflow_error("Empty"); }
        back_ = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        T pop = data_[back_];
        size_--;
        if (capacity_ > 1 && size_ < capacity_ / 4){
            size_t nCap = capacity_ / SCALE_FACTOR;
            T* nData = new T[nCap];
            for (size_t i = 0; i < size_; i++){
                nData[i] = data_[(front_ + i) % capacity_];
            }

            delete[] data_;
            data_ = nData;
            capacity_ = nCap;
            front_ = 0;
            back_ = size_;
        }
        return pop;
    }

    // Access
    const T& front() const override{
        if(size_ == 0) {throw underflow_error("Empty"); }
        return data_[front_];
    }
    const T& back() const override{
        if(size_ == 0) {throw underflow_error("Empty"); }
        size_t back = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        return data_[back];
    }

    // Getters
    std::size_t getSize() const noexcept override{
        return size_;
    }

};
