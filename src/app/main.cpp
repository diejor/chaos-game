/*
 * Chaos Game 
 * file: main.cpp
 * author: Diego R.R. 
 * started: 10/1/2023
 * course: CS2337.501
 *
 * Purpose: To visualize the beauty of chaotical systems.
 *
 * Changelog:
 *  - 10/1/2023 - imported utils files, added grid module
 *  - 10/2/2023 - designed chaotical module with experiments abstraction, rgb_mapping 
 *                  functions and structs associated
 *  - 10/3/2023 - implemented chaotical module, editing the program flow of the user
 *                interface, added input module.
 *  - 10/4/2023 - added more experiments, and robustnest to the program.
 *
 * Notes:
 *  - Documentation for each experiment is detailed in the experiments.cpp file.
 *
 *  - I decided to pass the experiment information with Experiment struct defined in experiment.hpp. 
 *    This struct is passed by reference basically throughout the whole program. 
 *    The reason to do this instead of creating a class and define all the program 
 *    inside this class was to divide the program into modules rather than innerstructs
 *
 *  - The structure of the project was flattened for submission
 *    but it follows the following tree:
 *  ├── src
 *       ├── app
 *       │   └── main.cpp
 *       ├── chaotical
 *       │   ├── experiments.cpp
 *       │   ├── experiments.hpp
 *       │   ├── ppm_stream.cpp
 *       │   ├── ppm_stream.hpp
 *       │   ├── rgb_mapping.cpp
 *       │   └── rgb_mapping.hpp
 *       ├── grid
 *       │   ├── chaos.cpp
 *       │   ├── chaos.hpp
 *       │   ├── grid.cpp
 *       │   ├── grid.hpp
 *       │   ├── point.cpp
 *       │   ├── point.hpp
 *       │   ├── polygon.cpp
 *       │   └── polygon.hpp
 *       └── utils
 *           ├── global.hpp
 *           ├── input.hpp
 *           └── output.hpp
 *      One important remark from this tree is that all the include are relative to this tree
 *      but I added comments in top of each inclusion to make this clear.
 */

// utils imports
#include "global.hpp"
#include "input.hpp"

// experiment imports
#include "experiments.hpp"

// grid imports
#include "grid.hpp"
#include "polygon.hpp"

using namespace experiments;
using namespace grid;

// helper function of decide experiment to retrieve necessary information from user
Experiment ask_info() {
    // ask for grid
    int len = input::integer("Enter size length: ");
    Grid grid = Grid(len, len);

    // ask for polygon
    int sides = input::integer("Enter number of sides: ");
    Point center = Point(len / 2 - 1, len / 2 - 1);  // note that points are 0-indexed
    Polygon polygon = Polygon(center, sides, len / 2 - 1);

    // ask for data to run experiment
    int iterations = input::integer("Enter iterations: ");
    int percentage = input::integer("What percentage of distance?  (100% based): ");
    bool repeat = input::yes_or_no("Repeat collisions?");
    return Experiment{grid, polygon, iterations, percentage, repeat};
}

// control flow function to decide which experiment to run
void decide_experiment() {
    vector<string> experiments = {
        "Simple Polygon",
        "Time taken to reach a point",
        "Distance to center",
        "Tracing path",
    };
    int experiment = input::select("Choose an experiment:", experiments);

    Experiment experiment_info = ask_info();
    switch (experiment) {
        case 1:
            experiments::simple_polygon(experiment_info);
            break;
        case 2:
            experiments::time_taken_to_reach_point(experiment_info);
            break;
        case 3:
            experiments::color_distance_to_center(experiment_info);
            break;
        case 4:
            experiments::tracing_path(experiment_info);
            break;
        default:
            break;
    }
}

int main() {
    do {
        decide_experiment();
    } while (input::yes_or_no("Another experiment?"));
    return 0;
}
