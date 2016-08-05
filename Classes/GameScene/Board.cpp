//
//  Board.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#include "Board.hpp"

#include "BigTile.hpp"

USING_NS_CC;

static const int NUM_OF_TILES = 9;

Board::Board()
{
    _board = NULL;
    _currentTile = std::make_pair(0-1, -1);
    _currentBlock = NULL;
    _availableBigTiles.clear();
    _tileMap.clear();
}

Board::~Board()
{
    
}

bool Board::init()
{
    if(!Node::init()) return false;
    
    // place board
    _board = Sprite::create("board_big.png");
    Size size = _board->getContentSize();
    _board->setPosition(Vec2(size.width / 2.0, size.height / 2.0));
    this->addChild(_board);
    this->setContentSize(size);
    this->setAnchorPoint(Vec2(0.5, 0.5));
    
    // initialize big tiles
    for(int i = 0; i < NUM_OF_TILES; i++){
        BigTile* tile = BigTile::create(i);
        Size tileSize = tile->getContentSize();
        this->addChild(tile);
        Vec2 position = Vec2(0, 0);
        if(i == 0){
            position = Vec2(tileSize.width / 2.0, tileSize.height / 2.0 * 5);
        }
        else if(i == 1){
            position = Vec2(tileSize.width / 2.0 * 3, tileSize.height / 2.0 * 5);
        }
        else if(i == 2){
            position = Vec2(tileSize.width / 2.0 * 5, tileSize.height / 2.0 * 5);
        }
        else if(i == 3){
            position = Vec2(tileSize.width / 2.0, tileSize.height / 2.0 * 3);
        }
        else if(i == 4){
            position = Vec2(tileSize.width / 2.0 * 3, tileSize.height / 2.0 * 3);
        }
        else if( i == 5){
            position = Vec2(tileSize.width / 2.0 * 5, tileSize.height / 2.0 * 3);
        }
        else if (i == 6){
            position = Vec2(tileSize.width / 2.0, tileSize.height / 2.0);
        }
        else if ( i == 7){
            position = Vec2(tileSize.width / 2.0 * 3, tileSize.height / 2.0);
        }
        else if ( i == 8){
            position = Vec2(tileSize.width / 2.0 * 5, tileSize.height / 2.0);
        }
        tile->setPosition(position);
        _bigTileList[i] = tile;
    }
    
    // put all big tiles in available big tile vector initially
    for( int i = 0; i < NUM_OF_TILES; i++)
    {
        _availableBigTiles.push_back(i);
    }
    return true;
}

Board* Board::clone()
{
    Board* newBoard = Board::create();
    //newBoard->_board = NULL;
    //newBoard->_currentTile = _currentTile;
    //newBoard->_currentBlock = NULL;
    newBoard->setAvailableBigTiles(_availableBigTiles);
    newBoard->setTileMap(_tileMap);
//    for(int i = 0; i < 9; i++){
//        newBoard->_bigTileList[i] = _bigTileList[i];
//    }
    for(int i = 0; i < 9; i++){
        newBoard->_bigTileList[i] = BigTile::create(i);
        newBoard->_bigTileList[i]->setDone(this->getBigTileList()[i]->getDone());
    }
    return newBoard;
}

std::vector<std::pair<int, int>> Board::getAvailableMoves()
{
    std::vector<std::pair<int, int>> availableMoves;
    
    for(auto it = _availableBigTiles.begin(); it != _availableBigTiles.end(); it++)
    {
        int numOfTiles = 9;
        for(int i = 0; i < numOfTiles; i++)
        {
            std::pair<int, int> tile = std::make_pair((*it), i);
            if(_tileMap.find(tile) == _tileMap.end())
            {
                availableMoves.push_back(tile);
            }
        }
    }
    
    return availableMoves;

}

void Board::resetAvailableBigTiles(int nextSmallTileNum)
{
    // clear current available big tile list
    _availableBigTiles.clear();
    
    BigTile* bigTile = _bigTileList[nextSmallTileNum];
    
    // check if next small tile num is done
    if(!bigTile->getDone())
    {
        _availableBigTiles.push_back(nextSmallTileNum);
    }
    else
    {
        int numOfTiles = 9;
        for(int i = 0; i < numOfTiles; i++)
        {
            bigTile = _bigTileList[i];
            if(!bigTile->getDone())
            {
                _availableBigTiles.push_back(i);
            }
        }
    }
    
    // reset the yellowbg of the big tiles
    // set all of the yellowbg visiblity to false first
    int numOfTiles = 9;
    for(int i = 0; i < numOfTiles; i++)
    {
        bigTile = _bigTileList[i];
        Sprite* yellowbg = bigTile->getYellowBG();
        yellowbg->setVisible(false);
    }
    // then set the ones that are in the available big tile vector as visible
    for(auto it = _availableBigTiles.begin(); it != _availableBigTiles.end(); it++)
    {
        bigTile = _bigTileList[(*it)];
        Sprite* yellowbg = bigTile->getYellowBG();
        yellowbg->setVisible(true);
    }

}

