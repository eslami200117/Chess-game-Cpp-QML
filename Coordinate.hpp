#pragma once

struct Coordinate {
    int x;
    int y;

    Coordinate(int x=0, int y=0) 
        : x(x), y(y)
    {}
    Coordinate(const Coordinate& other){
        x = other.x;
        y = other.y;
    }
    Coordinate& operator=(const Coordinate& other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    Coordinate operator+(const Coordinate& other) const {
        return Coordinate(other.x + x, other.y + y);
    }

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }

};


