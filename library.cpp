#include "library.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


void declareVictory(string s) {cout << "\nGame over. " << s << " wins!" << endl;}

void declareTie() {cout << "\nGame over. It's a tie!" << endl;}

void promptPlayer(string p) {
  cout << p << "\'s turn. Pick a position.\nFirst number: row. Second number: column.\n(i.e. 00, 02, 10, 11, etc.): ";
}

bool isValidPlacement(string s) {
  if ( (s.length() == 2)              &&
       ('0' <= s[0]) && (s[0] <= '2') &&
       ('0' <= s[1]) && (s[1] <= '2')    ) {
    return true;
  }
  return false;
}

int convertToInt(char c) {return (c - 48);}

void promptMenu() {
  char quit;
  cout << "Press any letter to quit." << endl;
  cin >> quit;
}

void playerTurn(Game &game, Player &player) {
  string position;
  int row, column;
  game.display();
  promptPlayer(player.name);
  
  do {
    cin >> position;
    row = convertToInt(position[0]);
    column = convertToInt(position[1]);

    if (game.vacant(row, column)) {
      game.markPosition(row, column, player.mark);
      break;
    }
    else if (!isValidPlacement(position)) {
      cout << "Not a valid position. Please choose again." << endl;
    }
    else {
      cout << "That position is already occupied. Please choose again." << endl;
    }
    
  } while (true);
}

void beginTurns(Game& g, Player& pX, Player& pO) {
  do {
    playerTurn(g, pX);
    if (g.endState()) {break;}
    playerTurn(g, pO);
    if (g.endState()) {break;}
  } while (true);
}

void generatePlayers(vector<Player> &v) {
  string input;
  cout << "Enter player name for X's: ";
  cin >> input;
  v.push_back(Player(input, 'X'));
  cout << "Enter player name for O's: ";
  cin >> input;
  v.push_back(Player(input, 'O'));
}