bool Board::makeMoveFromTouch(Touch* touch, Block::Player player)
{
    Vec2 touchBoardBegan = _board->convertTouchToNodeSpace(touch);
    // find which big tile user is touching
    int bigTileNum = -1;
    BigTile* bigTile = NULL;
    for(auto it = _availableBigTiles.begin(); it != _availableBigTiles.end(); it++){
        bigTile = _bigTileList[(*it)];
        if(bigTile->getBoundingBox().containsPoint(touchBoardBegan)){
            bigTileNum =  bigTile->getBigTileNum();
            break;
        }
    }
    
    // prevent bugs
    if(bigTileNum == -1 ) {
        return false;
    }
    // find which small tile user is touching
    SmallTile** smallTileList = bigTile->getSmallTileList();
    Vec2 touchBigTileBegan = bigTile->convertTouchToNodeSpace(touch);
    int smallTileNum = -1;
    SmallTile* smallTile = NULL;
    for(int i = 0; i < NUM_OF_TILES; i++){
        smallTile = smallTileList[i];
        if(smallTile->getBoundingBox().containsPoint(touchBigTileBegan)){
            smallTileNum = smallTile->getSmallTileNum();
            break;
        }
    }
    
    // prevent bugs
    if(smallTileNum == -1 ) {
        return false;
    }
    
    _currentTile = std::make_pair(bigTileNum, smallTileNum);
    if(makeMoveFromTile(_currentTile, player))
    {
        return true;
    }

    return false;
}

bool Board::makeMoveFromTile(std::pair<int, int> tile, Block::Player player)
{
    // check if it is already in the map
    
    if(_tileMap.find(tile) != _tileMap.end()){ // already on the map
        return false;
    }
    else{ // not on the map yet
    }
    // add block to the board
    // when it is currently player 1's turn
    if(player == Block::Player::PLAYER1){
        _currentBlock = Block::create(player);
        _tileMap[tile] = player;
        checkBigTileForWin(tile.first, player);
        checkBigTileFull(tile.first);
    }
    // when it is currently player 2's turn
    else if(player == Block::Player::PLAYER2){
        _currentBlock = Block::create(player);
        _tileMap[tile] = player;
        checkBigTileForWin(tile.first, player);
        checkBigTileFull(tile.first);
    }
    
    BigTile* bigTile = _bigTileList[tile.first];
    SmallTile* smallTile = bigTile->getSmallTileList()[tile.second];
    _currentBlock->setPosition(Vec2(smallTile->getContentSize().width / 2.0, smallTile->getContentSize().height / 2.0));
    smallTile->addChild(_currentBlock);
    
    // reset available big tiles
    resetAvailableBigTiles(tile.second);

    return true;
}

