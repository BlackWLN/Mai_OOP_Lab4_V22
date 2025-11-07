#include <limits>
#include "../include/array.hpp"
#include "../include/pentagon.hpp"
#include "../include/hexagon.hpp"
#include "../include/octagon.hpp"

template<Scalar T>
void Octagon<T>::calculateVertices() {
    for (int i = 0; i < 8; ++i) {
        T angle = 2 * M_PI * i / 8;
        vertices[i] = std::make_unique<Point<T>>(
            center_.getX() + radius * std::cos(angle),
            center_.getY() + radius * std::sin(angle)
        );
    }
}

template<Scalar T>
Octagon<T>::Octagon(const Octagon& other) : center_(other.center_), radius(other.radius) {
    calculateVertices();
}

template<Scalar T>
Point<T> Octagon<T>::center() const {
    return center_;
}

template<Scalar T>
double Octagon<T>::area() const {
    if constexpr (std::is_integral_v<T>) {
        double r = static_cast<double>(radius);
        double side = 2 * r * std::sin(M_PI / 8);
        double apothem = r * std::cos(M_PI / 8);
        return (8 * side * apothem) / 2;
    } else {
        T side = 2 * radius * std::sin(M_PI / 8);
        T apothem = radius * std::cos(M_PI / 8);
        return static_cast<double>((8 * side * apothem) / 2);
    }
}

template<Scalar T>
void Octagon<T>::print(std::ostream& os) const {
    os << "Octagon: Center" << center_ << ", Radius: " << radius << ", Vertices: ";
    for (int i = 0; i < 8; ++i) {
        os << *vertices[i];
        if (i < 7) os << ", ";
    }
}

template<Scalar T>
void Octagon<T>::read(std::istream& is) {
    T x, y, r;
    if (!(is >> x >> y >> r)) {
        throw std::runtime_error("Invalid input for octagon.");
    }
    if (r <= 0) {
        throw std::invalid_argument("Radius must be positive.");
    }
    if (!std::isfinite(x) || !std::isfinite(y)) {
        throw std::invalid_argument("Center coordinates must be finite numbers.");
    }
    center_ = Point<T>(x, y);
    radius = r;
    calculateVertices();
}

template<Scalar T>
bool Octagon<T>::operator==(const Figure<T>& other) const {
    const Octagon* o = dynamic_cast<const Octagon*>(&other);
    if (!o) return false;
    return center_ == o->center_ && radius == o->radius;
}

template<Scalar T>
std::shared_ptr<Figure<T>> Octagon<T>::clone() const {
    return std::make_shared<Octagon>(*this);
}


template class Octagon<int>;
template class Octagon<float>;
template class Octagon<double>;
template class Octagon<long double>;