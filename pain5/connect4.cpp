#include <iostream>
#include <vector>
#include <cstdlib> // For random number generation
#include <ctime>   // For seeding the random number generator
#include <algorithm>
#include <random>

const int ROWS = 6;
const int COLS = 7;
const char EMPTY = ' ';
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';
const int MediumLevel = 3;
const int HardLevel = 5;
int LEVEL;
int MODE;

using namespace std;

class ConnectFour {
public:
    ConnectFour(bool isAIPlayer1, bool isAIPlayer2)
            : currentPlayer(PLAYER1),
              aiPlayer1(isAIPlayer1),
              aiPlayer2(isAIPlayer2) {
        board = std::vector<std::vector<char>>(ROWS, std::vector<char>(COLS, EMPTY));
        std::srand(std::time(nullptr));
    }

    void play() {
        while (!isGameOver()) {
            displayBoard();
            if ((currentPlayer == PLAYER1 && aiPlayer1) ||
                (currentPlayer == PLAYER2 && aiPlayer2)) {
                int column = getAIMove();
                std::cout << "AI Player " << currentPlayer << " chooses column " << column << std::endl;
                dropDisc(column, currentPlayer);
            } else {
                int column;
                do {
                    std::cout << "Player " << currentPlayer << ", enter a column (1-7): ";
                    std::cin >> column;
                } while (!isValidMove(column));

                dropDisc(column, currentPlayer);
            }

            if (isWinningMove(currentPlayer, 4)) {
                displayBoard();
                if ((currentPlayer == PLAYER1 && aiPlayer1) ||
                    (currentPlayer == PLAYER2 && aiPlayer2)) {
                    std::cout << "AI Player " << currentPlayer << " wins!" << std::endl;
                } else {
                    std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                }
                return;
            }

            // Switch to the other player for the next turn
            currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
        }

        displayBoard();
        std::cout << "It's a draw!" << std::endl;
    }

private:
    std::vector<std::vector<char>> board;
    char currentPlayer;
    bool aiPlayer1;
    bool aiPlayer2;

    void displayBoard() {
        std::cout << "\n";
        for (int i = ROWS - 1; i >= 0; --i) {
            std::cout << "|";
            for (int j = 0; j < COLS; ++j) {
                std::cout << board[i][j] << "|";
            }
            std::cout << "\n";
        }
        std::cout << "-----------------\n";
        std::cout << " 1 2 3 4 5 6 7\n";
    }

    bool isValidMove(int column) {
        return column >= 1 && column <= COLS && board[ROWS - 1][column - 1] == EMPTY;
    }

    void dropDisc(int column, char player) {
        for (int i = 0; i < ROWS; ++i) {
            if (board[i][column - 1] == EMPTY) {
                board[i][column - 1] = player;
                break;
            }
        }
    }

    void undoMove(int column) {
        for (int i = ROWS - 1; i >= 0; --i) {
            if (board[i][column - 1] != EMPTY) {
                board[i][column - 1] = EMPTY;
                break;
            }
        }
    }


    bool isWinningMove(char player,int count) {
        return checkRows(player,4) || checkColumns(player, 4) || checkDiagonals(player, 4);
    }

    bool numCons(char player, int count) {
        return checkRows(player, count) || checkColumns(player, count) || checkDiagonals(player, count);
    }