bool Board::checkBigTileForWin(int bigTileNum, Block::Player player)
{
    // checks all 8 cases
    std::pair<int, int> tile0 = std::make_pair(bigTileNum, 0);
    std::pair<int, int> tile1 = std::make_pair(bigTileNum, 1);
    std::pair<int, int> tile2 = std::make_pair(bigTileNum, 2);
    std::pair<int, int> tile3 = std::make_pair(bigTileNum, 3);
    std::pair<int, int> tile4 = std::make_pair(bigTileNum, 4);
    std::pair<int, int> tile5 = std::make_pair(bigTileNum, 5);
    std::pair<int, int> tile6 = std::make_pair(bigTileNum, 6);
    std::pair<int, int> tile7 = std::make_pair(bigTileNum, 7);
    std::pair<int, int> tile8 = std::make_pair(bigTileNum, 8);
    BigTile* bigTile = _bigTileList[bigTileNum];
    bigTile->setDone(false);
    bigTile->getBlueBG()->setVisible(false);
    bigTile->getPinkBG()->setVisible(false);
    
    // row 1
    if((_tileMap.find(tile0) != _tileMap.end()) && (_tileMap.find(tile1) != _tileMap.end()) && (_tileMap.find(tile2) != _tileMap.end()))
    {
        if(_tileMap[tile0] == _tileMap[tile1] && _tileMap[tile1] ==  _tileMap[tile2]) {
            bigTile->setDone(true);
        }
    }
    // row 2
    if((_tileMap.find(tile3) != _tileMap.end()) && (_tileMap.find(tile4) != _tileMap.end()) && (_tileMap.find(tile5) != _tileMap.end()))
    {
        if(_tileMap[tile3] == _tileMap[tile4] && _tileMap[tile4] == _tileMap[tile5]) {
            bigTile->setDone(true);
        }
    }
    // row 3
    if((_tileMap.find(tile6) != _tileMap.end()) && (_tileMap.find(tile7) != _tileMap.end()) && (_tileMap.find(tile8) != _tileMap.end()))
    {
        if(_tileMap[tile6] == _tileMap[tile7] && _tileMap[tile7] == _tileMap[tile8]) {
            bigTile->setDone(true);
        }
    }
    // col 1
    if((_tileMap.find(tile0) != _tileMap.end()) && (_tileMap.find(tile3) != _tileMap.end()) && (_tileMap.find(tile6) != _tileMap.end()))
    {
        if(_tileMap[tile0] == _tileMap[tile3] && _tileMap[tile3] == _tileMap[tile6]) {
            bigTile->setDone(true);
        }
    }
    // col 2
    if((_tileMap.find(tile1) != _tileMap.end()) && (_tileMap.find(tile4) != _tileMap.end()) && (_tileMap.find(tile7) != _tileMap.end()))
    {
        if(_tileMap[tile1] == _tileMap[tile4] && _tileMap[tile4] == _tileMap[tile7]) {
            bigTile->setDone(true);
        }
    }
    // col 3
    if((_tileMap.find(tile2) != _tileMap.end()) && (_tileMap.find(tile5) != _tileMap.end()) && (_tileMap.find(tile8) != _tileMap.end()))
    {
        if(_tileMap[tile2] == _tileMap[tile5] && _tileMap[tile5] == _tileMap[tile8]) {
            bigTile->setDone(true);
        }
    }
    
    // diag 1
    if((_tileMap.find(tile0) != _tileMap.end()) && (_tileMap.find(tile4) != _tileMap.end()) && (_tileMap.find(tile8) != _tileMap.end()))
    {
        if(_tileMap[tile0] == _tileMap[tile4] && _tileMap[tile4] == _tileMap[tile8]) {
            bigTile->setDone(true);
        }
    }
    
    // diag 2
    if((_tileMap.find(tile2) != _tileMap.end()) && (_tileMap.find(tile4) != _tileMap.end()) && (_tileMap.find(tile6) != _tileMap.end()))
    {
        if(_tileMap[tile2] == _tileMap[tile4] && _tileMap[tile4] == _tileMap[tile6]) {
            bigTile->setDone(true);
        }
    }
    
    // change bg
    if(bigTile->getDone()){
        if(player == Block::Player::PLAYER1) {
            bigTile->getBlueBG()->setVisible(true);
        }
        else{
            bigTile->getPinkBG()->setVisible(true);
        }
        bigTile->setPlayerWon(player);
        return true;
    }
    return false;
}

bool Board::checkBigTileFull(int bigTileNum)
{
    std::pair<int, int> tile0 = std::make_pair(bigTileNum, 0);
    std::pair<int, int> tile1 = std::make_pair(bigTileNum, 1);
    std::pair<int, int> tile2 = std::make_pair(bigTileNum, 2);
    std::pair<int, int> tile3 = std::make_pair(bigTileNum, 3);
    std::pair<int, int> tile4 = std::make_pair(bigTileNum, 4);
    std::pair<int, int> tile5 = std::make_pair(bigTileNum, 5);
    std::pair<int, int> tile6 = std::make_pair(bigTileNum, 6);
    std::pair<int, int> tile7 = std::make_pair(bigTileNum, 7);
    std::pair<int, int> tile8 = std::make_pair(bigTileNum, 8);
    BigTile* bigTile = _bigTileList[bigTileNum];
    if((_tileMap.find(tile0) != _tileMap.end()) && (_tileMap.find(tile1) != _tileMap.end()) && (_tileMap.find(tile2) != _tileMap.end()) && (_tileMap.find(tile3) != _tileMap.end()) && (_tileMap.find(tile4) != _tileMap.end()) && (_tileMap.find(tile5) != _tileMap.end()) && (_tileMap.find(tile6) != _tileMap.end()) && (_tileMap.find(tile7) != _tileMap.end()) && (_tileMap.find(tile8) != _tileMap.end()))
    {
        bigTile->setDone(true);
        bigTile->setPlayerWon(Block::Player::NEITHER);
        return true;
    }
    return false;
}



