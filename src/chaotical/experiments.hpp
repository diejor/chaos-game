#ifndef EXPERIMENTS_HPP
#define EXPERIMENTS_HPP

#include <vector>

#include "grid.hpp"

using namespace std;
using namespace grid;

namespace experiments {
    void run(vector<grid::Point> starting_points, Grid& grid, int iterations);
}

#endif // ! EXPERIMENTS_HPP