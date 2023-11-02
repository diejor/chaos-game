#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

using namespace std;

#include "point.hpp"
#include "chaos.hpp"

class Grid {
   private:
    int rows; 
    int cols;
    vector<vector<chaos::Chaos>> grid;

   public:
    // Constructor
    Grid(int rows, int cols);

    // Dimensions
    int get_rows() const;
    int get_cols() const;

    chaos::Chaos& grid_point_info(const Point& p);
    void add_collision(const Point& p, Point displacement, int iterations);
};

#endif  // GRID_HPP
