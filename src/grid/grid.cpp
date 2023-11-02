#include "grid.hpp"
#include "chaos.hpp"
#include "output.hpp"

// Constructor
Grid::Grid(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    
    for (int row = 0; row < rows; row++) {
        vector<chaos::Chaos> row_vector;
        for (int col = 0; col < cols; col++) {
            chaos::Chaos chaos_in_point = chaos::Chaos(row, col);
            row_vector.push_back(chaos_in_point);
        }
        grid.push_back(row_vector);
    }
}

// Accessors for rows and cols
int Grid::get_rows() const {
    return rows;
}

int Grid::get_cols() const {
    return cols;
}

chaos::Chaos& Grid::grid_point_info(const Point& p) {
    return grid[p.row][p.col];
}

void Grid::add_collision(const Point& p, Point displacement, int iterations) {
    chaos::Chaos chaos_in_point = grid[p.row][p.col];
    tuple<Point, int> collision(displacement, iterations);
    chaos_in_point.collisions.push_back(collision);
}
