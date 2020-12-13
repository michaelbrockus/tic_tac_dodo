//
// file: game.cpp
// author: Michael Brockus
// gmail: <michaelbrockus@gmail.com>
//
#include "game.hpp"
#include <iostream>
#include <algorithm>

// All possible winning states
std::vector<std::vector<std::pair<int, int>>> winningStates{
    // Every row
    {{0, 0}, {0, 1}, {0, 2}},
    {{1, 0}, {1, 1}, {1, 2}},
    {{2, 0}, {2, 1}, {2, 2}},

    // Every column
    {{0, 0}, {1, 0}, {2, 0}},
    {{0, 1}, {1, 1}, {2, 1}},
    {{0, 2}, {1, 2}, {2, 2}},

    // Every diagonal
    {{0, 0}, {1, 1}, {2, 2}},
    {{2, 0}, {1, 1}, {0, 2}}};

//
// Get all available legal moves (spaces that are not occupied)
//
std::vector<std::pair<int, int>> getLegalMoves(std::array<std::array<char, 3>, 3> board)
{
    std::vector<std::pair<int, int>> legalMoves;
    for (size_t row = 0; row < 3; ++row)
    {
        for (size_t col = 0; col < 3; ++col)
        {
            if (board[row][col] != AI_MARKER && board[row][col] != PLAYER_MARKER)
            {
                legalMoves.push_back({row, col});
            } // end if

        } // end for

    } // end for

    return legalMoves;
} // end of function getLegalMoves

//
// Check if a position is occupied
//
bool positionOccupied(std::array<std::array<char, 3>, 3> board, std::pair<int, int> pos)
{
    std::vector<std::pair<int, int>> legalMoves = getLegalMoves(board);

    for (size_t index = 0; index < legalMoves.size(); ++index)
    {
        if (pos.first == legalMoves[index].first && pos.second == legalMoves[index].second)
        {
            return false;
        } // end if

    } // end for

    return true;
} // end of function positionOccupied

//
// Get all board positions occupied by the given marker
//
std::vector<std::pair<int, int>> getOccupiedPositions(std::array<std::array<char, 3>, 3> board, char marker)
{
    std::vector<std::pair<int, int>> occupiedPositions;

    for (size_t row = 0; row < 3; ++row)
    {
        for (size_t col = 0; col < 3; ++col)
        {
            if (marker == board[row][col])
            {
                occupiedPositions.push_back({row, col});
            } // end if

        } // end for

    } // end for

    return occupiedPositions;
} // end of function getOccupiedPositions

//
// Check if the board is full
//
bool boardIsFull(std::array<std::array<char, 3>, 3> board)
{
    std::vector<std::pair<int, int>> legal_moves = getLegalMoves(board);

    if (0 == legal_moves.size())
    {
        return true;
    } // end if
    else
    {
        return false;
    } // end else
} // end of function boardIsFull

//
// Check if the game has been won
//
bool gameIsWon(std::vector<std::pair<int, int>> occupiedPositions)
{
    bool game_won;

    for (size_t winIndex = 0; winIndex < winningStates.size(); winIndex++)
    {
        game_won = true;
        std::vector<std::pair<int, int>> curr_win_state = winningStates[winIndex];
        for (int index = 0; index < 3; index++)
        {
            if (!(std::find(std::begin(occupiedPositions),
                            std::end(occupiedPositions),
                            curr_win_state[index]) != std::end(occupiedPositions)))
            {
                game_won = false;
                break;
            } // end if

        } // end for

        if (game_won)
        {
            break;
        } // end if

    } // end for
    return game_won;
} // end of function gameIsWon

//
// get the opponent marker char
//
char getOpponentMarker(char marker)
{
    char opponentMarker;
    if (marker == PLAYER_MARKER)
    {
        opponentMarker = AI_MARKER;
    } // end if
    else
    {
        opponentMarker = PLAYER_MARKER;
    } // end else

    return opponentMarker;
} // end of function getOpponentMarker

