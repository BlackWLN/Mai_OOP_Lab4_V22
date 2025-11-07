#ifndef PENTAGON_HPP
#define PENTAGON_HPP

#include "figure.hpp"

template<Scalar T>
class Pentagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertices[5]; //массив вершин
    Point<T> center_; //центр пятиугольника
    T radius; //радиус описанной вокруг фигуры окружности
    
    void calculateVertices(); //метод для вычисления вершин
    
public:
    Pentagon() : center_(0, 0), radius(1) { //конструктор по умолчанию
        calculateVertices();
    }
    
    Pentagon(const Point<T>& center, T rad) : center_(center), radius(rad) { //конструктор с центром и радиусом
        calculateVertices();
    }
    
    Pentagon(const Pentagon& other); //конструктор копирования
    Point<T> center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    bool operator==(const Figure<T>& other) const override;
    std::shared_ptr<Figure<T>> clone() const override;
};

#endif