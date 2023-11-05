/**
 * Chaos Game Experiments
 * file: experiments.cpp
 * author: Diego R.R.
 * last updated: 11/1/2023
 * course: CS2337.501
 *
 * Notes:
 * - Logic of the chaos game is implemented with run(), run_no_repeat(), and run_tracing().
 *
 * - The output of the experiments is handled by ppm_stream module, to get more details go down
 *   the file and read the remarks for the experiments section or go to ppm_stream module.
 */

// standard imports
#include <cmath>
#include <filesystem>
#include <vector>

// implementation
#include "experiments.hpp"

// utils imports
#include "output.hpp"

// experiment imports
#include "ppm_stream.hpp"

// grid imports
#include "grid.hpp"
#include "point.hpp"

using namespace std;
using namespace grid;

namespace experiments {
    namespace debug {
        void experiment_before(Experiment const& experiment) {
            if (global::debug_flags::EXPERIMENT_BEFORE) {
                output::debug("Experiment before:");
                output::debug("\t grid:");
                experiment.grid.print(cout);
                output::debug("\t iterations: " + to_string(experiment.iterations));
                output::debug("\t ths: " + to_string(experiment.percentage));
                output::debug("\t repeat: " + to_string(experiment.repeat));
            }
        }

        void experiment_after(Experiment const& experiment) {
            if (global::debug_flags::EXPERIMENT_AFTER) {
                output::debug("Experiment after:");
                output::debug("\t grid:");
                experiment.grid.print(cout);
                output::debug("\t iterations: " + to_string(experiment.iterations));
                output::debug("\t ths: " + to_string(experiment.percentage));
                output::debug("\t repeat: " + to_string(experiment.repeat));
            }
        }
    }  // namespace debug

    Point choose_random(vector<Point> points) {
        int index = rand() % points.size();
        return points[index];
    }

    /*
     * Performs the algorithm specified by the professor to generate the chaos information
     * for each point in the grid, that is lated used by the RGBMappingFunc to generate
     * the color for each point.
     */
    void run(Experiment& experiment) {
        // unwrap experiment
        vector<Point>& starting_points = experiment.polygon.vertices;
        Grid& grid = experiment.grid;
        int& iterations = experiment.iterations;
        int& percentage = experiment.percentage;
        debug::experiment_before(experiment);

        // add starting points to the grid
        // Point(0,0) is the displacement which is 0 for starting starting_points
        // collided points will not have 0 displacement
        for (Point p : starting_points) {
            // add(point, displacement to get to point, which iteration it was added)
            grid.add_collision(p, Point(0, 0), 0);
        }

        // algorithm specified by professor
        Point cur_point = grid.random_point();
        for (int i = 0; i < iterations; i++) {
            Point vertex = choose_random(starting_points);
            Point dsplcmt_by = cur_point.displacement_by(vertex, percentage);
            Point collision_point = cur_point.add(dsplcmt_by);
            grid.add_collision(collision_point, dsplcmt_by, i);
            cur_point = collision_point;
        }
        debug::experiment_after(experiment);
    }

    /*
     * Same as run() but does not repeat the vertex chosen in previous iteration.
     */
    void run_no_repeat(Experiment& experiment) {
        // unwrap experiment
        vector<Point>& starting_points = experiment.polygon.vertices;
        Grid& grid = experiment.grid;
        int& iterations = experiment.iterations;
        int& percentage = experiment.percentage;
        debug::experiment_before(experiment);

        for (Point p : starting_points) {
            // add(point, displacement to get to point, which iteration it was added)
            grid.add_collision(p, Point(0, 0), 0);
        }

        // algorithm specified by professor
        Point cur_point = grid.random_point();
        Point prev_vertex;
        for (int i = 0; i < iterations; i++) {
            Point vertex = choose_random(starting_points);
            if (vertex == prev_vertex) {
                i--;
                continue;
            }
            prev_vertex = vertex;
            Point dsplcmt_by = cur_point.displacement_by(vertex, percentage);
            Point p = cur_point.add(dsplcmt_by);
            grid.add_collision(p, dsplcmt_by, i);
            cur_point = p;
        }
        debug::experiment_after(experiment);
    }

