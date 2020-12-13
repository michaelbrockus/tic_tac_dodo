//
// file: program.cpp
// author: Michael Brockus
// gmail: <michaelbrockus@gmail.com>
//
#include "program.hpp"
#include "game.hpp"
#include <iostream>
#include <cstdlib>

//
// foundation of the program and related
// application logic must be implemented
// in the foundation.
//
int foundation(void)
{
    std::array<std::array<char, 3>, 3> board = {{{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
                                                 {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
                                                 {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE}}};

    std::cout << "********************************\n\n\tTic Tac Toe Dodo\n\n********************************" << std::endl
              << std::endl;
    std::cout << "Player = X\t Dodo = O" << std::endl
              << std::endl;

    while (!gameIsDone(board))
    {
        int row, col;
        std::cout << "Row play: ";
        std::cin >> row;
        std::cout << "Col play: ";
        std::cin >> col;
        std::cout << std::endl
                  << std::endl;

        if (positionOccupied(board, {row, col}))
        {
            std::cout << "The position (" << row << ", " << col << ") is occupied. Try another one..." << std::endl;
            continue;
        } // end if
        else
        {
            board[row][col] = PLAYER_MARKER;
        } // end else

        std::pair<int, int> aiMove = findBestMove(board);
        board[aiMove.first][aiMove.second] = AI_MARKER;

        printBoard(board);
    } // end while

    std::cout << "********** GAME OVER **********" << std::endl
              << std::endl;
    int playerState = getBoardState(board, PLAYER_MARKER);
    std::cout << "PLAYER ";
    printGameState(playerState);
    return EXIT_SUCCESS;
} // end of function foundation
