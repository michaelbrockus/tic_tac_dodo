//
// file: test_cases.cpp
// author: Michael Brockus
// gmail: <michaelbrockus@gmail.com>
//
// USE CASE:
//
// The use case of this file is to contain the test cases needed by this
// project since its important to test once implementation against a set
// of common test cases
//
#include "game.hpp"
#include <iostream>
#include <unity.h>

//
//  project setup teardown functions if needed
//
void setUp(void)
{
    // TODO.
} // end of function setUp

void tearDown(void)
{
    // TODO.
} // end of function tearDown

//
// list of all the test cases for this project
//
static void test_validGridChar()
{
    TEST_ASSERT_EQUAL_CHAR('O', AI_MARKER);
    TEST_ASSERT_EQUAL_CHAR('X', PLAYER_MARKER);
    TEST_ASSERT_EQUAL_CHAR('-', EMPTY_SPACE);
} // end of test case

static void test_validOpponentMarker()
{
    TEST_ASSERT_EQUAL_CHAR('X', getOpponentMarker(AI_MARKER));
    TEST_ASSERT_EQUAL_CHAR('O', getOpponentMarker(PLAYER_MARKER));
} // end of test case

///////////////////////////////////////////////////////////////////////////////
// test_checkGetLegalMoves:
//
// Verify getLegalMoves returns the available and correct legal moves.
//
static void test_checkGetLegalMoves()
{
    std::vector<std::pair<int, int>> legalMoves;
    std::array<std::array<char, 3>, 3> board = {{{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
                                                 {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
                                                 {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE}}};

    //
    // - - -
    // - - -
    // - - -
    legalMoves = getLegalMoves(board);
    TEST_ASSERT_EQUAL(9, legalMoves.size());

    //
    // X - -
    // - - -
    // - - -
    board[0][0] = PLAYER_MARKER;
    legalMoves = getLegalMoves(board);
    TEST_ASSERT_EQUAL(8, legalMoves.size());

    //
    // X - -
    // - O -
    // - - -
    board[1][1] = AI_MARKER;
    legalMoves = getLegalMoves(board);
    TEST_ASSERT_EQUAL(7, legalMoves.size());

    //
    // X - -
    // - O -
    // - - X
    board[2][2] = PLAYER_MARKER;
    legalMoves = getLegalMoves(board);
    TEST_ASSERT_EQUAL(6, legalMoves.size());

    //
    // X - O
    // - O -
    // - - X
    board[0][2] = AI_MARKER;
    legalMoves = getLegalMoves(board);
    TEST_ASSERT_EQUAL(5, legalMoves.size());

    //
    // X - O
    // - O -
    // X - X
    board[2][0] = PLAYER_MARKER;
    legalMoves = getLegalMoves(board);
    TEST_ASSERT_EQUAL(4, legalMoves.size());

    //
    // X - O
    // O O -
    // X - X
    board[1][0] = AI_MARKER;
    legalMoves = getLegalMoves(board);
    TEST_ASSERT_EQUAL(3, legalMoves.size());

    //
    // X - O
    // O O -
    // X X X
    board[2][1] = PLAYER_MARKER;
    legalMoves = getLegalMoves(board);
    TEST_ASSERT_EQUAL(2, legalMoves.size());

    //
    // Make sure the two positions are the expected values returned.
    int numberOfLegalMoves = legalMoves.size();

    for (size_t index = 0; index < legalMoves.size(); ++index)
    {
        std::pair<int, int> currMove = legalMoves[index];
        if (currMove.first == 0)
        {
            --numberOfLegalMoves;
            TEST_ASSERT(currMove.second == 1);
            break;
        }
    }

    for (size_t index = 0; index < legalMoves.size(); ++index)
    {
        std::pair<int, int> currMove = legalMoves[index];
        if (currMove.first == 1)
        {
            --numberOfLegalMoves;
            TEST_ASSERT(currMove.second == 2);
            break;
        }
    }

    TEST_ASSERT(numberOfLegalMoves == 0);
} // end of test case

///////////////////////////////////////////////////////////////////////////////
// test_checkPositionOccupied:
//
// Verify valid and invalid combinations of calls to positionOccupied
// return the expected correct value.
//
static void test_checkPositionOccupied()
{
    //
    // Start with an empty board.
    std::array<std::array<char, 3>, 3> board = {{{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
                                                 {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
                                                 {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE}}};

    //
    // Verify the empty board shows all valid positions as not occupied.
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            TEST_ASSERT_EQUAL(false, positionOccupied(board, {row, col}));
        }
    }

    //
    // Verify setting a single board position will only show occupied
    // for that location and no others.
    for (int orow = 0; orow < 3; ++orow)
    {
        for (int ocol = 0; ocol < 3; ++ocol)
        {
            // Mark the current occupied board location
            board[orow][ocol] = PLAYER_MARKER;
            for (int row = 0; row < 3; ++row)
            {
                for (int col = 0; col < 3; ++col)
                {
                    TEST_ASSERT_EQUAL((orow == row && ocol == col), positionOccupied(board, {row, col}));
                }
            }
            // Reset the current occupied board location
            board[orow][ocol] = EMPTY_SPACE;
        }
    }

    //
    // Verify checking out of bounds board positions shows as being occupied.
    TEST_ASSERT_EQUAL(true, positionOccupied(board, {-1, 0}));
    TEST_ASSERT_EQUAL(true, positionOccupied(board, {0, -1}));
    TEST_ASSERT_EQUAL(true, positionOccupied(board, {-1, -1}));
    TEST_ASSERT_EQUAL(true, positionOccupied(board, {1, 3}));
    TEST_ASSERT_EQUAL(true, positionOccupied(board, {3, 1}));
    TEST_ASSERT_EQUAL(true, positionOccupied(board, {3, 3}));
} // end of test case

///////////////////////////////////////////////////////////////////////////////
// test_checkGetOccupiedPositions:
//
// Verify getOccupiedPositions returns the correct occupied locations.
//
static void test_checkGetOccupiedPositions()
{
    std::vector<std::pair<int, int>> positions;
    std::array<std::array<char, 3>, 3> board = {{{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
                                                 {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
                                                 {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE}}};

    //
    // - - -
    // - - -
    // - - -
    positions = getOccupiedPositions(board, AI_MARKER);
    TEST_ASSERT(positions.size() == 0);
    positions = getOccupiedPositions(board, PLAYER_MARKER);
    TEST_ASSERT(positions.size() == 0);

    //
    // X - -
    // - - -
    // - - -
    board[0][0] = PLAYER_MARKER;
    positions = getOccupiedPositions(board, AI_MARKER);
    TEST_ASSERT(positions.size() == 0);
    positions = getOccupiedPositions(board, PLAYER_MARKER);
    TEST_ASSERT(positions.size() == 1);

    //
    // X - -
    // - O -
    // - - -
    board[1][1] = AI_MARKER;
    positions = getOccupiedPositions(board, AI_MARKER);
    TEST_ASSERT(positions.size() == 1);
    positions = getOccupiedPositions(board, PLAYER_MARKER);
    TEST_ASSERT(positions.size() == 1);

    //
    // X - -
    // - O -
    // - - X
    board[2][2] = PLAYER_MARKER;
    positions = getOccupiedPositions(board, AI_MARKER);
    TEST_ASSERT(positions.size() == 1);
    positions = getOccupiedPositions(board, PLAYER_MARKER);
    TEST_ASSERT(positions.size() == 2);

    //
    // X - O
    // - O -
    // - - X
    board[0][2] = AI_MARKER;
    positions = getOccupiedPositions(board, AI_MARKER);
    TEST_ASSERT(positions.size() == 2);
    positions = getOccupiedPositions(board, PLAYER_MARKER);
    TEST_ASSERT(positions.size() == 2);

    //
    // X - O
    // - O -
    // X - X
    board[2][0] = PLAYER_MARKER;
    positions = getOccupiedPositions(board, AI_MARKER);
    TEST_ASSERT(positions.size() == 2);
    positions = getOccupiedPositions(board, PLAYER_MARKER);
    TEST_ASSERT(positions.size() == 3);

    //
    // X - O
    // O O -
    // X - X
    board[1][0] = AI_MARKER;
    positions = getOccupiedPositions(board, AI_MARKER);
    TEST_ASSERT(positions.size() == 3);
    positions = getOccupiedPositions(board, PLAYER_MARKER);
    TEST_ASSERT(positions.size() == 3);

    //
    // X - O
    // O O -
    // X X X
    board[2][1] = PLAYER_MARKER;
    positions = getOccupiedPositions(board, AI_MARKER);
    TEST_ASSERT(positions.size() == 3);
    positions = getOccupiedPositions(board, PLAYER_MARKER);
    TEST_ASSERT(positions.size() == 4);

    //
    // Verify we are getting the actual positions
    positions = getOccupiedPositions(board, AI_MARKER);
    for (size_t index = 0; index < positions.size(); ++index)
    {
        std::pair<int, int> currPosition = positions[index];
        TEST_ASSERT(board[currPosition.first][currPosition.second] == AI_MARKER);
        board[currPosition.first][currPosition.second] = EMPTY_SPACE;
    }

    positions = getOccupiedPositions(board, PLAYER_MARKER);
    for (size_t index = 0; index < positions.size(); ++index)
    {
        std::pair<int, int> currPosition = positions[index];
        TEST_ASSERT(board[currPosition.first][currPosition.second] == PLAYER_MARKER);
        board[currPosition.first][currPosition.second] = EMPTY_SPACE;
    }

    std::vector<std::pair<int, int>> legalMoves = getLegalMoves(board);
    TEST_ASSERT_EQUAL(9, legalMoves.size());
} // end of test case

///////////////////////////////////////////////////////////////////////////////
// test_checkBoardIsFull:
//
// Verify boardIsFull returns the correct board status.
//
static void test_checkBoardIsFull()
{
    std::array<std::array<char, 3>, 3> board;

    //
    // Empty board is not full
    board = {{{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
              {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
              {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE}}};
    TEST_ASSERT_EQUAL(false, boardIsFull(board));

    //
    // DRAW board with empty position is not full
    board = {{{AI_MARKER, AI_MARKER, PLAYER_MARKER},
              {PLAYER_MARKER, PLAYER_MARKER, AI_MARKER},
              {PLAYER_MARKER, AI_MARKER, EMPTY_SPACE}}};
    TEST_ASSERT_EQUAL(false, boardIsFull(board));

    //
    // AI WIN board with empty position is not full
    board = {{{AI_MARKER, AI_MARKER, AI_MARKER},
              {PLAYER_MARKER, PLAYER_MARKER, EMPTY_SPACE},
              {PLAYER_MARKER, EMPTY_SPACE, EMPTY_SPACE}}};
    TEST_ASSERT_EQUAL(false, boardIsFull(board));

    //
    // PLAYER WIN board with empty position is not full
    board = {{{AI_MARKER, EMPTY_SPACE, PLAYER_MARKER},
              {AI_MARKER, PLAYER_MARKER, EMPTY_SPACE},
              {PLAYER_MARKER, EMPTY_SPACE, EMPTY_SPACE}}};
    TEST_ASSERT_EQUAL(false, boardIsFull(board));

    //
    // Full board is full
    board = {{{AI_MARKER, AI_MARKER, PLAYER_MARKER},
              {PLAYER_MARKER, PLAYER_MARKER, AI_MARKER},
              {PLAYER_MARKER, AI_MARKER, PLAYER_MARKER}}};
    TEST_ASSERT_EQUAL(true, boardIsFull(board));
} // end of test case

///////////////////////////////////////////////////////////////////////////////
// test_checkGameIsWon:
//
// Verify gameIsWon returns the correct game completion status.
//
static void test_checkGameIsWon()
{
    std::vector<std::pair<int, int>> positions;

    // Empty is not a win
    positions = {};
    TEST_ASSERT_EQUAL(false, gameIsWon(positions));

    // Not three in a row is not a win
    positions = {{0, 0}, {0, 1}, {1, 0}, {2, 2}};
    TEST_ASSERT_EQUAL(false, gameIsWon(positions));
    positions = {{0, 0}, {1, 1}};
    TEST_ASSERT_EQUAL(false, gameIsWon(positions));
    positions = {{0, 0}, {1, 1}, {2, 0}, {2, 1}};
    TEST_ASSERT_EQUAL(false, gameIsWon(positions));
    positions = {{0, 0}, {1, 0}, {2, 1}, {2, 2}};
    TEST_ASSERT_EQUAL(false, gameIsWon(positions));

    // Every row is a win
    positions = {{0, 0}, {0, 1}, {0, 2}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));
    positions = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {2, 1}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));

    positions = {{1, 0}, {1, 1}, {1, 2}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));
    positions = {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {2, 1}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));

    positions = {{2, 0}, {2, 1}, {2, 2}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));
    positions = {{0, 0}, {0, 1}, {2, 0}, {2, 1}, {2, 2}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));

    // Every column is a win
    positions = {{0, 0}, {1, 0}, {2, 0}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));
    positions = {{0, 0}, {0, 1}, {1, 0}, {2, 0}, {2, 2}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));

    positions = {{0, 1}, {1, 1}, {2, 1}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));
    positions = {{0, 1}, {0, 2}, {1, 1}, {2, 1}, {2, 2}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));

    positions = {{0, 2}, {1, 2}, {2, 2}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));
    positions = {{0, 0}, {0, 2}, {1, 2}, {2, 0}, {2, 2}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));

    // Every diagonal is a win
    positions = {{0, 0}, {1, 1}, {2, 2}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));
    positions = {{0, 0}, {0, 2}, {1, 0}, {1, 1}, {2, 2}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));

    positions = {{2, 0}, {1, 1}, {0, 2}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));
    positions = {{0, 0}, {2, 0}, {2, 1}, {1, 1}, {0, 2}};
    TEST_ASSERT_EQUAL(true, gameIsWon(positions));
} // end of test case

