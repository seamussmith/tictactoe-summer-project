#ifndef _CASSIEBOT_
#define _CASSIEBOT_
#include <array>
#include "reliablerand.hpp"
#include "Board.hpp"
#include "BoardEnums.hpp"

template<class BoardType>
class CassieBot
{
private:
public:
    BoardType Vision;
    BoardEnums::PlayerTurnState Represents;
    CassieBot()
    {
    }
    int MakeMove()
    {
        int move = 0;
        // Attempt to find an immediate victory state
        for (int i = 0; i != Vision.BoardSize; ++i) // Find victory state for self
        {
            for (int j = 0; j != Vision.BoardSize; ++j)
            {
                ++move;
                BoardType itterationCheck = Vision;
                itterationCheck.SetSpace(move);
                if ((int)itterationCheck.CheckForVictor())
                {
                    return move;
                }
            }
        }
        move = 0;
        for (int i = 0; i != Vision.BoardSize; ++i) // Find victory state for player
        {
            for (int j = 0; j != Vision.BoardSize; ++j)
            {
                ++move;
                BoardType itterationCheck = Vision;
                itterationCheck.Turn = (Represents == BoardEnums::PlayerTurnState::X ? BoardEnums::PlayerTurnState::O : BoardEnums::PlayerTurnState::X); // Set board to opposite player's turn
                itterationCheck.SetSpace(move);
                if ((int)itterationCheck.CheckForVictor())
                {
                    return move;
                }
            }
        }
        // If a victory state isnt possible, choose a random empty spot
        move = 0;
        BoardType itterationCheck = Vision;
        while (itterationCheck.SetSpace(move) != BoardEnums::MoveResult::Success)
        {
            itterationCheck = Vision;
            move = relrand::genint<unsigned long long>(1, Vision.BoardSize * Vision.BoardSize);
        }
        return move;
    }
};

#endif