//
// Check if someone has won or lost
//
int getBoardState(std::array<std::array<char, 3>, 3> board, char marker)
{

    char opponentMarker = getOpponentMarker(marker);

    std::vector<std::pair<int, int>> occupiedPositions = getOccupiedPositions(board, marker);

    if (gameIsWon(occupiedPositions))
    {
        return static_cast<int>(State::WIN);
    } // end if

    occupiedPositions = getOccupiedPositions(board, opponentMarker);

    if (gameIsWon(occupiedPositions))
    {
        return static_cast<int>(State::LOSS);
    } // end if

    if (boardIsFull(board))
    {
        return static_cast<int>(State::DRAW);
    } // end if

    return static_cast<int>(State::DRAW);
} // end of function getBoardState

//
// Apply the minimax game optimization algorithm
//
static std::pair<int, std::pair<int, int>> minimax(std::array<std::array<char, 3>, 3> board, char optForMarker, bool isMax)
{
    //
    // Initialize best move
    std::pair<int, int> bestMove = {-1, -1};

    //
    // Get a list of the empty board locations.
    std::vector<std::pair<int, int>> legalMoves = getLegalMoves(board);

    //
    // Determine which marker we are working with based on the number of
    // empty spaces... An odd number indicates it is the PLAYER's turn.
    char marker = (legalMoves.size() & 1) ? PLAYER_MARKER : AI_MARKER;

    //
    // Get the current state of the board from the marker we are optimizing for.
    int boardState = getBoardState(board, optForMarker);

    //
    // If we have no more moves to make then return a WIN, LOSE or DRAW value.
    if ((legalMoves.size() == 0) || (boardState != static_cast<int>(State::DRAW)))
    {
        return {boardState, bestMove};
    } // end if

    //
    // Start with the value furthest away from what we want to find.
    int bestScore = isMax ? INT32_MIN : INT32_MAX;

    //
    // Go through all of the open positions and see how they score.
    for (size_t index = 0; index < legalMoves.size(); ++index)
    {
        //
        // Set the current location, score it and then restore as empty.
        std::pair<int, int> currMove = legalMoves[index];
        board[currMove.first][currMove.second] = marker;
        int newScore = minimax(board, optForMarker, !isMax).first;
        board[currMove.first][currMove.second] = EMPTY_SPACE;

        //
        // Track the appropriate MAX or MIN score. Short circuit the
        // loop if we get what we were looking for.
        if (isMax)
        {
            if (newScore > bestScore)
            {
                bestMove = currMove;
                bestScore = newScore;
                if (bestScore == static_cast<int>(State::WIN))
                {
                    break;
                } // end if

            } // end if

        } // end if
        else
        {
            if (newScore < bestScore)
            {
                bestMove = currMove;
                bestScore = newScore;
                if (bestScore == static_cast<int>(State::LOSS))
                {
                    break;
                } // end if

            } // end if

        } // end else

    } // end for
    return {bestScore, bestMove};
} // end of function minimax

std::pair<int, int> findBestMove(std::array<std::array<char, 3>, 3> board)
{
    //
    // Get a list of the empty board locations.
    std::vector<std::pair<int, int>> legalMoves = getLegalMoves(board);

    //
    // Determine which marker we are working with based on the number of
    // empty spaces... An odd number indicates it is the PLAYER's turn.
    char marker = (legalMoves.size() & 1) ? PLAYER_MARKER : AI_MARKER;

    return minimax(board, marker, true).second;
}

//
// Check if the game is finished
//
const bool gameIsDone(std::array<std::array<char, 3>, 3> board)
{
    if (boardIsFull(board))
    {
        return true;
    } // end if

    if (static_cast<int>(State::DRAW) != getBoardState(board, AI_MARKER))
    {
        return true;
    } // end if

    return false;
} // end of function findBestMove

//
// Print the current board state
//
void printBoard(std::array<std::array<char, 3>, 3> board)
{
    std::cout << std::endl;
    std::cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << std::endl
              << std::endl;
} // end of function printPoard

//
// Print game state
//
void printGameState(int state)
{
    if (static_cast<int>(State::WIN) == state)
    {
        std::cout << "WIN" << std::endl;
    } // end if
    else if (static_cast<int>(State::DRAW) == state)
    {
        std::cout << "DRAW" << std::endl;
    } // end else if
    else if (static_cast<int>(State::LOSS) == state)
    {
        std::cout << "LOSS" << std::endl;
    } // end else if
} // end of function printGameState
