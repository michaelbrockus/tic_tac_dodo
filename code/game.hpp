//
// file: game.hpp
// author: Michael Brockus
// gmail: <michaelbrockus@gmail.com>
//
#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <array>

enum class State
{
    WIN = 1000,
    DRAW = 0,
    LOSS = -1000
};

const char AI_MARKER = 'O';
const char PLAYER_MARKER = 'X';
const char EMPTY_SPACE = '-';

const int START_DEPTH = 0;

//
// Testing prototypes
void printBoard(std::array<std::array<char, 3>, 3> board);
void printGameState(int state);
char getOpponentMarker(char marker);
std::vector<std::pair<int, int>> getLegalMoves(std::array<std::array<char, 3>, 3> board);
bool positionOccupied(std::array<std::array<char, 3>, 3> board, std::pair<int, int> pos);
std::vector<std::pair<int, int>> getOccupiedPositions(std::array<std::array<char, 3>, 3> board, char marker);
bool boardIsFull(std::array<std::array<char, 3>, 3> board);
bool gameIsWon(std::vector<std::pair<int, int>> occupiedPositions);
int getBoardState(std::array<std::array<char, 3>, 3> board, char marker);
std::pair<int, int> findBestMove(std::array<std::array<char, 3>, 3> board);
const bool gameIsDone(std::array<std::array<char, 3>, 3> board);

//
// Game helpers
void printBoard(std::array<std::array<char, 3>, 3> board);
void printGameState(int state);

#endif // end of GAME_H