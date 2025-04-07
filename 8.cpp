#include <iostream>
#include <cmath>

using namespace std;

int queenPos[10];

void printBoard(int size) {
    cout << "\nChessboard Configuration:\n";
    int queenNum = 1;
    for (int row = 1; row <= size; row++) {
        for (int col = 1; col <= size; col++) {
            if (queenPos[row] == col) {
                cout << " Q" << queenNum;
                queenNum++;
            } else {
                cout << " . ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafe(int row, int column) {
    for (int prevRow = 1; prevRow < row; prevRow++) {
        if (queenPos[prevRow] == column || 
            abs(queenPos[prevRow] - column) == abs(prevRow - row)) {
            return false;
        }
    }
    return true;
}

void solveNQueens(int currentRow, int boardSize) {
    for (int tryCol = 1; tryCol <= boardSize; tryCol++) {
        queenPos[currentRow] = tryCol;
        if (isSafe(currentRow, tryCol)) {
            if (currentRow == boardSize) {
                printBoard(boardSize);
            } else {
                solveNQueens(currentRow + 1, boardSize);
            }
        }
    }
}

int main() {
    int boardSize;
    cout << "Enter the chessboard size: ";
    cin >> boardSize;

    solveNQueens(1, boardSize);
    
    return 0;
}