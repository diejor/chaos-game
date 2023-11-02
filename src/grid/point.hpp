
#ifndef POINT_HPP
#define POINT_HPP

struct Point {
    int row;
    int col;
    
    Point distance(Point const& other) const {
        Point dist;
        dist.row = other.row - row;
        dist.col = other.col - col;
        return dist;
    }
};

#endif // POINT_HPP 

