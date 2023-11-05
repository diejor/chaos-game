/*
 * Chaos Game
 * file: experiments.hpp
 * author: Diego R.R.
 * started: 10/1/2023
 * course: CS2337.501
 *
 * Purpose: compilates the experiments that can be run with the chaos game.
 *
 * Changelog:
 *  - 10/2/2023 - Initial creation of Experiment struct and function declarations.
 *  - 10/4/2023 - + Added documentation struct with an additional 
 *                +'opt' parameter for uses such as accumalted distance or max distance.
 *
 * Notes:
 *  - The output of the experiments is handled by ppm_stream module.
 *
 *  - For more details of how chaos game logic works, go to experiments.cpp and check run() and run_no_repeat().
 *
 *  - RGB mappings are not defined here but they are central to the experiments
 *  since they are the ones that visually define the experiment. Nevertheless I decided
 *  to separate them in rgb_mapping.hpp, so the purpose of this module is to gather the 
 *  experiments in a comprehensive way.
 *  
 */

#ifndef EXPERIMENTS_HPP
#define EXPERIMENTS_HPP

#include <vector>

// grid imports
#include "grid.hpp"
#include "polygon.hpp"

using namespace std;
using namespace grid;

namespace experiments {
    // This is just the data required to run an experiment, the run() function
    // creates the grid with the chaos information of each point. Then, each type of
    // experiment provides a RGBMappingFunc to map the chaos information to a color
    // that is later used by ppm_stream to output the experiment.
    //

    /*
     * Data required to run an experiment.
     */
    struct Experiment {
        Grid grid;
        Polygon polygon;
        int iterations;
        int percentage;
        bool repeat;
        /*
         * This is used for experiments that require an additional parameter.
         * Nevertheless, experiments such as simple_polygon don't use it.
         */
        double opt;
    };

    /*
     *  Black and white drawing of the polygon. 
     */
    void simple_polygon(Experiment experiment);

    /*
     * Coloring based on the iterations it took to reach a point.
     */
    void time_taken_to_reach_point(Experiment experiment);

    /*
     * Coloring based on the distance to the center of the polygon.
     */
    void color_distance_to_center(Experiment experiment);

    /*
     * Traces the whole path the chaos game took and colors based on the accumulated distance.
     */
    void tracing_path(Experiment experiment);
}  // namespace experiments

#endif  // ! EXPERIMENTS_HPP
