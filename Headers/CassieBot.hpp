#ifndef _CASSIEBOT_
#define _CASSIEBOT_

#include <memory> // * Maybe heap allocation will help out with runtime stack overflow errors on bigger boards... - Past Self
                  // * Nope! In fact, I think it made it worse. - Future Self
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
    void UpdateVision(BoardType newBoard)
    {
        Vision = newBoard;
    }
    void SetPlayer(BoardEnums::PlayerTurnState Represents)
    {
        this->Represents = Represents;
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
                std::unique_ptr<BoardType> itterationCheck = std::make_unique<BoardType>(Vision);
                itterationCheck->SetSpace(move);
                if ((int)itterationCheck->CheckForVictor())
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
                std::unique_ptr<BoardType> itterationCheck = std::make_unique<BoardType>(Vision);
                itterationCheck->Turn = (Represents == BoardEnums::PlayerTurnState::X ? BoardEnums::PlayerTurnState::O : BoardEnums::PlayerTurnState::X); // Set board to opposite player's turn
                itterationCheck->SetSpace(move);
                if ((int)itterationCheck->CheckForVictor())
                {
                    return move;
                }
            }
        }
        // If a victory state isnt possible, choose a random empty spot
        move = 0;
        std::unique_ptr<BoardType> itterationCheck = std::make_unique<BoardType>(Vision);
        while (itterationCheck->SetSpace(move) != BoardEnums::MoveResult::Success)
        {
            itterationCheck = std::make_unique<BoardType>(Vision);
            move = relrand::genint<unsigned long long>(1, Vision.BoardSize * Vision.BoardSize); // in case of this function being an unreliable piece of garbage, replace with: rand() % Vision.BoardSize * Vision.BoardSize + 1
        }
        return move;
    }
};

#endif
