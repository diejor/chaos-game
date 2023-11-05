#ifndef CHAOS_HPP
#define CHAOS_HPP

#include <tuple>
#include <vector>

#include "point.hpp"

using namespace std;

namespace grid {
    struct Collision {
        Point point;
        int iteration;

        Collision() {
            point = Point();
            iteration = 0;
        }

        Collision(Point point, int iteration) {
            this->point = point;
            this->iteration = iteration;
        }
    };

    /*
     *  Stores information of each point in the 'Grid'.
     */
    struct Chaos {
        Point grid_point;

        // the first component is the displacement from the original point
        // the second component is the current number of iterations
        vector<Collision> collisions;

        unsigned int accumulation;

        Chaos() {
            grid_point = Point();
            accumulation = 0;
        }

        Chaos(Point grid_point) {
            this->grid_point = grid_point;
            accumulation = 0;
        }
    };

}  // namespace grid

#endif  // !CHAOS_HPP
