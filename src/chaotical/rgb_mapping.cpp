
#include <cmath>

// implementation
#include "rgb_mapping.hpp"

// grid dependencies
#include "grid.hpp"
#include "chaos.hpp"

using namespace std;
using namespace grid;

namespace rgb_mapping {

    double sigmoid(double x, double v_shift, double v_stretch, double h_stretch) {
        return (v_stretch / (1 + exp(h_stretch * x) / v_stretch)) + v_shift;
    }

    RGB existential(const Chaos& info) {
        RGB rgb;
        if (info.collisions.empty()) {
            rgb.r = 0;
            rgb.g = 0;
            rgb.b = 0;
        } else {
            rgb.r = 255;
            rgb.g = 255;
            rgb.b = 255;
        }
        return rgb;
    }

    // Define the RGB mapping function
    // Function to convert a Grid of Chaos to a Grid of RGB using the provided mapping function
    vector<vector<RGB>> grid_to_rgb(const Grid& chaos_grid, RGBMappingFunc chaos_to_rgb) {
        vector<vector<RGB>> rgb_grid;

        for (int row = 0; row < chaos_grid.get_rows(); row++) {
            vector<RGB> rgb_row;
            for (int col = 0; col < chaos_grid.get_cols(); col++) {
                Point p(row, col);
                RGB rgb = chaos_to_rgb(chaos_grid.grid_point_info(p));
                rgb_row.push_back(rgb);
            }
            rgb_grid.push_back(rgb_row);
        }

        return rgb_grid;
    }

}  // namespace rgb_mapping
