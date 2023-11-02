
#ifndef DEBUG
#define DEBUG

#include <iostream>
#include <vector>

#include "point.hpp"

using namespace std;

/*
 *  Used for each pixel in the 'Grid' class to store data.
 */
namespace chaos {
    struct Chaos {
        Point grid_point;

        // store all the collisions, the first component is the displacement from the original point
        // the second component is the current number of iterations
        vector<tuple<Point, int>> collisions;

        Chaos(int row, int col) {
            grid_point = Point(row, col);
        }
    };
}

#endif // !DEBUG