///////////////////////////////////////////////////////////////////////////////
// test_checkGetBoardState:
//
// Verify getBoard returns the correct state.
//
static void test_checkGetBoardState()
{
    std::array<std::array<char, 3>, 3> board = {{{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
                                                 {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
                                                 {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE}}};

    //
    // - - -
    // - - -
    // - - -
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, AI_MARKER));
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, PLAYER_MARKER));

    //
    // X - -
    // - - -
    // - - -
    board[0][0] = PLAYER_MARKER;
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, AI_MARKER));
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, PLAYER_MARKER));

    //
    // X - -
    // - O -
    // - - -
    board[1][1] = AI_MARKER;
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, AI_MARKER));
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, PLAYER_MARKER));

    //
    // X - -
    // - O -
    // - - X
    board[2][2] = PLAYER_MARKER;
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, AI_MARKER));
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, PLAYER_MARKER));

    //
    // X - O
    // - O -
    // - - X
    board[0][2] = AI_MARKER;
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, AI_MARKER));
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, PLAYER_MARKER));

    //
    // X - O
    // - O -
    // X - X
    board[2][0] = PLAYER_MARKER;
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, AI_MARKER));
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, PLAYER_MARKER));

    //
    // X - O
    // O O -
    // X - X
    board[1][0] = AI_MARKER;
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, AI_MARKER));
    TEST_ASSERT_EQUAL(static_cast<int>(State::DRAW), getBoardState(board, PLAYER_MARKER));

    //
    // X - O
    // O O -
    // X X X
    board[2][1] = PLAYER_MARKER;
    TEST_ASSERT_EQUAL(static_cast<int>(State::LOSS), getBoardState(board, AI_MARKER));
    TEST_ASSERT_EQUAL(static_cast<int>(State::WIN), getBoardState(board, PLAYER_MARKER));
} // end of test case

