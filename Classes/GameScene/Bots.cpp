//
//  Bots.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-08-03.
//
//

#include "Bots.hpp"

#include <time.h>

USING_NS_CC;

static const int BOT_THINKING_TIME = 2;

Bots::Bots()
{
    
}

Bots::~Bots()
{
    
}

bool Bots::init()
{
    if(!Node::init()) return false;
    
    if(UserDefault::getInstance()->getStringForKey("mode") == "easy"){
        _botThinkingTime = 1.0;
        _mode = "easy";
    }
    else if(UserDefault::getInstance()->getStringForKey("mode") == "medium"){
        _botThinkingTime = 2.0;
        _mode = "medium";
    }
    else if(UserDefault::getInstance()->getStringForKey("mode") == "hard"){
        _botThinkingTime = 3.0;
        _mode = "hard";
    }
    else if(UserDefault::getInstance()->getStringForKey("mode") == "extreme"){
        _botThinkingTime = 4.0;
        _mode = "extreme";
    }
    else{
        _botThinkingTime = 2.5;
    }

    
    return true;
}

// randomBot takes all the next possible moves and returns a random move
std::pair<int, int> Bots::randomBot(Board* board)
{
    clock_t timeStart = clock();
    std::vector<std::pair<int, int>> availableMoves = board->getAvailableMoves();
    
    int numOfAvailableMoves = (int)availableMoves.size();
    int randomIndex = random(0, numOfAvailableMoves - 1);
    return availableMoves[randomIndex];
}

// MonteCarloBot uses a Monte Carlo Search Tree to look for the best possible move.
// The function will use TIME_TO_THINK (globally defined) seconds to try to decide
// the "best" next move it can make. A win counts as +1, a tie as 0 and loses as -1,
// each divided with the number of moves it took to reach that state. This means moves
// where few following moves lead to a win are strongly favored, while moves that within
// a few moves will lead to a loss are strongly disfavored.
std::pair<int, int> Bots::monteCarloBot(Board* board, Block::Player playerNext)
{
    // start timer
    float timer = 0;
    clock_t timeStart;
    timeStart = clock();
    
    // make vector of available moves
    std::vector<std::pair<int, int>> availableMoves = board->getAvailableMoves();

    
    std::map<std::pair<int, int>, float> ties;
    std::map<std::pair<int, int>, float> wins;
    std::map<std::pair<int, int>, float> weightedWins;
    std::map<std::pair<int, int>, float> losses;
    std::map<std::pair<int, int>, float> weightedLosses;
    
    // initialize all to 0
    for(auto it = availableMoves.begin(); it != availableMoves.end(); it++)
    {
        ties[(*it)] = 0;
        wins[(*it)] = 0;
        weightedWins[(*it)] = 0;
        losses[(*it)] = 0;
        weightedLosses[(*it)] = 0;
    }
    int gamesPlayed = 0;
    
    do {
        // Until we run out of time...
        for(auto it = availableMoves.begin(); it != availableMoves.end(); it++){
            gamesPlayed += 1;
            
            // Keep track of whose turn it is
            Block::Player player = playerNext; // bot is player 2
            
            // Keep track of how many moves were needed to end the game
            int movesUntilGameEnded = 0;
            
            // Create a copy of the board
            
            Board* localBoard = board->clone();
            std::pair<int, int> move = (*it);
            
            if(localBoard->makeMoveFromTile(move, player)){
                if(localBoard->checkWin()){
                    return move;
                }
                if(player == Block::Player::PLAYER1){
                    player = Block::Player::PLAYER2;
                }
                else if(player == Block::Player::PLAYER2){
                    player = Block::Player::PLAYER1;
                }
            }
            else{
                CCLOG("CANT MAKE MOVE");
                continue;
            }
            
            CCLOG("new game");
            
            // Simulate the rest of the game with two RandomBots.
            while(!localBoard->checkWin()) { // useless condition since the while loop should break before
                
                movesUntilGameEnded += 1;
                
                std::pair<int, int> nextMove = randomBot(localBoard);
                
                if(localBoard->makeMoveFromTile(nextMove, player)){
                    if(localBoard->checkWin())
                    {
                        if(player == playerNext){ // bot
                            wins[move] += 1.0;
                            weightedWins[move] += (1.0 / movesUntilGameEnded);
                            CCLOG("Bot wins for move %d, %d", move.first, move.second);
                            CCLOG("Moves it took to win: %d", movesUntilGameEnded);
                            CCLOG("Bot weighted win: %f", (1.0 / movesUntilGameEnded));
                        }
                        else { // user
                            losses[move] += 1.0;
                            weightedLosses[move] += (1.0 / movesUntilGameEnded);
                            CCLOG("User wins for move %d, %d", move.first, move.second);
                            CCLOG("Moves it took to win: %d", movesUntilGameEnded);
                            CCLOG("User weighted win: %f", (1.0 / movesUntilGameEnded));
                        }
                        break;
                    }
                    
                    if(localBoard->checkDraw()) {
                        ties[move] += 1.0;
                        CCLOG("Draw for move %d, %d", move.first, move.second);
                        break;
                    }
                    
                    if(player == Block::Player::PLAYER1){
                        player = Block::Player::PLAYER2;
                    }
                    else if(player == Block::Player::PLAYER2){
                        player = Block::Player::PLAYER1;
                    }
                }
            }
        }
        clock_t timeEnd = clock();
        timer = (timeEnd - timeStart) / CLOCKS_PER_SEC;
    } while(timer < BOT_THINKING_TIME);
    
    CCLOG("BotThinkingTime: %f", _botThinkingTime);
    CCLOG("Timer: %f", timer);
    CCLOG("MonteCarloBot had time to play %d simulated games using %d valid moves (~%lu per valid move) before running out of time!", gamesPlayed, availableMoves.size(), (gamesPlayed / availableMoves.size()));
    
    float bestScore = -10000.0;
    std::pair<int, int> bestMove = std::make_pair(-1, -1);
    
    for(auto it = availableMoves.begin(); it != availableMoves.end(); it++)
    {
        std::pair<int, int> move = (*it);
        CCLOG("For move %d, %d: wins %f, weighted wins: %f, losses: %f, weighted loses: %f, ties: %f", move.first, move.second, wins[move], weightedWins[move], losses[move], weightedLosses[move], ties[move]);
        float score = (weightedWins[move] - (weightedLosses[move])) / (wins[move] + losses[move] + ties[move]);
        //CCLOG("Score: %f", score);
        if( score > bestScore ) {
            bestScore = score;
            bestMove = move;
        }
    }
    
    return bestMove;
}