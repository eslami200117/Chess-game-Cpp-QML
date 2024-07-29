#include "ChessBoard.hpp"


using namespace std;

ChessBoard::ChessBoard()
    : m_board(8, vector<shared_ptr<ChessPiece>>(8, nullptr))
    , m_turn(true)
    , m_loadAddress("resource/default.txt")
    , m_winer(0)
{
    loadGame();
}

void ChessBoard::nextTurn(){
    m_turn = !m_turn;
}

QVariant ChessBoard::getTurn() const{
    if(m_turn) return "White";
    else return "Black";
}

std::shared_ptr<ChessPiece> ChessBoard::getPiece(Coordinate c) const
{
    return m_board[c.x][c.y];
}

void ChessBoard::listAvailableFiles() const {
    cout << "Available game files in the 'resource' folder:" << endl;
    for (const auto& entry : filesystem::directory_iterator("resource")) {
        if (entry.is_regular_file()) {
            string filename = entry.path().filename().string();
            size_t lastdot = filename.find_last_of(".");
            if (lastdot != string::npos) {
                filename = filename.substr(0, lastdot);
            }
            cout << "  " << filename << endl;
        }
    }
}

int ChessBoard::coordinateToIndex(Coordinate c)
{
    return (c.x*8)+ c.y;
}

void ChessBoard::saveGame(const string& filename) const{
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return;
    }

    file << (m_turn ? "white" : "black") << endl;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if(m_board[row][col])
                file << m_board[row][col]->getChar();
            else
                file<<'.';
        }
        file << endl;
    }

    file.close();
}


void ChessBoard::printBoard() const {
    const int boardSize = 8;
    const string columnLabels = "   a b c d e f g h";

    cout << columnLabels << endl;
    cout << " +-----------------+" << endl;

    for (int row = 0; row < boardSize; ++row) {
        cout << boardSize - row << "| ";
        for (int col = 0; col < boardSize; ++col) {
            Coordinate c = {row, col};
            char pieceChar = '.';
            if (isOccupied(c)) {
                pieceChar = getPieceChar(c);
            }
            cout << pieceChar << ' ';
        }
        cout << "| " << boardSize - row << endl;
    }

    cout << " +-----------------+" << endl;
    cout << columnLabels << endl;
}

void ChessBoard::loadGame() {
    m_winer = 0;
    string filename;
    filename = m_loadAddress;

    ifstream file(m_loadAddress);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        cout << "Default game load."<<endl;
        file = ifstream(m_loadAddress);
    }
    string line;

    if (getline(file, line)) {
        m_turn = (line == "white");
    } else {
        cout << "Error: Failed to read the boolean value from the file" << endl;
        return;
    }

    int row = 0;
    while (getline(file, line) && row < 8) {
        for (int col = 0; col < 8 && col < line.size(); ++col) {
            m_board[row][col] = ChessPieceFactory::createPiece(line[col], Coordinate{row, col});
        }
        ++row;
    }

    file.close();
}

char ChessBoard::getPieceChar(Coordinate c) const
{
    if(isOccupied(c)){
        return getPiece(c)->getChar();
    }

    return 'e';
}

char ChessBoard::getPieceChar(int row, int column)
{
    Coordinate c = {row, column};
    if(isOccupied(c)){
        return getPiece(c)->getChar();
    }

    return 'e';
}

bool ChessBoard::getPieceColor(Coordinate c) const
{
    if(isOccupied(c)){
        return getPiece(c)->getColor();
    }
    return false;
}

bool ChessBoard::getPieceColor(int row, int column)
{
    Coordinate c = {row, column};
    if(isOccupied(c)){
        return getPiece(c)->getColor();
    }
    return false;
}

void ChessBoard::extracted(QVariantList &qRe, vector<Coordinate> &re) {
    for (auto &v : re) {
        int index = coordinateToIndex(v);
        QVariant qIndex(index);
        qRe.push_back(qIndex);
    }
}

QVariantList ChessBoard::validMoves(int row, int column) {
    Coordinate c = {row, column};
    QVariantList qRe;
    if(isOpponent(c) || !isOccupied(c)){
        return qRe;
    }
    vector<Coordinate> re = getPiece(c)->availableMoves(*this);
    extracted(qRe, re);
    // qDebug()<<qRe;
    return qRe;
}

