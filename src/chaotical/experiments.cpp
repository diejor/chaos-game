
#include <vector>

#include "experiments.hpp"
#include "grid.hpp"
#include "output.hpp"
#include "point.hpp"
#include "ppm_stream.hpp"

using namespace std;
using namespace grid;

namespace experiments {
    const int WIDTH = 1000;
    const int HEIGHT = 1000;
    const int ITERATIONS = 100000;
    
    Point choose_random(vector<Point> points) {
        int index = rand() % points.size();
        return points[index];
    }

    void run(vector<grid::Point> starting_points, Grid& grid, int iterations) {
        for (Point p : starting_points) {
            grid.add_collision(p, Point(0,0), 0);
        }

        Point curPoint = grid.random_point();
        for (int i = 0; i < iterations; i++) {
            Point nextPoint = choose_random(starting_points);
            Point dsplcmt_to_mid = curPoint.dsplcmt_to_middle(nextPoint);
            Point middle = curPoint.add(dsplcmt_to_mid);
            grid.add_collision(middle, dsplcmt_to_mid, i);
            curPoint = middle;
        }
    }

    // simple shapes and white/black coloring
    void simple_polygon(int sides) {
        output::inform("Running simple polygon experiment");
        Grid grid = Grid(WIDTH, HEIGHT);
        vector<Point> starting_points = polygon(Point(HEIGHT/2-1, WIDTH/2-1), sides, WIDTH/2-1);

        experiments::run(starting_points, grid, ITERATIONS);

        vector<vector<RGB>> rgb_grid = grid_to_rgb(grid, existential);
        ppm_stream::output_experiment(rgb_grid);
    }
}

