#include "ChessPieceFactory.hpp"

std::unique_ptr<ChessPiece> ChessPieceFactory::createPiece(const char pieceChar, Coordinate coordinate) {
    bool color = isupper(pieceChar); 
    switch (tolower(pieceChar)) {
        case 'k': return std::make_unique<King>(color, coordinate, pieceChar);
        case 'q': return std::make_unique<Queen>(color, coordinate, pieceChar);
        case 'r': return std::make_unique<Rook>(color, coordinate, pieceChar);
        case 'b': return std::make_unique<Bishop>(color, coordinate, pieceChar);
        case 'n': return std::make_unique<Knight>(color, coordinate, pieceChar);
        case 'p': return std::make_unique<Pawn>(color, coordinate, pieceChar);
        default: return nullptr;
    }
}
