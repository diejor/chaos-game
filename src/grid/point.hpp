#ifndef POINT_HPP
#define POINT_HPP

#include <string>
#include <vector>

using namespace std;

namespace grid {
    struct Point {
        int row;
        int col;

        Point add(const Point& other) const;
        Point subtract(const Point& other) const;

        Point displacement(const Point& other) const;
        Point displacement_by(const Point& other, int ths) const;

        Point rotate(int degrees) const;
        double distance(const Point& other) const;

        bool operator==(const Point& other) const;

        std::string to_string() const;
    };

    vector<Point> polygon(const Point& center, int num_rotations, int radius);
}  // namespace grid

#endif  // !POINT_HPP
