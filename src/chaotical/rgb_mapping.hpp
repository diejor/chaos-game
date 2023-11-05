#ifndef RGB_MAPPING_HPP
#define RGB_MAPPING_HPP

// experiment imports
#include "experiments.hpp"

// grid imports
#include "chaos.hpp"
#include "grid.hpp"

using namespace std;
using namespace grid;
using namespace experiments;

namespace rgb_mapping {
    const int MAX_COLOR = 255;

    struct RGB {
        int r;
        int g;
        int b;

        string to_string() const {
            return std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b);
        }
    };

    // Define some common colors
    const RGB BLACK = {0, 0, 0};
    const RGB WHITE = {MAX_COLOR, MAX_COLOR, MAX_COLOR};
    const RGB RED = {MAX_COLOR, 0, 0};
    const RGB GREEN = {0, MAX_COLOR, 0};
    const RGB BLUE = {0, 0, MAX_COLOR};
    const RGB YELLOW = {MAX_COLOR, MAX_COLOR, 0};
    const RGB CYAN = {0, MAX_COLOR, MAX_COLOR};
    const RGB MAGENTA = {MAX_COLOR, 0, MAX_COLOR};

    // Not sure how this works but in c++ but I just inteded to have a wrapper function
    // for the rgb_mapping functions.

    /*
     * This is the function used by grid_to_rgb to map the chaos information to a RGB color.
     */
    using RGBMappingFunc = RGB (*)(const Chaos&, Experiment const& experiment);

    vector<vector<RGB>> grid_to_rgb(RGBMappingFunc chaos_to_rgb, Experiment const& experiment);

    //~~~~~~~~~~~~~~~~~~~~~~~
    // RGB mapping functions

    RGB existential(const Chaos& info, Experiment const& experiment);
    RGB time_taken(const Chaos& info, Experiment const& experiment);
    RGB distance_to_center(const Chaos& info, Experiment const& experiment);
    RGB accumulated_distance(const Chaos& info, Experiment const& experiment);

}  // namespace rgb_mapping

#endif  // ! RGB_MAPPING_HPP