///////////////////////////////////////////////////////////////////////////////
// test_checkFindBestMove:
//
// Verify findBestMove returns a good next position choice for either player
//
static void test_checkFindBestMove()
{
    std::pair<int, int> nextMove;
    std::array<std::array<char, 3>, 3> board;

    board = {{{PLAYER_MARKER, EMPTY_SPACE, EMPTY_SPACE},
              {EMPTY_SPACE, AI_MARKER, EMPTY_SPACE},
              {EMPTY_SPACE, EMPTY_SPACE, PLAYER_MARKER}}};
    nextMove = findBestMove(board);
    std::cout << "chose " << nextMove.first << "," << nextMove.second << std::endl;
    TEST_ASSERT((nextMove.first == 0 && nextMove.second == 1) ||
                (nextMove.first == 1 && nextMove.second == 0) ||
                (nextMove.first == 1 && nextMove.second == 2) ||
                (nextMove.first == 2 && nextMove.second == 1));

    board = {{{PLAYER_MARKER, AI_MARKER, EMPTY_SPACE},
              {EMPTY_SPACE, AI_MARKER, EMPTY_SPACE},
              {EMPTY_SPACE, EMPTY_SPACE, PLAYER_MARKER}}};
    nextMove = findBestMove(board);
    TEST_ASSERT(nextMove.first == 2 && nextMove.second == 1);
    board[nextMove.first][nextMove.second] = PLAYER_MARKER;

    nextMove = findBestMove(board);
    TEST_ASSERT(nextMove.first == 2 && nextMove.second == 0);
    board[nextMove.first][nextMove.second] = AI_MARKER;

    nextMove = findBestMove(board);
    TEST_ASSERT(nextMove.first == 0 && nextMove.second == 2);
    board[nextMove.first][nextMove.second] = PLAYER_MARKER;

    nextMove = findBestMove(board);
    TEST_ASSERT(nextMove.first == 1 && nextMove.second == 2);
    board[nextMove.first][nextMove.second] = AI_MARKER;

    nextMove = findBestMove(board);
    TEST_ASSERT(nextMove.first == 1 && nextMove.second == 0);
    board[nextMove.first][nextMove.second] = PLAYER_MARKER;

    board = {{{PLAYER_MARKER, AI_MARKER, PLAYER_MARKER},
              {AI_MARKER, AI_MARKER, PLAYER_MARKER},
              {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE}}};
    nextMove = findBestMove(board);
    TEST_ASSERT(nextMove.first == 2 && nextMove.second == 2);

    board = {{{PLAYER_MARKER, AI_MARKER, PLAYER_MARKER},
              {AI_MARKER, AI_MARKER, PLAYER_MARKER},
              {PLAYER_MARKER, EMPTY_SPACE, EMPTY_SPACE}}};
    nextMove = findBestMove(board);
    TEST_ASSERT(nextMove.first == 2 && nextMove.second == 1);
}

