#ifndef POINT_HPP
#define POINT_HPP

#include <memory>
#include <cmath>
#include <iostream>
#include <type_traits>
#include <concepts>

template<typename T>
concept Scalar = std::is_scalar_v<T>; //задаем что тип скалярный - int, float, double и прочее

template<Scalar T>
class Point {
private:
    std::unique_ptr<T> x; //умные указатели на х и у, деструктор не нужен
    std::unique_ptr<T> y;
public:
    Point(T x_val = 0, T y_val = 0) : //конструктор
        x(std::make_unique<T>(x_val)), //выделяем память
        y(std::make_unique<T>(y_val)) {}
    
    Point(const Point& other) : //конструктор копирования
        x(std::make_unique<T>(*other.x)), 
        y(std::make_unique<T>(*other.y)) {}
    
    Point(Point&& other) noexcept = default; //конструктор перемещения
    
    Point& operator=(const Point& other) { //оператор присваивания копированием
        if (this != &other) {
            *x = *other.x;
            *y = *other.y;
        }
        return *this;
    }
    
    Point& operator=(Point&& other) noexcept = default; //оператор перемещащего присваивания
    
    T getX() const { return *x; } //геттер - возвращаем значение, а не указатель
    T getY() const { return *y; }
    void setX(T val) { *x = val; } //сеттер - меняем значение через разыменовывание указателей
    void setY(T val) { *y = val; }
    
    bool operator==(const Point& other) const { //оператор сравнения
        if constexpr (std::is_floating_point_v<T>) {
            return std::abs(*x - *other.x) < 1e-9 && std::abs(*y - *other.y) < 1e-9;
        } else {
            return *x == *other.x && *y == *other.y;
        }
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) { //дружественная функция для вывода, переопределяем
        os << "(" << p.getX() << ", " << p.getY() << ")";
        return os;
    }
};

#endif