bool Board::checkWin()
{
    // check all 8 cases
    // row 1
    if(_bigTileList[0]->getDone() && _bigTileList[1]->getDone() && _bigTileList[2]->getDone())
    {
        if(_bigTileList[0]->getPlayerWon() == _bigTileList[1]->getPlayerWon()  && _bigTileList[1]->getPlayerWon() == _bigTileList[2]->getPlayerWon()){
            return true;
        }
    }
    // row 2
    if(_bigTileList[3]->getDone() && _bigTileList[4]->getDone() && _bigTileList[5]->getDone())
    {
        if(_bigTileList[3]->getPlayerWon() == _bigTileList[4]->getPlayerWon() && _bigTileList[4]->getPlayerWon() == _bigTileList[5]->getPlayerWon()){
            return true;
        }
    }
    // row 3
    if(_bigTileList[6]->getDone() && _bigTileList[7]->getDone() && _bigTileList[8]->getDone())
    {
        if(_bigTileList[6]->getPlayerWon() == _bigTileList[7]->getPlayerWon() && _bigTileList[7]->getPlayerWon() == _bigTileList[8]->getPlayerWon()){
            return true;
        }
    }
    // col 1
    if(_bigTileList[0]->getDone() && _bigTileList[3]->getDone() && _bigTileList[6]->getDone())
    {
        if(_bigTileList[0]->getPlayerWon() == _bigTileList[3]->getPlayerWon() && _bigTileList[3]->getPlayerWon() == _bigTileList[6]->getPlayerWon()){
            return true;
        }
    }
    // col 2
    if(_bigTileList[1]->getDone() && _bigTileList[4]->getDone() && _bigTileList[7]->getDone())
    {
        if(_bigTileList[1]->getPlayerWon() == _bigTileList[4]->getPlayerWon() && _bigTileList[4]->getPlayerWon() == _bigTileList[7]->getPlayerWon()){
            return true;
        }
    }
    // col 3
    if(_bigTileList[2]->getDone() && _bigTileList[5]->getDone() && _bigTileList[8]->getDone())
    {
        if(_bigTileList[2]->getPlayerWon() == _bigTileList[5]->getPlayerWon() && _bigTileList[5]->getPlayerWon() == _bigTileList[8]->getPlayerWon()){
            return true;
        }
    }
    
    // diag 1
    if(_bigTileList[0]->getDone() && _bigTileList[4]->getDone() && _bigTileList[8]->getDone())
    {
        if(_bigTileList[0]->getPlayerWon() == _bigTileList[4]->getPlayerWon() && _bigTileList[4]->getPlayerWon() == _bigTileList[8]->getPlayerWon()){
            return true;
        }
    }
    
    // diag 2
    if(_bigTileList[2]->getDone() && _bigTileList[4]->getDone() && _bigTileList[6]->getDone())
    {
        if(_bigTileList[2]->getPlayerWon() == _bigTileList[4]->getPlayerWon() && _bigTileList[4]->getPlayerWon() == _bigTileList[6]->getPlayerWon()){
            return true;
        }
    }

    return false;
}

bool Board::checkDraw()
{
    int numOfTilesDone = 0;
    for(int i = 0; i < NUM_OF_TILES; i++)
    {
        BigTile* bigTile = _bigTileList[i];
        if(bigTile->getDone()){
            numOfTilesDone++;
        }
    }
    
    if(numOfTilesDone == NUM_OF_TILES)
    {
        return true;
    }
    return false;
}

void Board::undoMove(Block::Player player)
{
    // remove the block placed
    _currentBlock->removeFromParent();
    // remove from tile map
    std::map<std::pair<int, int>, Block::Player>::iterator it;
    it = _tileMap.find(_currentTile);
    _tileMap.erase(it);
    // reset current tile
    checkBigTileForWin(_currentTile.first, player);
    // reset available big tiles
    if(_tileMap.empty()){ // undo first move
        // put all big tiles in available big tile vector initially
        int numOfTiles = 9;
        for( int i = 0; i < numOfTiles; i++)
        {
            _availableBigTiles.push_back(i);
        }
        // then set the ones that are in the available big tile vector as visible
        for(auto it = _availableBigTiles.begin(); it != _availableBigTiles.end(); it++)
        {
            BigTile* bigTile = _bigTileList[(*it)];
            Sprite* yellowbg = bigTile->getYellowBG();
            yellowbg->setVisible(true);
        }
    }
    else{
        resetAvailableBigTiles(_currentTile.first);
    }
    return;
}