#include "grid.hpp"
#include "chaos.hpp"
#include "point.hpp"

#include "output.hpp"

namespace grid {
    namespace debug {
        void add_collision(Collision collision) {
            if (global::debug_flags::COLLISIONS) {
                output::inform("Adding collision at " + collision.point.to_string() + " with " + to_string(collision.iteration) + " iterations");
            }
        }
    }

    // Constructor
    Grid::Grid(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        output::inform("Creating grid with " + to_string(rows) + " rows and " + to_string(cols) + " cols");

        for (int row = 0; row < rows; row++) {
            vector<Chaos> row_vector;
            for (int col = 0; col < cols; col++) {
                Point p(row, col);
                Chaos chaos_in_point = Chaos(p);
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

    const Chaos& Grid::grid_point_info(const Point& p) const {
        return grid[p.row][p.col];
    }

    void Grid::add_collision(const Point& p, Point displacement, int iterations) {
        Collision c(displacement, iterations);
        debug::add_collision(c);
        grid[p.row][p.col].collisions.push_back(c);
    }

    Point Grid::random_point() const {
        int row = rand() % rows;
        int col = rand() % cols;
        return Point(row, col);
    }

    void Grid::print(ostream& os) const {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {

                Chaos chaos_in_point = grid[row][col];
                if (chaos_in_point.collisions.size() == 0) {
                    os << "  ";
                } else {
                    os << "X ";
                }
            }
            os << endl;
        }
    }
}  // namespace grid
