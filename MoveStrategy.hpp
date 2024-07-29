#pragma once

#include <vector>
#include "Coordinate.hpp"

class ChessBoard;

class MoveStrategy {
public:
    MoveStrategy() = default;
    virtual ~MoveStrategy() = default;
    virtual std::vector<Coordinate> availableMoves(
        ChessBoard& chessBoard, 
        Coordinate coordinate, 
        const std::vector<Coordinate>& jump
    ) = 0;
};


class ShortMoveStrategy : public MoveStrategy {
public:
    std::vector<Coordinate> availableMoves(
        ChessBoard& chessBoard, 
        Coordinate coordinate, 
        const std::vector<Coordinate>& jump
    ) override;
};


class LongMoveStrategy : public MoveStrategy {
public:
    std::vector<Coordinate> availableMoves(
        ChessBoard& chessBoard, 
        Coordinate coordinate, 
        const std::vector<Coordinate>& jump
    ) override;
};


class PawnMoveStrategy : public MoveStrategy {
public:
    std::vector<Coordinate> availableMoves(
        ChessBoard& chessBoard, 
        Coordinate coordinate, 
        const std::vector<Coordinate>& jump
    ) override;
};
