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
    };

}  // namespace grid

#endif  // !CHAOS_HPP
