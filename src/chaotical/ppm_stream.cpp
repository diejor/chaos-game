
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// Utils
#include "input.hpp"
#include "output.hpp"

#include "rgb_mapping.hpp"
#include "ppm_stream.hpp"
#include "grid.hpp"

using namespace std;
using namespace grid;
using namespace rgb_mapping;


namespace ppm_stream {
    const int MAX_COLOR = 255;

    void write_comment(ofstream &out_file, const string &comment) {
        // Commented out because it's not necessary for the ppm file to be valid.
        // and some image viewers dont support comments.
        // out_file << "# " << comment << endl;
    }

    void write_magic_num(ofstream &out_file, const string &magic_num) {
        write_comment(out_file, "magic number for PPM file");
        out_file << magic_num << endl;
    }

    void write_dim(ofstream &out_file, int rows, int cols) {
        write_comment(out_file, "dimensions of the image");
        out_file << rows << "  " << cols << endl;
    }

    void write_max_color(ofstream &out_file, int max_color) {
        write_comment(out_file, "maximum color value");
        out_file << max_color << endl;
    }

    /*
     * Helper function to build the ofstream ppm file, where the returned ofstream object is then used to write the rgb values to output the ppm file.
     */ 
    ofstream create_ppm(const vector<vector<RGB>>& rgb_grid) {
        output::inform("Creating ppm file ...");
        string ppm_file_name = input::get_file_name_validated(); 
        ofstream ppm_file(ppm_file_name);

        output::inform("Writing to file " + ppm_file_name + " ...");
        write_magic_num(ppm_file, "P3");
        write_dim(ppm_file, rgb_grid.size(), rgb_grid[0].size());
        write_max_color(ppm_file, MAX_COLOR);
        return ppm_file;
    }

    void output_experiment(const vector<vector<RGB>>& rgb_grid) {
        ofstream ppm_file = create_ppm(rgb_grid);
        for (int row = 0; row < rgb_grid.size(); row++) {
            for (int col = 0; col < rgb_grid[row].size(); col++) {
                ppm_file << rgb_grid[row][col].to_string() << " ";
            }
            ppm_file << endl;
        }
        ppm_file.close();
        output::inform("Done!");
    }
}
