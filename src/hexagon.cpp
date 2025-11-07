#include "../include/array.hpp"
#include "../include/pentagon.hpp"
#include "../include/hexagon.hpp"
#include "../include/octagon.hpp"

template<Scalar T>
void Hexagon<T>::calculateVertices() {
    for (int i = 0; i < 6; ++i) {
        T angle = 2 * M_PI * i / 6;
        vertices[i] = std::make_unique<Point<T>>(
            center_.getX() + radius * std::cos(angle),
            center_.getY() + radius * std::sin(angle)
        );
    }
}

template<Scalar T>
Hexagon<T>::Hexagon(const Hexagon& other) : center_(other.center_), radius(other.radius) {
    calculateVertices();
}

template<Scalar T>
Point<T> Hexagon<T>::center() const {
    return center_;
}

template<Scalar T>
double Hexagon<T>::area() const {
    if constexpr (std::is_integral_v<T>) {
        double side = static_cast<double>(radius);
        return (3 * std::sqrt(3) * side * side) / 2;
    } else {
        T side = radius;
        return static_cast<double>((3 * std::sqrt(3) * side * side) / 2);
    }
}

template<Scalar T>
void Hexagon<T>::print(std::ostream& os) const {
    os << "Hexagon: Center" << center_ << ", Radius: " << radius << ", Vertices: ";
    for (int i = 0; i < 6; ++i) {
        os << *vertices[i];
        if (i < 5) os << ", ";
    }
}

template<Scalar T>
void Hexagon<T>::read(std::istream& is) {
    T x, y, r;
    if (!(is >> x >> y >> r)) {
        throw std::runtime_error("Invalid input for hexagon.");
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
bool Hexagon<T>::operator==(const Figure<T>& other) const {
    const Hexagon* h = dynamic_cast<const Hexagon*>(&other);
    if (!h) return false;
    return center_ == h->center_ && radius == h->radius;
}

template<Scalar T>
std::shared_ptr<Figure<T>> Hexagon<T>::clone() const {
    return std::make_shared<Hexagon>(*this);
}

template class Hexagon<int>;
template class Hexagon<float>;
template class Hexagon<double>;
template class Hexagon<long double>;