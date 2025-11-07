#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "point.hpp"
#include <memory>
#include <iostream>

template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default; //деструктор
    virtual Point<T> center() const = 0; //центр
    virtual double area() const = 0; //площадь
    virtual void print(std::ostream& os) const = 0; //вывод
    virtual void read(std::istream& is) = 0; //ввод
    virtual bool operator==(const Figure<T>& other) const = 0; //сравнение
    virtual std::shared_ptr<Figure<T>> clone() const = 0; //копирование
    
    operator double() const { //плоащдь
        return area(); 
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        fig.read(is);
        return is;
    }
};

#endif