#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "Coordinate.hpp"
#include "MoveStrategy.hpp"

class ChessBoard;

class ChessPiece {
public:
    ChessPiece(bool, Coordinate, std::shared_ptr<MoveStrategy>, std::vector<Coordinate>, char);
    virtual ~ChessPiece() = default;
    std::vector<Coordinate>availableMoves(ChessBoard&) const;
    bool getColor();
    void setCoordinate(Coordinate des);
    char getChar() const;
    

protected:
    const bool m_color;
    const char m_pieceChar;
    Coordinate m_coordinate;
    const std::vector<Coordinate> m_jump;
    const std::shared_ptr<MoveStrategy> m_strategy;

};


class King : public ChessPiece{
public:
    King(bool, Coordinate, char);
    ~King() = default;
};

class Queen : public ChessPiece{
public:
    Queen(bool, Coordinate, char);
    ~Queen() = default;
};

class Rook : public ChessPiece{
public:
    Rook(bool, Coordinate, char);
    ~Rook() = default;
};

class Bishop : public ChessPiece{
public:
    Bishop(bool, Coordinate, char);
    ~Bishop() = default;
};

class Knight : public ChessPiece{
public:
    Knight(bool, Coordinate, char);
    ~Knight() = default;
};

class Pawn : public ChessPiece{
public:
    Pawn(bool, Coordinate, char);
    ~Pawn() = default;
};
