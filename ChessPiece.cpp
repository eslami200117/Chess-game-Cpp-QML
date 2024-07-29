#include "ChessPiece.hpp"
#include "ChessBoard.hpp"


using namespace std;

ChessPiece::ChessPiece(
    bool color,
    Coordinate coordinate,
    shared_ptr<MoveStrategy> moveStrategy,
    vector<Coordinate> jump,
    char pieceChar)
    : m_color(color)
    , m_coordinate(coordinate)
    , m_strategy(moveStrategy)
    , m_jump(jump)
    , m_pieceChar(pieceChar)
{}

bool ChessPiece::getColor(){
    return m_color;
}

void ChessPiece::setCoordinate(Coordinate des){
    m_coordinate = des;
}

vector<Coordinate> ChessPiece::availableMoves(ChessBoard& chessBoard) const {
    return m_strategy->availableMoves(chessBoard, m_coordinate, m_jump);
}

char ChessPiece::getChar() const{
    return m_pieceChar;
}

King::King(bool color, Coordinate coordinate, char pieceChar)
    :ChessPiece(color, coordinate, make_shared<ShortMoveStrategy>(), vector<Coordinate>{{0, 1}, {1, 1}, 
        {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}}, pieceChar)
{}

Queen::Queen(bool color, Coordinate coordinate, char pieceChar)
    :ChessPiece(color, coordinate, make_shared<LongMoveStrategy>(), vector<Coordinate>{{0, 1}, {1, 1}, 
        {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}}, pieceChar)
{}

Rook::Rook(bool color, Coordinate coordinate, char pieceChar)
    :ChessPiece(color, coordinate, make_shared<LongMoveStrategy>(),
                 vector<Coordinate>{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}, pieceChar)
{}

Bishop::Bishop(bool color, Coordinate coordinate, char pieceChar)
    :ChessPiece(color, coordinate, make_shared<LongMoveStrategy>(), 
                 vector<Coordinate>{{1, 1}, {1, -1}, {-1, -1}, {-1, 1}}, pieceChar)
{}

Knight::Knight(bool color, Coordinate coordinate, char pieceChar)
    :ChessPiece(color, coordinate, make_shared<ShortMoveStrategy>(), 
        vector<Coordinate>{{1, 2}, {2, 1}, {1, -2}, {-2, 1}, {-1, 2}, {2, -1}, {-1, -2}, {-2, -1}}, pieceChar)
{}

Pawn::Pawn(bool color, Coordinate coordinate, char pieceChar)
    : ChessPiece(color, coordinate, make_shared<PawnMoveStrategy>(),
        color ? vector<Coordinate>{{-1, 0}, {-1, -1}, {-1, 1}} :
                vector<Coordinate>{{1, 0}, {1, -1}, {1, 1}}, pieceChar)
{}


