
#include <cmath>
#include <complex>

// implementation
#include "rgb_mapping.hpp"

// grid dependencies
#include "chaos.hpp"
#include "grid.hpp"

#include "output.hpp"

using namespace std;
using namespace grid;

namespace rgb_mapping {
    namespace debug {
        void print_rgb(string msg, RGB rgb) {
            output::debug(msg + rgb.to_string());
        }
    }

    /*
     * Converts a RGB color to a polar coordinate.
     * The radius is the maximum value of the RGB color.
     * The angle is the hue angle of the RGB color.
     * 
     * At the end I didn't use this and wheel_to_rgb functions.
     */
    tuple<double, int> polar_from(RGB color) {
        // Normalize the RGB values to the range [0, 1]
        double dMAX_COLOR = MAX_COLOR;
        double r = color.r / dMAX_COLOR;
        double g = color.g / dMAX_COLOR;
        double b = color.b / dMAX_COLOR;

        // Calculate the hue angle using the atan2 function
        double angle = atan2(sqrt(3) * (g - b), 2 * r - g - b);

        // Convert angle from radians to degrees and normalize it to the range [0, 360)
        angle = fmod(angle * (180 / M_PI) + 360, 360); // double is truncated to int

        // not sure if maximum rgb value would be the radius
        // specially if the color is white based and not black based
        double radius = fmax(fmax(r, g), b);

        return make_tuple(radius, angle);
    }

    // radius is between 0 and 1
    RGB color_from_wheel(double radius, int degree) {
        RGB rgb;
        double red, green, blue;
        double angle = degree * M_PI / 180;

        red = (sin(angle) + 1) / 2;
        green = (sin(angle + M_PI / 3) + 1) / 2;
        blue = (sin(angle + 2 * M_PI / 3) + 1) / 2;

        red *= radius * MAX_COLOR;
        green *= radius * MAX_COLOR;
        blue *= radius * MAX_COLOR;

        // Clamping the values to the range [0, 255]
        rgb.r = fmax(0, fmin(MAX_COLOR, red));
        rgb.g = fmax(0, fmin(MAX_COLOR, green));
        rgb.b = fmax(0, fmin(MAX_COLOR, blue));

        return rgb;
    }

    /*
     * Converts a grid of chaos to a grid of rgb using the provided mapping function.
     * For more information about the mapping function, see the rgb_mapping.hpp file.
     * Chaos struct is just a container of information about the chaos in a point, for more 
     * information about it, see chaos.hpp in grid module.
     */
    vector<vector<RGB>> grid_to_rgb(RGBMappingFunc chaos_to_rgb, Experiment const& experiment) {
        vector<vector<RGB>> rgb_grid;
        Grid const& chaos_grid = experiment.grid;
        int iterations = experiment.iterations;

        for (int row = 0; row < chaos_grid.get_rows(); row++) {
            vector<RGB> rgb_row;
            for (int col = 0; col < chaos_grid.get_cols(); col++) {
                Point p(row, col);
                RGB rgb = chaos_to_rgb(chaos_grid.grid_point_info(p), experiment);
                rgb_row.push_back(rgb);
            }
            rgb_grid.push_back(rgb_row);
        }

        return rgb_grid;
    }

    /*
     * Half negative sigmoid function, used to scale the rgb values between the
     * transition from one color to another when could be arbitrarily large or small
     * (-infinity, +infinity), but trying to scale the domain to fit the standard deviation.
     */
    double half_negative_sigmoid(double x, double standard_deviation) {
        return (2 / (1 + exp(-3 * x / standard_deviation))) - 1;
    }

    /*
     * Linear transition from -1 to 1 centered at 0, used to scale the rgb values
     * between the transition from one color to another. Similar to the half_negative_sigmoid,
     * but when range of x is known to be [0, max_value]
     */
    double linear(double x, int max_value) {
        int half = max_value / 2;
        return (x - half) / half;
    }

    /*
     * Creates a neat gradient between two colors.
     */
    RGB linear_transition(RGB from, RGB to, double x, int max_value) {
        RGB rgb;
        double scale = linear(x, max_value);
        if (scale < 0) {
            scale = -scale;
            rgb = from;
        } else
         rgb = to;

        rgb.r *= scale;
        rgb.g *= scale;
        rgb.b *= scale;

        return rgb;
    }

    /*
     * Similar to linear_transition, but the range of x is unknown.
     */
    RGB nonlinear_transition(RGB from, RGB to, double x, double standard_deviation) {
        RGB rgb;
        double scale = half_negative_sigmoid(x, standard_deviation);
        if (scale < 0) {
            scale = -scale;
            rgb = from;
        } else
         rgb = to;

        rgb.r *= scale;
        rgb.g *= scale;
        rgb.b *= scale;

        return rgb;
    }

    RGB complementary(RGB color) {
        RGB rgb;
        rgb.r = MAX_COLOR - color.r;
        rgb.g = MAX_COLOR - color.g;
        rgb.b = MAX_COLOR - color.b;
        return rgb;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~ RGB Mappings of Experiments ~~~~~~~~~~~~~~~~~~~~~~~~

    /*
     * Black and white drawing of the polygon, used by simple_polygon experiment.
     */
    RGB existential(Chaos const& info, Experiment const& experiment) {
        RGB rgb = WHITE;
        if (info.collisions.empty()) {
            return complementary(rgb);
        }
        return rgb;
    }

    /*
     * Time taken to reach a point, used by time_taken_to_reach_point experiment.
     */
    RGB time_taken(Chaos const& info, Experiment const& experiment) {
        RGB from = RED;
        RGB to = BLUE;

        // unwarp experiment
        int iterations = experiment.iterations;

        if (info.collisions.empty()) {
            return BLACK;
        }
        int first_collision = info.collisions[0].iteration;
        return linear_transition(from, to, first_collision, iterations);
    }

    /*
     * Coloring based on the distance to the center of the polygon, used by color_distance_to_center experiment.
     */
    RGB distance_to_center(Chaos const& info, Experiment const& experiment) {
        RGB from = RED;
        RGB to = BLUE;

        // unwarp experiment
        int iterations = experiment.iterations;
        Point center = experiment.polygon.center;

        if (info.collisions.empty()) {
            return BLACK;
        }

        double max_dist = experiment.opt;
        double dist = info.grid_point.distance(center);

        return linear_transition(from, to, dist, max_dist);
    }

    /*
     * Traces the whole path the chaos game took and colors based on the accumulated distance, used by tracing_path experiment.
     */
    RGB accumulated_distance(Chaos const& info, Experiment const& experiment) {
        RGB from = RED;
        RGB to = BLUE;

        // unwarp experiment
        int iterations = experiment.iterations;

        if (info.collisions.empty()) {
            return BLACK;
        }

        double max_dist = experiment.opt;
        double dist = info.accumulation;

        return linear_transition(from, to, dist, max_dist);
    }

}  // namespace rgb_mapping
