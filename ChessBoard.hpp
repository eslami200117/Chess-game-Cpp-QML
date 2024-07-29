#pragma once

#include <string>
// #include <sstream>
#include <vector>
// #include <iostream>
#include <fstream>
#include <memory>
#include <filesystem>
#include "ChessPiece.hpp"
#include "Coordinate.hpp"
#include "ChessPieceFactory.hpp"
#include <QObject>
#include <qvariant.h>
#include <QDebug>
// #include <qqml.h>

class ChessBoard: public QObject {
    Q_OBJECT
public:
    ChessBoard();
    ~ChessBoard() = default;
    Q_INVOKABLE bool getPieceColor(int, int);
    Q_INVOKABLE bool isDone();
    Q_INVOKABLE void printBoard() const;
    Q_INVOKABLE void loadGame();
    Q_INVOKABLE void move(int, int);
    Q_INVOKABLE void nextTurn();
    Q_INVOKABLE char getPieceChar(int , int);
    Q_INVOKABLE QVariantList validMoves(int, int);
    Q_INVOKABLE QVariant getTurn() const;
    bool getPieceColor(Coordinate) const;
    bool isValid(Coordinate);
    bool isOccupied(Coordinate) const;
    bool isOpponent(Coordinate) const;
    // bool executeCommand();
    void quite() const;
    void saveGame(const std::string&) const;
    char getPieceChar(Coordinate) const;
private:
    std::shared_ptr<ChessPiece> charToPiece(char, Coordinate);
    std::shared_ptr<ChessPiece> getPiece(Coordinate) const;
    std::string reverseCoordinate(Coordinate);
    Coordinate convertPosition(const std::string&) const;
    bool isSrcDesValid(Coordinate, Coordinate);
    void movePiece(Coordinate, Coordinate);
    void listAvailableFiles() const;
    void extracted(QVariantList &qRe, std::vector<Coordinate> &re);
    int coordinateToIndex(Coordinate);

    std::vector<std::vector<std::shared_ptr<ChessPiece>>> m_board;
    bool m_turn;
    int m_winer;
    const std::string m_loadAddress;
};