    /*
     * Used to generate the points between two points using Bresenham's line algorithm.
     */
    void run_tracing(Experiment& experiment) {
        // unwrap experiment
        vector<Point>& starting_points = experiment.polygon.vertices;
        Grid& grid = experiment.grid;
        int& iterations = experiment.iterations;
        int& percentage = experiment.percentage;
        debug::experiment_before(experiment);

        // add starting points to the grid
        for (Point p : starting_points) {
            grid.add_collision(p, Point(0, 0), 0);
        }

        Point cur_point = grid.random_point();
        for (int i = 0; i < iterations; i++) {
            Point vertex = choose_random(starting_points);
            Point dsplcmt_by = cur_point.displacement_by(vertex, percentage);
            Point collision_point = cur_point.add(dsplcmt_by);

            // Use Bresenham's algorithm to find all points on the line
            // from cur_point to collision_point
            vector<Point> linePoints = bresenham_line(cur_point, collision_point);

            // Record the line points in the grid starting from cur_point to collision_point
            for (const Point& linePoint : linePoints) {
                unsigned int distance =
                    linePoint.distance(cur_point);  // truncate to int in purpose
                distance += grid.grid_point_info(cur_point).accumulation;  // accumulate distance
                experiment.opt = distance;
                Point displacement = cur_point.displacement(linePoint);
                grid.add_collision(linePoint, displacement, i, distance);
            }

            // Update current point to the last collision point
            cur_point = collision_point;
        }
        debug::experiment_after(experiment);
    }

    /*
     * Returns the maximum value possible in vector so RGBMappingFunc can create a gradient of the color.
     */
    double max(vector<double> values) {
        double max = values[0];
        for (double d : values) {
            if (d > max) {
                max = d;
            }
        }
        return max;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~ Possible experiments to run ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //
    // Important remark is that files are named based on the polygon used, followed
    // by the wether it repeats vertices or not, experiment used, the percentage used
    // to calculate the displacement, and the number of iterations. Some information
    // is excluded if it is not relevant to the experiment.
    //
    // ex: pentagon-norepeat-dist-60%-100k.ppm
    // Here, the polygon used is a pentagon, it does not repeat vertices, the experiment
    // used is distance to center, the percentage used to calculate the displacement is 60%,
    // and the number of iterations is 100k.

    /*
     * Colors based on wether the point has collided or not, using the existential rgb_mapping function.
     * This is the simplest experiment.
     */
    void simple_polygon(Experiment experiment) {
        output::inform("Running simple polygon experiment");
        if (experiment.repeat) {
            run(experiment);
        } else {
            run_no_repeat(experiment);
        }

        // existential rgb_mapping function is used to generate the color for each point
        vector<vector<RGB>> rgb_grid = grid_to_rgb(existential, experiment);
        ppm_stream::output_experiment(rgb_grid);
    }

    /*
     * Colors based on the iterations it took to reach a point.
     */
    void time_taken_to_reach_point(Experiment experiment) {
        output::inform("Running time taken to reach a point experiment");
        if (experiment.repeat) {
            run(experiment);
        } else {
            run_no_repeat(experiment);
        }

        vector<vector<RGB>> rgb_grid = grid_to_rgb(time_taken, experiment);
        ppm_stream::output_experiment(rgb_grid);
    }

    /*
     * Colors based on the distance to the center of the polygon.
     */
    void color_distance_to_center(Experiment experiment) {
        output::inform("Running distance to center experiment");
        if (experiment.repeat) {
            run(experiment);
        } else {
            run_no_repeat(experiment);
        }

        vector<double> distances_to_center;
        for (Point p : experiment.grid.points()) {
            // ignore points that have not collided
            Chaos chaos = experiment.grid.grid_point_info(p);
            if (chaos.collisions.empty())
                continue;

            Point center = experiment.polygon.center;
            double dist = p.distance(center);
            distances_to_center.push_back(dist);
        }

        experiment.opt = max(distances_to_center);

        vector<vector<RGB>> rgb_grid = grid_to_rgb(distance_to_center, experiment);
        ppm_stream::output_experiment(rgb_grid);
    }

    /*
     * Traces the whole path the chaos game took and colors based on the accumulated distance.
     */
    void tracing_path(Experiment experiment) {
        output::inform("Running trace path experiment");
        run_tracing(experiment);

        vector<vector<RGB>> rgb_grid = grid_to_rgb(accumulated_distance, experiment);
        ppm_stream::output_experiment(rgb_grid);
    }
}  // namespace experiments
