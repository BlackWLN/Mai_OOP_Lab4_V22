#include <limits>
#include "../include/array.hpp"
#include "../include/pentagon.hpp"
#include "../include/hexagon.hpp"
#include "../include/octagon.hpp"

template<Scalar T>
void Pentagon<T>::calculateVertices() {
    for (int i = 0; i < 5; ++i) {
        T angle = 2 * M_PI * i / 5;
        vertices[i] = std::make_unique<Point<T>>(
            center_.getX() + radius * std::cos(angle),
            center_.getY() + radius * std::sin(angle)
        );
    }
}

template<Scalar T>
Pentagon<T>::Pentagon(const Pentagon& other) : center_(other.center_), radius(other.radius) {
    calculateVertices();
}

template<Scalar T>
Point<T> Pentagon<T>::center() const {
    return center_;
}

template<Scalar T>
double Pentagon<T>::area() const {
    if constexpr (std::is_integral_v<T>) {
        double r = static_cast<double>(radius);
        double side = 2 * r * std::sin(M_PI / 5);
        double apothem = r * std::cos(M_PI / 5);
        return (5 * side * apothem) / 2;
    } else {
        T side = 2 * radius * std::sin(M_PI / 5);
        T apothem = radius * std::cos(M_PI / 5);
        return static_cast<double>((5 * side * apothem) / 2);
    }
}

template<Scalar T>
void Pentagon<T>::print(std::ostream& os) const {
    os << "Pentagon: Center" << center_ << ", Radius: " << radius << ", Vertices: ";
    for (int i = 0; i < 5; ++i) {
        os << *vertices[i];
        if (i < 4) os << ", ";
    }
}

template<Scalar T>
void Pentagon<T>::read(std::istream& is) {
    T x, y, r;
    if (!(is >> x >> y >> r)) {
        throw std::runtime_error("Invalid input for pentagon.");
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
bool Pentagon<T>::operator==(const Figure<T>& other) const {
    const Pentagon* p = dynamic_cast<const Pentagon*>(&other);
    if (!p) return false;
    return center_ == p->center_ && radius == p->radius;
}

template<Scalar T>
std::shared_ptr<Figure<T>> Pentagon<T>::clone() const {
    return std::make_shared<Pentagon>(*this);
}

template class Pentagon<int>;
template class Pentagon<float>;
template class Pentagon<double>;
template class Pentagon<long double>;