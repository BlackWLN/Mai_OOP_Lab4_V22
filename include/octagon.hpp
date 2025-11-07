#ifndef OCTAGON_HPP
#define OCTAGON_HPP

#include "figure.hpp"

template<Scalar T>
class Octagon : public Figure<T> { //то же самое
private:
    std::unique_ptr<Point<T>> vertices[8];
    Point<T> center_;
    T radius;
    
    void calculateVertices();
    
public:
    Octagon() : center_(0, 0), radius(1) {
        calculateVertices();
    }
    
    Octagon(const Point<T>& center, T rad) : center_(center), radius(rad) {
        calculateVertices();
    }
    
    Octagon(const Octagon& other);
    Point<T> center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    bool operator==(const Figure<T>& other) const override;
    std::shared_ptr<Figure<T>> clone() const override;
};

#endif