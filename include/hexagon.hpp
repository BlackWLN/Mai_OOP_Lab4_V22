#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "figure.hpp"

template<Scalar T>
class Hexagon : public Figure<T> { //то же самое
private:
    std::unique_ptr<Point<T>> vertices[6];
    Point<T> center_;
    T radius;
    
    void calculateVertices();
    
public:
    Hexagon() : center_(0, 0), radius(1) {
        calculateVertices();
    }
    
    Hexagon(const Point<T>& center, T rad) : center_(center), radius(rad) {
        calculateVertices();
    }
    
    Hexagon(const Hexagon& other);
    Point<T> center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    bool operator==(const Figure<T>& other) const override;
    std::shared_ptr<Figure<T>> clone() const override;
};

#endif