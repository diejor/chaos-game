#ifndef GRID_HPP
#define GRID_HPP

#include <tuple>
#include <vector>
#include <string>

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

        const Chaos& grid_point_info(const Point& p) const;
        void add_collision(const Point& p, Point displacement, int iterations);

        Point random_point() const;

        void print(ostream& os) const;
    };
}  // namespace grid

#endif  // GRID_HPP
