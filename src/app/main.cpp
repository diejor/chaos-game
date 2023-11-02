#include <iostream>

#include "input.hpp"
#include "output.hpp"

#include "grid.hpp"
#include "point.hpp"
#include "experiments.hpp"
#include "ppm_stream.hpp"
#include "rgb_mapping.hpp"

using namespace std;
using namespace grid;
using namespace rgb_mapping;

int main() {
    Point p1 = Point(0, 99);
    Point p2 = Point(199, 0);
    Point p3 = Point(199, 199);
    vector<Point> starting_points = {p1, p2, p3};

    Grid grid = Grid(200, 200);
    experiments::run(starting_points, grid, 100000);

    vector<vector<RGB>> rgb_grid = grid_to_rgb(grid, existential);
    ppm_stream::output_experiment(rgb_grid);

    return 0;
}
