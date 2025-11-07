#include <iostream>
#include "../include/array.hpp"
#include "../include/pentagon.hpp"
#include "../include/hexagon.hpp"
#include "../include/octagon.hpp"

template<typename T>
void Array<T>::resize(int new_capacity) {
    T* new_data = new T[new_capacity];
    for (int i = 0; i < size_; ++i) {
        new_data[i] = std::move(data[i]);
    }
    delete[] data;
    data = new_data;
    capacity_ = new_capacity;
}

template<typename T>
Array<T>::Array() : data(new T[10]), size_(0), capacity_(10) {}

template<typename T>
Array<T>::~Array() {
    delete[] data;
}

template<typename T>
Array<T>::Array(Array&& other) noexcept : data(other.data), size_(other.size_), capacity_(other.capacity_) {
    other.data = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template<typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template<typename T>
void Array<T>::add(const T& item) {
    if (size_ == capacity_) {
        resize(capacity_ * 2);
    }
    data[size_++] = item;
}

template<typename T>
void Array<T>::remove(int index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    for (int i = index; i < size_ - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    --size_;
}

template<typename T>
T& Array<T>::operator[](int index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    return data[index];
}

template<typename T>
const T& Array<T>::operator[](int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    return data[index];
}

template<typename T>
int Array<T>::size() const { return size_; }

template<typename T>
int Array<T>::capacity() const { return capacity_; }

template<typename T>
double Array<T>::totalArea() const {
    double total = 0;
    for (int i = 0; i < size_; ++i) {
        total += static_cast<double>(*data[i]);
    }
    return total;
}

template<typename T>
void Array<T>::printAll() const {
    for (int i = 0; i < size_; ++i) {
        std::cout << "Figure " << i << ": ";
        data[i]->print(std::cout);
        auto c = data[i]->center();
        std::cout << " | Center: " << c << " | Area: " << data[i]->area() << std::endl;
    }
}

template class Array<std::shared_ptr<Figure<int>>>;
template class Array<std::shared_ptr<Figure<float>>>;
template class Array<std::shared_ptr<Figure<double>>>;
template class Array<std::shared_ptr<Figure<long double>>>;