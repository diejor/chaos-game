#ifndef GRID_HPP
#define GRID_HPP

#include <string>
#include <tuple>
#include <vector>

#include "chaos.hpp"
#include "point.hpp"

using namespace std;

namespace grid {
    class Grid {
       private:
        int rows;
        int cols;
        vector<vector<Chaos>> grid;

       public:
        // Constructor
        Grid(int rows, int cols);

        // Dimensions
        int get_rows() const;
        int get_cols() const;

        vector<Point> points() const;

        const Chaos& grid_point_info(const Point& p) const;
        void add_collision(const Point& p, Point displacement, int iterations,
                           unsigned int accumulate = 0);

        Point random_point() const;
        bool has_collision(const Point& p) const;

        void print(ostream& os) const;
    };

    // used by run_tracing to collide all points between the current and collision point
    vector<Point> bresenham_line(const Point& start, const Point& end);
}  // namespace grid

#endif  // GRID_HPP
