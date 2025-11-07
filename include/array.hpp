#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "figure.hpp"

template<typename T>
class Array {
private:
    T* data; //указатель на массив с фигурами
    int size_; //размер
    int capacity_; //вместимость
    
    void resize(int new_capacity); //увеличение размера
    
public:
    Array(); //конструктор
    ~Array(); //деструктор
    Array(const Array&) = delete; //копирование
    Array& operator=(const Array&) = delete;
    Array(Array&& other) noexcept; //перемещение
    Array& operator=(Array&& other) noexcept;
    
    void add(const T& item); //добавить фигуру
    void remove(int index); //удалить по индексу
    T& operator[](int index); //достать по индексу
    const T& operator[](int index) const; //доступ
    int size() const; //текущий размер
    int capacity() const; //вместимость
    double totalArea() const; //общая площадь
    void printAll() const; //печать всего
};

#endif