#ifndef RGB_MAPPING_HPP
#define RGB_MAPPING_HPP

#include "chaos.hpp"
#include "grid.hpp"

using namespace std;
using namespace grid;

namespace rgb_mapping {
    struct RGB {
        int r;
        int g;
        int b;

        string to_string() const {
            return std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b);
        }
    };

    double sigmoid(double x, double v_shift, double v_stretch, double h_stretch);
    RGB existential(const Chaos& info);

    // Define the function type for the RGB mapping function
    using RGBMappingFunc = RGB (*)(const Chaos&);

    vector<vector<RGB>> grid_to_rgb(const Grid& chaos_grid, RGBMappingFunc chaos_to_rgb);
    
}  // namespace rgb_mapping

#endif  // ! RGB_MAPPING_HPP
