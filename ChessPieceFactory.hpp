#include <memory>
#include "ChessPiece.hpp"

class ChessPieceFactory {
public:
    static std::unique_ptr<ChessPiece> createPiece(const char pieceChar, Coordinate coordinate);
};
