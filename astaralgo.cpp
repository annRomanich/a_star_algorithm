#include "astaralgo.h"

ostream& operator<<(ostream& os, const Coord& coord) {
    os << "(" << coord.x << "," << coord.y << ")";
    return os;
}

bool operator<(const Coord& l, const Coord& r) {
    return l.x < r.x || (l.x == r.x && l.y < r.y);
}

bool operator==(const Coord& l, const Coord& r) {
    return l.x == r.x && l.y == r.y;
}

double distance(Coord start, Coord end) {
    double x = abs(end.x - start.x);
    double y = abs(end.y - start.y);
    return sqrt(pow(x, 2) + pow(y, 2));
}

bool operator<(const Visited& l, const Visited& r) {
    return l.coord < r.coord;
}
