#ifndef POINT_HPP
#define POINT_HPP

#include <string>
#include <vector>

using namespace std;

namespace grid {
    struct Point {
        int row;
        int col;

        Point() {
            row = 0;
            col = 0;
        }

        Point(int row, int col) {
            this->row = row;
            this->col = col;
        }


        Point(Point const& other) {
            row = other.row;
            col = other.col;
        }

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
