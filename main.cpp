#include "Game.h"
#include "Player.h"
#include "library.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  vector<Player> players;

  generatePlayers(players);
  Game game(players[0].name, players[1].name);
  beginTurns(game, players[0], players[1]);
  game.runEndState();
  game.display();
  promptMenu();
  
  return 0;
}