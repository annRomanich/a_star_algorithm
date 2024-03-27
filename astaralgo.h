#ifndef ASTARALGO_H
#define ASTARALGO_H

#include <iostream>
#include <vector>

using namespace std;

struct Coord {
    int x, y;
};

ostream& operator<<(ostream& os, const Coord& coord);
bool operator<(const Coord& l, const Coord& r);
bool operator==(const Coord& l, const Coord& r);

vector<Coord> aStarSearch(Coord start, Coord goal, const vector<vector<int>> &field);


#endif // ASTARALGO_H
