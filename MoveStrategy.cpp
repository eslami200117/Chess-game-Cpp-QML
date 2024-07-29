#include "MoveStrategy.hpp"
#include "ChessBoard.hpp"

using namespace std;


vector<Coordinate> ShortMoveStrategy::availableMoves(ChessBoard& chessBoard, Coordinate coordinate, const vector<Coordinate>& jump){
    vector<Coordinate> allPossibleMoves;
    for(const auto& j : jump){
        Coordinate target = j + coordinate;
        if (chessBoard.isValid(target))
            allPossibleMoves.push_back(target);
    }
    return allPossibleMoves;
}


vector<Coordinate> LongMoveStrategy::availableMoves(ChessBoard& chessBoard, Coordinate coordinate, const vector<Coordinate>& jump){
    vector<Coordinate> allPossibleMoves;
    for(const auto& j : jump){
        Coordinate target = coordinate;
        for(int i = 0; i < 8; i++){
            target = target + j;
            if (chessBoard.isValid(target)){
                allPossibleMoves.push_back(target);
                if(chessBoard.isOpponent(target)){
                    break;
                }
            } else break;
        }
    }

    return allPossibleMoves;
}


vector<Coordinate> PawnMoveStrategy::availableMoves(ChessBoard& chessBoard, Coordinate coordinate, const std::vector<Coordinate>& jump){
    std::vector<Coordinate> allPossibleMoves;

    for (const auto& j : jump) {
        Coordinate target = j + coordinate;
        
        if (j.y == 0) {
            if (chessBoard.isValid(target) && !chessBoard.isOpponent(target)) {
                allPossibleMoves.push_back(target);
            }
        }

        if (j.y != 0) {
            if (chessBoard.isValid(target)){
                if(chessBoard.isOpponent(target)) {
                    allPossibleMoves.push_back(target);
                }
            }
        }

    }

    if ((coordinate.x == 1 && chessBoard.getTurn() == "Black") ||
        (coordinate.x == 6 && chessBoard.getTurn() == "White")) {
        Coordinate doubleMove = coordinate + Coordinate(coordinate.x == 1 ? 2 : -2, 0);
        Coordinate singleMove = coordinate + Coordinate(coordinate.x == 1 ? 1 : -1, 0);
        if (!chessBoard.isOccupied(doubleMove) && !chessBoard.isOccupied(singleMove)) {
            allPossibleMoves.push_back(doubleMove);
        }
    }

    return allPossibleMoves;
}
