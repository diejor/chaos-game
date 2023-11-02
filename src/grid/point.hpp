#ifndef POINT_HPP
#define POINT_HPP

#include <string>

namespace grid {
    struct Point {
        int row;
        int col;

        Point add(const Point& other) const;
        Point subtract(const Point& other) const;

        Point displacement(const Point& other) const;
        Point dsplcmt_to_middle(const Point& other) const;
        Point middle(const Point& other) const;

        std::string to_string() const;
    };
}  // namespace grid

#endif // !POINT_HPP