    bool checkRows(char player, int count) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS - count + 1; ++j) {
                bool isWinning = true;
                for (int k = 0; k < count; ++k) {
                    if (board[i][j + k] != player) {
                        isWinning = false;
                        break;
                    }
                }
                if (isWinning) {
                    return true;
                }
            }
        }
        return false;
    }

    bool checkColumns(char player, int count) {
        for (int i = 0; i < ROWS - count + 1; ++i) {
            for (int j = 0; j < COLS; ++j) {
                bool isWinning = true;
                for (int k = 0; k < count; ++k) {
                    if (board[i + k][j] != player) {
                        isWinning = false;
                        break;
                    }
                }
                if (isWinning) {
                    return true;
                }
            }
        }
        return false;
    }

    bool checkDiagonals(char player, int count) {
        for (int i = 0; i < ROWS - count + 1; ++i) {
            for (int j = 0; j < COLS - count + 1; ++j) {
                bool isWinningDiagonal = true;
                bool isWinningAntiDiagonal = true;

                for (int k = 0; k < count; ++k) {
                    // Check diagonal
                    if (board[i + k][j + k] != player) {
                        isWinningDiagonal = false;
                    }

                    // Check anti-diagonal
                    if (board[i + k][j + count - 1 - k] != player) {
                        isWinningAntiDiagonal = false;
                    }
                }

                if (isWinningDiagonal || isWinningAntiDiagonal) {
                    return true;
                }
            }
        }
        return false;
    }


    bool isGameOver() {
        for (int i = 0; i < COLS; ++i) {
            if (board[ROWS - 1][i] == EMPTY) {
                return false;
            }
        }
        return true;
    }

    int evaluateBoardForPlayerOne() {
        int score = 0;
        if (isWinningMove('O', 4)) {
            score = 1000;
        } else if (isWinningMove('X', 4)) {
            score = -1000;
        }
        else if (numCons('O', 3)) {
            score = 500;
        }
        else if (numCons('X', 3)) {
            score = -500;
        }
        else if (numCons('O', 2)) {
            score = 100;
        }
        else if (numCons('X', 2)) {
            score = -100;
        }
        return score;
    }

    int evaluateBoardForPlayerTwo() {
        int score = 0;
        if (isWinningMove('O', 4)) {
            score = -1000;
        } else if (isWinningMove('X', 4)) {
            score = 1000;
        }
        else if (numCons('O', 3)) {
            score = -500;
        }
        else if (numCons('X', 3)) {
            score = 500;
        }
        else if (numCons('O', 2)) {
            score = -100;
        }
        else if (numCons('X', 2)) {
            score = 100;
        }
        return score;
    }
    int getRandomMove() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, COLS);
        return distrib(gen);
    }


    int getAIMove() {
        if (LEVEL == 1) {
            return getEasyAIMove();
        } else if (LEVEL == 2) {
            return getMediumAIMove();
        } else if (LEVEL == 3) {
            return getHardAIMove();
        } else {
            return getEasyAIMove(); // Default to easy difficulty if LEVEL is not 1, 2, or 3
        }
    }


    int minimax(char player, int depth, int alpha, int beta) {
        if (depth == 0 || isWinningMove('X', 4) || isWinningMove('O', 4) || (aiPlayer2 && !aiPlayer1 && isGameOver())) {
            return evaluateBoardForPlayerOne();
        }
        if (depth == 0 || isWinningMove('X', 4) || isWinningMove('O', 4) || (aiPlayer1 && !aiPlayer2 && isGameOver())) {
            return evaluateBoardForPlayerTwo();
        }

        if (player == 'O') {
            int maxEval = INT_MIN;
            for (int col = 1; col <= COLS; ++col) {
                if (isValidMove(col)) {
                    dropDisc(col, player);
                    int eval = minimax('X', depth - 1, alpha, beta);
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    undoMove(col);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
            return maxEval;
        } else {
            int minEval = INT_MAX;
            for (int col = 1; col <= COLS; ++col) {
                if (isValidMove(col)) {
                    dropDisc(col, player);
                    int eval = minimax('O', depth - 1, alpha, beta);
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    undoMove(col);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
            return minEval;
        }
    }
    int minimax(char player, int depth) {
        if (depth == 0 || isWinningMove('X', 4) || isWinningMove('O', 4) || (aiPlayer2 && !aiPlayer1 && isGameOver())) {
            return evaluateBoardForPlayerOne();
        }
        if (depth == 0 || isWinningMove('X', 4) || isWinningMove('O', 4) || (aiPlayer1 && !aiPlayer2 && isGameOver())) {
            return evaluateBoardForPlayerTwo();
        }

        if (player == 'O') {
            int maxEval = INT_MIN;
            for (int col = 1; col <= COLS; ++col) {
                if (isValidMove(col)) {
                    dropDisc(col, player);
                    int eval = minimax('X', depth - 1);
                    maxEval = max(maxEval, eval);
                    undoMove(col);
                }
            }
            return maxEval;
        } else {
            int minEval = INT_MAX;
            for (int col = 1; col <= COLS; ++col) {
                if (isValidMove(col)) {
                    dropDisc(col, player);
                    int eval = minimax('O', depth - 1);
                    minEval = min(minEval, eval);
                    undoMove(col);
                }
            }
            return minEval;
        }
    }

    int getEasyAIMove() {
        return getRandomMove();
    }

    int getMediumAIMove() {
        if (aiPlayer2 && aiPlayer1) {
            if (currentPlayer == 'O') {
                goto player2;
            }
            else if (currentPlayer == 'X') {
                goto player1;
            }
        } else if (aiPlayer2) {
            player2:
            int bestMove = -1;
            int bestScore = INT_MIN;
            vector<int> v={1, 2, 3, 4, 5, 6, 7};
            random_device rd;
            mt19937 rng(rd());
            std::shuffle(v.begin(), v.end(), rng);


            for (int col = 1; col <= COLS; ++col) {
                if (isValidMove(col)) {
                    dropDisc(col, 'O');
                    int moveScore = minimax('X', MediumLevel);
                    undoMove(col);

                    if (moveScore > bestScore) {
                        bestScore = moveScore;
                        bestMove = col;
                    }
                }
            }

            return bestMove;
        } else if (aiPlayer1) {
            player1:
            int bestMove = -1;
            int bestScore = INT_MIN;

            for (int col = 1; col <= COLS; ++col) {
                if (isValidMove(col)) {
                    dropDisc(col, 'O');
                    int moveScore = minimax('X', MediumLevel);
                    undoMove(col);

                    if (moveScore > bestScore) {
                        bestScore = moveScore;
                        bestMove = col;
                    }
                }
            }

            return bestMove;
        }
    }


    int getHardAIMove() {
        if (aiPlayer2 && aiPlayer1) {
            if (currentPlayer == 'O') {
                goto player2;
            }
            else if (currentPlayer == 'X') {
                goto player1;
            }
        } else if (aiPlayer2) {
            player2:
            int bestMove = -1;
            int bestScore = INT_MIN;
            for (int col = 1; col <= COLS; ++col) {
                if (isValidMove(col)) {
                    dropDisc(col, 'O');
                    int moveScore = minimax('X', HardLevel, INT_MIN, INT_MAX);
                    undoMove(col);

                    if (moveScore > bestScore) {
                        bestScore = moveScore;
                        bestMove = col;
                    }
                }
            }

            return bestMove;
        } else if (aiPlayer1) {
            player1:
            int bestMove = -1;
            int bestScore = INT_MIN;
            vector<int> v{1, 2, 3, 4, 5, 6, 7};
            random_device rd;
            mt19937 rng(rd());
            std::shuffle(v.begin(), v.end(), rng);
            for (int col = 1; col <= COLS; ++col) {
                if (isValidMove(col)) {
                    dropDisc(col, 'O');
                    int moveScore = minimax('X', HardLevel, INT_MIN, INT_MAX);
                    undoMove(col);

                    if (moveScore > bestScore) {
                        bestScore = moveScore;
                        bestMove = col;
                    }
                }
            }

            return bestMove;
        }
    }

};

using namespace std;

int main() {

    bool isAIPlayer1 = false;
    bool isAIPlayer2 = false;
    int MODE, LEVEL;

    cout << "Welcome to Connect Four!" << endl;
    cout << "Select Game Mode:" << endl;
    cout << "1. Human vs Human" << endl;
    cout << "2. Human vs AI" << endl;
    cout << "3. AI vs AI" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> MODE;

    while (MODE < 1 || MODE > 3) {
        cout << "Invalid choice. Please enter 1, 2, or 3: ";
        cin >> MODE;
    }

    if (MODE == 1) {
        isAIPlayer1 = false;
        isAIPlayer2 = false;
    } else if (MODE == 2) {
        int player;
        cout << "Would you like to be Player 1 or 2? (Enter 1 or 2): ";
        cin >> player;

        while (player != 1 && player != 2) {
            cout << "Invalid choice. Please enter 1 or 2: ";
            cin >> player;
        }

        if (player == 1) {
            isAIPlayer2 = true;
            cout << "You are Player 1. AI will be Player 2." << endl;
        } else {
            isAIPlayer1 = true;
            cout << "You are Player 2. AI will be Player 1." << endl;
        }

        cout << "Select AI Difficulty Level:" << endl;
        cout << "1. Easy" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Hard" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> LEVEL;

        while (LEVEL < 1 || LEVEL > 3) {
            cout << "Invalid choice. Please enter 1, 2, or 3: ";
            cin >> LEVEL;
        }
    } else {
        isAIPlayer1 = true;
        isAIPlayer2 = true;
    }

    ConnectFour game(isAIPlayer1, isAIPlayer2);
    game.play();
    return 0;
}
