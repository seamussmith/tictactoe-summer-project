#ifndef _BOARDENUMS_
#define _BOARDENUMS_

// * This namespace holds enum classes that are used to store the state of a tictactoe board
namespace BoardEnums
{
    enum class SpaceState { Empty, X, O }; // 0, 1, 2
    enum class PlayerTurnState { X, O }; // 0, 1
    enum class VictoryState { Nobody, X, O, Draw }; // 0, 1, 2, 3
    enum class MoveResult { Success, SpaceTaken, MoveOutOfRange, BoardAlreadyWon }; // 0, 1, 2, 3
}

#endif
