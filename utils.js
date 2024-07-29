function getAddressImage(char) {
    switch (char) {
    case 101:
        return "";
    case 80:
        return "qrc:/image/pieces/pawn-w.svg";
    case 82:
        return "qrc:/image/pieces/rook-w.svg";
    case 78:
        return "qrc:/image/pieces/knight-w.svg";
    case 66:
        return "qrc:/image/pieces/bishop-w.svg";
    case 75:
        return "qrc:/image/pieces/queen-w.svg";
    case 81:
        return "qrc:/image/pieces/king-w.svg";
    case 112:
        return "qrc:/image/pieces/pawn-b.svg";
    case 114:
        return "qrc:/image/pieces/rook-b.svg";
    case 110:
        return "qrc:/image/pieces/knight-b.svg";
    case 98:
        return "qrc:/image/pieces/bishop-b.svg";
    case 113:
        return "qrc:/image/pieces/king-b.svg";
    case 107:
        return "qrc:/image/pieces/queen-b.svg";
    default:
        return "";
    }
}

function unSelecteOthers(){
    let i = 0;
    while(i < 64){
        boardRepeater.itemAt(i).unSelect();
        i += 1;
    }
}

function refreshAll(){
    let i = 0;
    while(i < 64){
        boardRepeater.itemAt(i).select_();
        i += 1;
    }
    unSelecteOthers()
}


function selectAll(listOfMove){
    boardRepeater.readyToSelect = false;
    boardRepeater.moves = []
    for(let i in listOfMove){
        boardRepeater.itemAt(listOfMove[i]).select_();
        boardRepeater.readyToSelect = true;
        boardRepeater.moves.push(listOfMove[i])
    }
}

function isNextMove(moves, index){
    for(let i in moves){
        if(moves[i] === index)
            return true;
    }
    return false;
}