void ChessBoard::move(int src_, int des_)
{
    Coordinate src = {src_/8, src_%8};
    Coordinate des = {des_/8, des_%8};
    movePiece(src, des);
}

bool ChessBoard::isDone(){
    if(m_winer == 0)
        return false;
    if(m_winer == 2){
        cout<< "White is winner!"<<endl;
    } else if(m_winer == 1){
        cout<< "Black is winner!"<<endl;
    }
    return true;
}

bool ChessBoard:: isOccupied(Coordinate coordinate) const {
    return m_board[coordinate.x][coordinate.y] != nullptr;
}

// bool ChessBoard::executeCommand(){
//     while(true) {
//         cout<<"Player " << getTurn() << " move: ";
//         string command, from, to, dummy;
//         getline(cin, command);

//         if(command == "q"){
//             quite();
//             return true;
//         }
//         istringstream iss(command);
//         if (!(iss >> from >> dummy >> to) || dummy != "to") {
//             cout << "Invalid command format. (e.g., 'a6 to b6') or 'q' to quit." << endl;
//             continue;
//         };

//         Coordinate src = convertPosition(from);
//         Coordinate des = convertPosition(to);

//         if (src == Coordinate{-1, -1} || des == Coordinate{-1, -1}) {
//             cout << "Invalid position in command. Use positions between 'a1' and 'h8'." << endl;
//             continue;
//         }
//         if(!isSrcDesValid(src, des)){
//             continue;
//         }
        
//         movePiece(src, des);
//         return false;

//     }

// }


Coordinate ChessBoard::convertPosition(const string& pos) const {
    char file = pos[0];
    char rank = pos[1];
    int x = 8 - (rank - '1') - 1;
    int y = file - 'a';
    if (0 <= x && x <= 8 && 0 <= y && x <= 8 ){
        return Coordinate{x, y};
    }
    return Coordinate{-1, -1};
}

string ChessBoard::reverseCoordinate(Coordinate coordinate) {
    char rank = '8' - coordinate.x;
    char file = 'a' + coordinate.y;
    return std::string{file, rank};
}

bool ChessBoard::isValid(Coordinate coordinate){
    bool rangeValidate = false;
    bool emptyValidate = false;
    if((-1 < coordinate.x) &&
        (coordinate.x < 8) &&
        (-1 < coordinate.y) &&
        (coordinate.y < 8)){
        rangeValidate = true;
    } else return false;

    if(!isOccupied(coordinate)){
        emptyValidate = true;
    } else {
        if(getPieceColor(coordinate) != m_turn){
            emptyValidate = true;
        }
    }

    return rangeValidate && emptyValidate;
}

void ChessBoard::quite()const{
    cout<<"Are you want to save game? [y/n]"<<endl;
    char y_n;
    cin>>y_n;
    if(y_n == 'y'){
        cout<<"Enter a name for game: ";
        string name;
        cin>>name;
        saveGame("resource/" + name + ".txt");
    }
}
bool ChessBoard::isOpponent(Coordinate des) const{
    if(!isOccupied(des)) return false;
    if(getPieceColor(des) == m_turn) return false;
    return true;
}

bool ChessBoard::isSrcDesValid(Coordinate src, Coordinate des) {
    if(!isOccupied(src)){
        cout<<"this box is empty!"<<endl;
        return false;
    }
    if(getPieceColor(src) != m_turn){
        cout<<"choise your own side!"<<endl;
        return false;
    }
    std::vector<Coordinate> allDes = getPiece(src)->availableMoves(*this);
    for (const auto& move : allDes) {
        if (move == des) {
            return true;
        }
    }

    cout << "Invalid move." << endl;
    cout<<"All possible move for "<<reverseCoordinate(src)<<": {";
    for (const auto& move : allDes) {
        cout<<reverseCoordinate(move)<<", ";
    }
    cout<<"}"<<endl;
    return false;
}

void ChessBoard::movePiece(Coordinate src, Coordinate des){
    bool isKing;
    if(isOccupied(des)){
        isKing  = toupper(getPieceChar(des)) == 75;
    }
    m_board[des.x][des.y] = std::move(getPiece(src));
    m_board[src.x][src.y] = nullptr;
    getPiece(des)->setCoordinate(des);
    if(isKing){
        m_winer = int(m_turn) + 1;
    }
}
