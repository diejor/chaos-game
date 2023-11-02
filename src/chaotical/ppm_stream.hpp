
#ifndef PPM_STREAM_HPP
#define PPM_STREAM_HPP

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "grid.hpp"
#include "rgb_mapping.hpp"

using namespace std;
using namespace rgb_mapping;

namespace ppm_stream {

    void write_rgb(ofstream& out_file, int r, int g, int b);
    void write_comment(ofstream& out_file, const string& comment);

    void write_magic_num(ofstream& out_file, const string& magic_num);

    void write_dim(ofstream& out_file, int rows, int cols);

    void write_max_color(ofstream& out_file, int max_color);

    ofstream create_ppm(const vector<vector<RGB>>& rgb_grid);

    void output_experiment(const vector<vector<RGB>>& rgb_grid);
}  // namespace ppm_stream

#endif  // !PPM_STREAM_HPP
