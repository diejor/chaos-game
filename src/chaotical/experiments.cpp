
#include <vector>

#include "experiments.hpp"

using namespace std;
using namespace grid;

namespace experiments {
    
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
}

