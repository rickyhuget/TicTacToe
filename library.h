#ifndef LIBRARY_H
#define LIBRARY_H
#include "Game.h"
#include "Player.h"
#include <string>
#include <vector>
using namespace std;

bool isValidPlacement(string s);
int convertToInt(char c);
void declareVictory(string s);
void declareTie();
void promptPlayer(string p);
void promptMenu();
void playerTurn(Game &game, Player &player);
void beginTurns(Game& g, Player& pX, Player& pO);
void generatePlayers(vector<Player> &g);

#endif