///////////////////////////////////////////////////////////////////////////////
// test_checkGameIsDone:
//
// Verify gameIsDone returns the correct game completion status.
//
static void test_checkGameIsDone()
{
    std::array<std::array<char, 3>, 3> board;

    //
    // Empty board is not GameOver
    board = {{{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
              {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
              {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE}}};
    TEST_ASSERT_EQUAL(false, gameIsDone(board));

    //
    // Full board without a winner is GameOver
    board = {{{AI_MARKER, PLAYER_MARKER, AI_MARKER},
              {PLAYER_MARKER, AI_MARKER, PLAYER_MARKER},
              {PLAYER_MARKER, AI_MARKER, PLAYER_MARKER}}};
    TEST_ASSERT_EQUAL(true, gameIsDone(board));

    //
    // Player Win is a GameOver
    board = {{{PLAYER_MARKER, PLAYER_MARKER, PLAYER_MARKER},
              {EMPTY_SPACE, AI_MARKER, EMPTY_SPACE},
              {AI_MARKER, EMPTY_SPACE, EMPTY_SPACE}}};
    TEST_ASSERT_EQUAL(true, gameIsDone(board));

    board = {{{PLAYER_MARKER, AI_MARKER, AI_MARKER},
              {EMPTY_SPACE, PLAYER_MARKER, EMPTY_SPACE},
              {EMPTY_SPACE, EMPTY_SPACE, PLAYER_MARKER}}};
    TEST_ASSERT_EQUAL(true, gameIsDone(board));

    //
    // AI Win is a GameOver
    board = {{{PLAYER_MARKER, EMPTY_SPACE, PLAYER_MARKER},
              {EMPTY_SPACE, PLAYER_MARKER, EMPTY_SPACE},
              {AI_MARKER, AI_MARKER, AI_MARKER}}};
    TEST_ASSERT_EQUAL(true, gameIsDone(board));

    board = {{{PLAYER_MARKER, PLAYER_MARKER, AI_MARKER},
              {EMPTY_SPACE, AI_MARKER, EMPTY_SPACE},
              {AI_MARKER, EMPTY_SPACE, PLAYER_MARKER}}};
    TEST_ASSERT_EQUAL(true, gameIsDone(board));
} // end of test case

//
//  here main is used as the test runner
//
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_validGridChar);
    RUN_TEST(test_validOpponentMarker);
    RUN_TEST(test_checkGetLegalMoves);
    RUN_TEST(test_checkPositionOccupied);
    RUN_TEST(test_checkGetOccupiedPositions);
    RUN_TEST(test_checkBoardIsFull);
    RUN_TEST(test_checkGameIsWon);
    RUN_TEST(test_checkGetBoardState);
    RUN_TEST(test_checkFindBestMove);
    RUN_TEST(test_checkGameIsDone);

    return UNITY_END();
} // end of function main
