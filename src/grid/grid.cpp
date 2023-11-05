#include "grid.hpp"
#include "chaos.hpp"
#include "point.hpp"

#include "output.hpp"

namespace grid {
    namespace debug {
        void add_collision(Collision collision) {
            if (global::debug_flags::COLLISIONS) {
                output::inform("Adding collision at " + collision.point.to_string() + " with " +
                               to_string(collision.iteration) + " iterations");
            }
        }
    }  // namespace debug

    // Constructor
    Grid::Grid(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        output::inform("Creating grid with " + to_string(rows) + " rows and " + to_string(cols) +
                       " cols");

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

    vector<Point> Grid::points() const {
        vector<Point> points;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                Point p(row, col);
                points.push_back(p);
            }
        }
        return points;
    }

    const Chaos& Grid::grid_point_info(const Point& p) const {
        return grid[p.row][p.col];
    }

    void Grid::add_collision(const Point& p, Point displacement, int iterations,
                             unsigned int accumulate) {
        Collision c(displacement, iterations);
        debug::add_collision(c);
        Chaos& chaos = grid[p.row][p.col];
        chaos.collisions.push_back(c);
        chaos.accumulation += accumulate;
    }

    Point Grid::random_point() const {
        int row = rand() % rows;
        int col = rand() % cols;
        return Point(row, col);
    }

    bool Grid::has_collision(const Point& p) const {
        return !grid[p.row][p.col].collisions.empty();
    }

    vector<Point> bresenham_line(const Point& start, const Point& end) {
        std::vector<Point> points;

        int startX = start.col;
        int startY = start.row;
        int endX = end.col;
        int endY = end.row;

        int deltaX = abs(endX - startX);     // Difference in columns
        int deltaY = -abs(endY - startY);    // Difference in rows (negative)
        int stepX = startX < endX ? 1 : -1;  // Determine the direction of the step in X
        int stepY = startY < endY ? 1 : -1;  // Determine the direction of the step in Y
        int error = deltaX + deltaY;         // Initialize the error term

        while (true) {
            points.emplace_back(startY, startX);  // Add the current point to the list
            // Check if the end point has been reached
            if (startX == endX && startY == endY)
                break;
            int error2 = 2 * error;  // Double the error term for comparison
            // Adjust the error term and current point in X direction
            if (error2 >= deltaY) {
                error += deltaY;
                startX += stepX;
            }
            // Adjust the error term and current point in Y direction
            if (error2 <= deltaX) {
                error += deltaX;
                startY += stepY;
            }
        }

        return points;
    }

    void Grid::print(ostream& os) const {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                Point p(row, col);
                if (has_collision(p)) {
                    os << "X ";
                } else {
                    os << "  ";
                }
            }
            os << endl;
        }
    }
}  // namespace grid
