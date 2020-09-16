#include <iostream>
#include <memory>
#include <chrono>
#include <boost/lexical_cast.hpp>
#include <boost/lexical_cast/try_lexical_convert.hpp>

#define BOARDSIZE 3 // * Want bigger or smaller boards? Change this macro!

#include "Headers/reliablerand.hpp"
//#include "Headers/tparse.hpp"

#include "Headers/BoardEnums.hpp"
#include "Headers/Board.hpp"
#include "Headers/CassieBot.hpp"

bool Playing = true;
bool EnemyIsBot = false;
std::unique_ptr<Board<BOARDSIZE>> TicTacToeBoard = std::make_unique<Board<BOARDSIZE>>();
std::unique_ptr<CassieBot<Board<BOARDSIZE>>> Bot = std::make_unique<CassieBot<Board<BOARDSIZE>>>();

using boost::conversion::try_lexical_convert;

void WinnerDialogue(BoardEnums::VictoryState &victoryState)
{
    if (EnemyIsBot)
    {
        switch (victoryState) // Print text for victory state
        {
        case BoardEnums::VictoryState::Draw:
            std::cout << "The game has ended in a draw!\n";
            break;
        case BoardEnums::VictoryState::X:
            std::cout << (Bot->Represents == BoardEnums::PlayerTurnState::X ? "CassieBot Wins!\n" : "Player X wins!\n");
            break;
        case BoardEnums::VictoryState::O:
            std::cout << (Bot->Represents == BoardEnums::PlayerTurnState::O ? "CassieBot Wins!\n" : "Player O wins!\n");
            break;
        case BoardEnums::VictoryState::Nobody:
            std::cout << "Nobody wins! Wait that shouldn't have happened...\n";
            break;
        }
    }
    else
    {
        switch (victoryState) // Print text for victory state
        {
        case BoardEnums::VictoryState::Draw:
            std::cout << "The game has ended in a draw!\n";
            break;
        case BoardEnums::VictoryState::X:
            std::cout << "Player X wins!\n";
            break;
        case BoardEnums::VictoryState::O:
            std::cout << "Player O wins!\n";
            break;
        case BoardEnums::VictoryState::Nobody:
            std::cout << "Nobody wins! Wait that shouldn't have happened...\n";
            break;
        }
    }
}

void BotLoop()
{
    BoardEnums::VictoryState victoryState = BoardEnums::VictoryState::Nobody;
    while (victoryState == BoardEnums::VictoryState::Nobody) // While there is no victor...
    {
        std::cout << std::endl;
        TicTacToeBoard->DrawBoard();
        int move = 0;
        if (TicTacToeBoard->Turn != Bot->Represents) // Check if it is the player's turn
        {
            std::string userInput;
            std::cout << "It is Player " << TicTacToeBoard->GetTurn() << "'s turn: "; // Get player's move
            std::getline(std::cin, userInput);
            // Below are multiple checks that make sure the player's inputs are valid. It will run Board->SetSpace() until it returns a success state.
            while(not try_lexical_convert(userInput, move))
            {
                std::cout << "Please enter a valid number, Player " << TicTacToeBoard->GetTurn() << ": ";
                std::getline(std::cin, userInput);
            }
            while (TicTacToeBoard->SetSpace(move) != BoardEnums::MoveResult::Success)
            {
                switch (TicTacToeBoard->SetSpace(move))
                {
                case BoardEnums::MoveResult::MoveOutOfRange:
                    std::cout << "Please enter a number between 1 and 9, Player " << TicTacToeBoard->GetTurn() << ": ";
                    break;
                case BoardEnums::MoveResult::SpaceTaken:
                    std::cout << "Please choose an empty space, Player " << TicTacToeBoard->GetTurn() << ": ";
                    break;
                }
                std::getline(std::cin, userInput);
                while(not try_lexical_convert(userInput, move))
                {
                    std::cout << "Please enter a valid number, Player " << TicTacToeBoard->GetTurn() << ": ";
                    std::getline(std::cin, userInput);
                }
            }
        }
        else // This represents the bot's turn
        {
            Bot->Vision = *TicTacToeBoard; // Update the bot's view of the board
            std::cout << "It is Player " << TicTacToeBoard->GetTurn() << "'s turn" << std::endl;
            std::cout << "CassieBot: Hmmm...\n";
            auto thinkTime = std::chrono::steady_clock::now();
            int thinkEnd = relrand::genint(500, 1000); // Freeze program for a random amount of miliseconds to make it look like the bot is thinking.
            while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - thinkTime) < std::chrono::milliseconds(thinkEnd));
            while (TicTacToeBoard->SetSpace(move) != BoardEnums::MoveResult::Success) // Force the bot to choose another space if it makes an invalid move (Not desired)
            {
                move = Bot->MakeMove();
            }
            std::cout << "CassieBot: I choose space " << move << "!" << std::endl;
        }
        victoryState = TicTacToeBoard->CheckForVictor();
    }
    std::cout << std::endl;
    TicTacToeBoard->DrawBoard();
    WinnerDialogue(victoryState);
}

