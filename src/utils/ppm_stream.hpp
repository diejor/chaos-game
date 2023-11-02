#ifndef WORD_SEARCH_PPM_STREAM_H
#define WORD_SEARCH_PPM_STREAM_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "global.hpp"
#include "input.hpp"

using namespace std;
using namespace global;

namespace ppm_stream {
    const int MAX_COLOR = 255;

    namespace debug {}  // namespace debug

    void write_rgb(ofstream& out_file, int r, int g, int b) {
        out_file << setw(3) << setfill('0') << r << " ";
        out_file << setw(3) << setfill('0') << g << " ";
        out_file << setw(3) << setfill('0') << b << "  ";
    }

    void write_comment(ofstream& out_file, const string& comment) {
        out_file << "# " << comment << endl;
    }

    void write_magic_num(ofstream& out_file, const string& magic_num) {
        write_comment(out_file, "magic number for PPM file");
        out_file << magic_num << endl;
    }

    void write_dim(ofstream& out_file, int rows, int cols) {
        write_comment(out_file, "dimensions of the image");
        out_file << rows << "  " << cols << endl;
    }

    void write_max_color(ofstream& out_file, int max_color) {
        write_comment(out_file, "maximum color value");
        out_file << max_color << endl;
    }

    /*
     * Complementary function to build the ofstream ppm file, where the returned ofstream object is then used to write the rgb values to output the ppm file.
     */
    ofstream create_ppm(const vector<vector<int>>& grid) {
        output::inform("Creating ppm file ...");
        string ppm_file_name = input::get_file_name_validated(); 
        ofstream ppm_file(ppm_file_name);
        output::inform("Writing to file " + ppm_file_name + " ...");

        write_magic_num(ppm_file, "P3");
        write_dim(ppm_file, grid.size(), grid[0].size());
        write_max_color(ppm_file, MAX_COLOR);
        return ppm_file;
    }
}  // namespace ppm_stream

#endif  // WORD_SEARCH_PPM_STREAM_H
