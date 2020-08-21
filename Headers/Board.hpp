#ifndef _BOARDCLASS_
#define _BOARDCLASS_

#include <iostream>
#include <array>
#include <cmath>

#include "BoardEnums.hpp"

// * Object that represents a tictactoe board. Now with templates!
template<unsigned long long Size = 3>
class Board
{
private:
    std::array<std::array<BoardEnums::SpaceState, Size>, Size> CurrentBoard;
    BoardEnums::VictoryState CurrentVictoryStatus;
public:
    unsigned long long BoardSize;
    BoardEnums::PlayerTurnState Turn;
    Board()
    {
        BoardSize = Size;
        CurrentVictoryStatus = BoardEnums::VictoryState::Nobody;
        for (int i = 0; i != Size; ++i)
        {
            for (int j = 0; j != Size; ++j)
            {
                CurrentBoard[i][j] = BoardEnums::SpaceState::Empty; // Set every space of the CurrentBoard array to SpaceState::Empty
            }
        }
        Turn = BoardEnums::PlayerTurnState::X;
    }
    // ? Maybe this function could be renamed to something more descriptive.
    // NOTE: If this function returns MoveResult::Success, it will change the turn state to the opposite player's turn.
    BoardEnums::MoveResult SetSpace(int space) // Takes int from 1 to <Size>. Returns success state of move.
    {
        if (CurrentVictoryStatus != BoardEnums::VictoryState::Nobody)
            return BoardEnums::MoveResult::BoardAlreadyWon;
        if (!((space <= Size * Size) and (space >= 1)))
            return BoardEnums::MoveResult::MoveOutOfRange;
        unsigned long long row = floor((space - 1) / Size); // Convert inputted number to 2d array indexes
        unsigned long long col = (space - 1) % Size;
        if (CurrentBoard[row][col] != BoardEnums::SpaceState::Empty) // Check if requested space is empty
            return BoardEnums::MoveResult::SpaceTaken;
        if (Turn == BoardEnums::PlayerTurnState::X) // Set state of space to the player of turn thing uhh how do i write comment
            CurrentBoard[row][col] = BoardEnums::SpaceState::X;
        else
            CurrentBoard[row][col] = BoardEnums::SpaceState::O;
        Turn == BoardEnums::PlayerTurnState::X ? Turn = BoardEnums::PlayerTurnState::O : Turn = BoardEnums::PlayerTurnState::X; // Set player turn state to other player
        return BoardEnums::MoveResult::Success;
    }
    // * Just draws the board to the console. Better than manually typing the loop later amirite??? heh heh ehh
    void DrawBoard()
    {
        for (auto i : CurrentBoard)
        {
            for (auto j : i)
            {
                switch (j)
                {
                case BoardEnums::SpaceState::Empty:
                    std::cout << '_';
                    break;
                case BoardEnums::SpaceState::X:
                    std::cout << 'X';
                    break;
                case BoardEnums::SpaceState::O:
                    std::cout << 'O';
                    break;
                default:
                    std::cout << "This shouldnt happen...";
                    break;
                }
                std::cout << ' ';
            }
            std::cout << std::endl;
        }
    }
    // * Return VictoryState. If victory state is not Board::VictoryState::Nobody, this returns CurrentVictoryStatus without doing any victory check, making this function act like a getter
    BoardEnums::VictoryState CheckForVictor()
    {
        if (CurrentVictoryStatus != BoardEnums::VictoryState::Nobody)
            return CurrentVictoryStatus;
        // Check for horizontal victory
        for (int i = 0; i != Size; ++i)
        {
            BoardEnums::SpaceState probableVictor = CurrentBoard[i][0];
            bool isVictor = true;
            for (int j = 0; j != CurrentBoard.size(); ++j)
            {
                if (CurrentBoard[i][j] != probableVictor)
                {
                    isVictor = false;
                    break; 
                }
            }
            if (isVictor)
            {
                if (probableVictor == BoardEnums::SpaceState::X)
                {
                    CurrentVictoryStatus = BoardEnums::VictoryState::X;
                    return BoardEnums::VictoryState::X;
                }
                else if (probableVictor == BoardEnums::SpaceState::O)
                {
                    CurrentVictoryStatus = BoardEnums::VictoryState::O;
                    return BoardEnums::VictoryState::O;
                }
            }
        }
        // Check for vertical victory
        for (int i = 0; i != Size; ++i)
        {
            BoardEnums::SpaceState probableVictor = CurrentBoard[0][i];
            bool isVictor = true;
            for (int j = 0; j != CurrentBoard.size(); ++j)
            {
                if (CurrentBoard[j][i] != probableVictor)
                {
                    isVictor = false;
                    break;
                }
            }
            if (isVictor)
            {
                if (probableVictor == BoardEnums::SpaceState::X)
                {
                    CurrentVictoryStatus = BoardEnums::VictoryState::X;
                    return BoardEnums::VictoryState::X;
                }
                else if (probableVictor == BoardEnums::SpaceState::O)
                {
                    CurrentVictoryStatus = BoardEnums::VictoryState::O;
                    return BoardEnums::VictoryState::O;
                }
            }
        }
        // * Check for diagonal victory
        {
            BoardEnums::SpaceState probableVictor = CurrentBoard[0][0];
            bool isVictor = true;
            for (int i = 0; i != Size; ++i)
            {
                if (CurrentBoard[i][i] != probableVictor)
                {
                    isVictor = false;
                    break;
                }
            }
            if (isVictor)
            {
                if (probableVictor == BoardEnums::SpaceState::X)
                {
                    CurrentVictoryStatus = BoardEnums::VictoryState::X;
                    return BoardEnums::VictoryState::X;
                }
                else if (probableVictor == BoardEnums::SpaceState::O)
                {
                    CurrentVictoryStatus = BoardEnums::VictoryState::O;
                    return BoardEnums::VictoryState::O;
                }
            }
        }
        {
            BoardEnums::SpaceState probableVictor = CurrentBoard[0][Size-1];
            bool isVictor = true;
            for (int i = 0, j = Size-1; i != Size; ++i, --j)
            {
                if (CurrentBoard[i][j] != probableVictor)
                {
                    isVictor = false;
                    break;
                }
            }
            if (isVictor)
            {
                if (probableVictor == BoardEnums::SpaceState::X)
                {
                    CurrentVictoryStatus = BoardEnums::VictoryState::X;
                    return BoardEnums::VictoryState::X;
                }
                else if (probableVictor == BoardEnums::SpaceState::O)
                {
                    CurrentVictoryStatus = BoardEnums::VictoryState::O;
                    return BoardEnums::VictoryState::O;
                }
            }
        }
        // If no victory condition is met and all spaces are filled, return VictoryState::Draw
        {
            bool foundEmptySpace = false;
            for (int i = 0; i != Size; ++i)
            {
                for (int j = 0; j != Size; ++j)
                {
                    if (CurrentBoard[i][j] == BoardEnums::SpaceState::Empty)
                    {
                        foundEmptySpace = true;
                        break;
                    }
                }
                if (foundEmptySpace)
                    break;
            }
            if (!foundEmptySpace)
            {
                CurrentVictoryStatus = BoardEnums::VictoryState::Draw;
                return BoardEnums::VictoryState::Draw;
            }
        }
        return BoardEnums::VictoryState::Nobody;
    }
    // * Clears the board and sets the turn state to X
    void ClearBoard()
    {
        for (int i = 0; i != Size; ++i)
        {
            for (int j = 0; j != Size; ++j)
            {
                CurrentBoard[i][j] = BoardEnums::SpaceState::Empty;
            }
        }
        CurrentVictoryStatus = BoardEnums::VictoryState::Nobody;
        Turn = BoardEnums::PlayerTurnState::X;
    }
    // * Get turn as a string. ONLY USE THIS FOR OUTPUTTING TO THE CONSOLE!
    std::string GetTurn()
    {
        switch (Turn)
        {
        case BoardEnums::PlayerTurnState::X:
            return "X";
            break;
        case BoardEnums::PlayerTurnState::O:
            return "O";
            break;
        }
        return "Error!";
    }
    // * Simulates a turn and returns the success of the would-be move without modifying the board.
    BoardEnums::MoveResult SimulateTurn(int space) // Takes int from 1 to <Size>
    {
        if (CurrentVictoryStatus != BoardEnums::VictoryState::Nobody)
            return BoardEnums::MoveResult::BoardAlreadyWon;
        if (!((space <= Size * Size) and (space >= 1)))
            return BoardEnums::MoveResult::MoveOutOfRange;
        unsigned long long row = floor((space - 1) / Size); // Convert inputted number to 2d array indexes
        unsigned long long col = (space - 1) % Size;
        if (CurrentBoard[row][col] != BoardEnums::SpaceState::Empty) // Check if requested space is empty
            return BoardEnums::MoveResult::SpaceTaken;
        return BoardEnums::MoveResult::Success;
    }
    std::array<std::array<BoardEnums::SpaceState, Size>, Size> GetBoard()
    {
        return CurrentBoard;
    }
};
#endif
