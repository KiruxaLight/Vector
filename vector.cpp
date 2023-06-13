#include "vector.h"

#include <algorithm>
#include <iostream>

using ValueType = int;
using SizeType = size_t;
using DifferenceType = ptrdiff_t;

Vector::Vector() {
    size_ = 0;
    capacity_ = 0;
    data_ = new ValueType[size_];
}

Vector::Vector(size_t size) {
    size_ = size;
    capacity_ = size;
    data_ = new ValueType[size_];
    for (size_t index = 0; index < size_; ++index) {
        data_[index] = 0;
    }
}

Vector::Vector(std::initializer_list<ValueType> list) {
    size_ = list.size();
    capacity_ = list.size();
    data_ = new ValueType[size_];
    for (size_t index = 0; auto x : list) {
        data_[index] = x;
        ++index;
    }
}

Vector::Vector(const Vector& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new ValueType[size_];
    for (size_t index = 0; index < size_; ++index) {
        data_[index] = other.data_[index];
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (data_ == other.data_) {
        return *this;
    }
    delete[] data_;
    size_ = other.size_;
    capacity_ = other.size_;
    data_ = new ValueType[size_];
    for (size_t index = 0; index < size_; ++index) {
        data_[index] = other.data_[index];
    }
    return *this;
}

Vector::~Vector() {
    delete[] data_;
}

SizeType Vector::Size() const {
    return size_;
}

SizeType Vector::Capacity() const {
    return capacity_;
}

const ValueType* Vector::Data() const {
    return data_;
}

ValueType& Vector::operator[](size_t position) {
    return data_[position];
}
ValueType Vector::operator[](size_t position) const {
    return data_[position];
}

bool Vector::operator==(const Vector& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (size_t index = 0; index < size_; ++index) {
        if (data_[index] != other.data_[index]) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

std::strong_ordering Vector::operator<=>(const Vector& other) const {
    size_t min_size = std::min(size_, other.size_);
    for (size_t index = 0; index < min_size; ++index) {
        if (data_[index] < other.data_[index]) {
            return std::strong_ordering::less;
        }
    }
    if (size_ == other.size_) {
        return std::strong_ordering::equal;
    }
    if (size_ > other.size_) {
        return std::strong_ordering::greater;
    }
    return std::strong_ordering::less;
}

void Vector::Reserve(SizeType new_capacity) {
    if (new_capacity > capacity_) {
        capacity_ = new_capacity;
        ValueType* data2 = new ValueType[capacity_];
        std::move(data_, data_ + size_, data2);
        std::swap(data_, data2);
        delete[] data2;
    }
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::PushBack(const ValueType& new_element) {
    if (capacity_ == 0) {
        capacity_ = 1;
        ValueType* data2 = new ValueType[capacity_];
        std::move(data_, data_ + size_, data2);
        data2[size_] = new_element;
        std::swap(data_, data2);
        delete[] data2;
        size_ = 1;
    } else {
        if (size_ == capacity_) {
            capacity_ <<= 1;
            ValueType* data2 = new ValueType[capacity_];
            std::move(data_, data_ + size_, data2);
            std::swap(data_, data2);
            delete[] data2;
        }
        data_[size_] = new_element;
        ++size_;
    }
}

void Vector::PopBack() {
    --size_;
}

void Vector::Swap(Vector& other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
}

Vector::Iterator Vector::Begin() {
    return Iterator(data_);
}

Vector::Iterator Vector::End() {
    return Iterator(data_ + size_);
}

Vector::Iterator Vector::begin() {
    return Iterator(data_);
}

Vector::Iterator Vector::end() {
    return Iterator(data_ + size_);
}

Vector::Iterator::Iterator(ValueType* pointer) {
    current_ = pointer;
}

Vector::Iterator::Iterator() {
}

ValueType& Vector::Iterator::operator*() const {
    return *current_;
}

ValueType* Vector::Iterator::operator->() const {
    return current_;
}

Vector::Iterator& Vector::Iterator::operator=(Iterator other) {
    current_ = other.current_;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator++() {
    ++current_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator now(*this);
    ++current_;
    return now;
}

Vector::Iterator& Vector::Iterator::operator--() {
    --current_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator--(int) {
    Iterator now(*this);
    --current_;
    return now;
}

Vector::Iterator Vector::Iterator::operator+(DifferenceType shift) {
    Iterator tmp;
    tmp.current_ = current_ + shift;
    return tmp;
}

DifferenceType Vector::Iterator::operator-(Iterator other) {
    DifferenceType diff = current_ - other.current_;
    return diff;
}

Vector::Iterator& Vector::Iterator::operator+=(DifferenceType shift) {
    current_ += shift;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator-=(DifferenceType shift) {
    current_ -= shift;
    return *this;
}

bool Vector::Iterator::operator==(const Iterator& other) const {
    return current_ == other.current_;
}

bool Vector::Iterator::operator!=(const Iterator& other) const {
    return current_ != other.current_;
}

std::strong_ordering Vector::Iterator::operator<=>(const Iterator& other) const {
    if (current_ < other.current_) {
        return std::strong_ordering::less;
    }
    if (current_ == other.current_) {
        return std::strong_ordering::equal;
    }
    return std::strong_ordering::greater;
}