void PvPLoop()
{
    BoardEnums::VictoryState victoryState = BoardEnums::VictoryState::Nobody;
    while (victoryState == BoardEnums::VictoryState::Nobody) // While there is no victor...
    {
        std::cout << std::endl;
        TicTacToeBoard->DrawBoard();
        int move = 0;
        std::string userInput;
        std::cout << "It is Player " << TicTacToeBoard->GetTurn() << "'s turn: "; // Get player's move
        std::getline(std::cin, userInput);
        // Below are multiple checks that make sure the player's inputs are valid
        while(not try_lexical_convert(userInput, move))
        {
            std::cout << "Please enter a valid number, Player " << TicTacToeBoard->GetTurn() << ": ";
            std::getline(std::cin, userInput);
        }
        while (TicTacToeBoard->SetSpace(move) != BoardEnums::MoveResult::Success)
        {
            switch (TicTacToeBoard->SetSpace(move))
            {
            case BoardEnums::MoveResult::MoveOutOfRange:
                std::cout << "Please enter a number between 1 and 9, Player " << TicTacToeBoard->GetTurn() << ": ";
                break;
            case BoardEnums::MoveResult::SpaceTaken:
                std::cout << "Please choose an empty space, Player " << TicTacToeBoard->GetTurn() << ": ";
                break;
            }
            std::getline(std::cin, userInput);
            while(not try_lexical_convert(userInput, move))
            {
                std::cout << "Please enter a valid number, Player " << TicTacToeBoard->GetTurn() << ": ";
                std::getline(std::cin, userInput);
            }
        }
        victoryState = TicTacToeBoard->CheckForVictor();
    }
    std::cout << std::endl;
    TicTacToeBoard->DrawBoard();
    WinnerDialogue(victoryState);
}

void PlayAgainPrompt()
{
    std::string playerResponse;
    std::cout << "Play another game? y/n: "; // Ask player if they want to play another game
    std::getline(std::cin, playerResponse);
    while (playerResponse != "y" and playerResponse != "n")
    {
        std::cout << "Please enter y or n: ";
        std::getline(std::cin, playerResponse);
    }
    if (playerResponse == "y")
    {
        std::cout << (EnemyIsBot ? "CassieBot: Lets give it another go!\n" : "Resetting board...\n");
        TicTacToeBoard->ClearBoard();
    }
    else
    {
        Playing = false;
    }
}

void Setup()
{
    Bot->Vision = *TicTacToeBoard;
    std::cout << "Welcome to my TicTacToe Game!\n"
        << "Enter a number from 1 to 9 to choose a space\n"
        << "Would you like to play with a bot? y/n: ";
    std::string playerResponse;
    std::getline(std::cin, playerResponse);
    while (playerResponse != "y" and playerResponse != "n")
    {
        std::cout << "Please enter y or n: ";
        std::getline(std::cin, playerResponse);
    }
    if (playerResponse == "y")
    {
        EnemyIsBot = true;
        std::cout << "CassieBot: Lets play!" << std::endl;
    }
    if (EnemyIsBot)
    {
        std::cout << "Would you like play as Player X or Player O? x/o: ";
        std::string playerResponse;
        std::getline(std::cin, playerResponse);
        while (!(playerResponse == "x") and !(playerResponse == "o"))
        {
            std::cout << "Please enter x or o: ";
            std::getline(std::cin, playerResponse);
        }
        Bot->Represents = (playerResponse == "x" ? BoardEnums::PlayerTurnState::O : BoardEnums::PlayerTurnState::X);
    }
}

int main()
{
    Setup();
    while (Playing)
    {
        if (EnemyIsBot)
            BotLoop();
        else
            PvPLoop();
        PlayAgainPrompt();
    }
}
