#include "Game.h"
#include "library.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Game::Game(string p1, string p2) {
  playerX_name = p1;
  playerO_name = p2;
}
  
void Game::victoryDiagnostics() {diagnostics(positions);}

void Game::diagnostics(char (&p)[3][3]) {
  if ( (p[0][0] != ' ')  && (p[0][0] == p[1][0]) && (p[1][0] == p[2][0]) ) {winner = p[0][0];} // 1 left vertical
  if ( (p[0][1] != ' ')  && (p[0][1] == p[1][1]) && (p[1][1] == p[2][1]) ) {winner = p[1][0];} // 2 middle vertical
  if ( (p[0][2] != ' ')  && (p[0][2] == p[1][2]) && (p[1][2] == p[2][2]) ) {winner = p[2][0];} // 3 right vertical
  if ( (p[0][0] != ' ')  && (p[0][0] == p[0][1]) && (p[0][1] == p[0][2]) ) {winner = p[0][0];} // 4 top across
  if ( (p[1][0] != ' ')  && (p[1][0] == p[1][1]) && (p[1][1] == p[1][2]) ) {winner = p[1][0];} // 5 middle across
  if ( (p[2][0] != ' ')  && (p[2][0] == p[2][1]) && (p[2][1] == p[2][2]) ) {winner = p[2][0];} // 6 bottom across
  if ( (p[0][0] != ' ')  && (p[0][0] == p[1][1]) && (p[1][1] == p[2][2]) ) {winner = p[0][0];} // 7 top-left to bottom right
  if ( (p[2][0] != ' ')  && (p[2][0] == p[1][1]) && (p[1][1] == p[0][2]) ) {winner = p[2][0];} // 8 bottom-right to top left
}

void Game::markPosition(int r, int c, char mark) {positions[r][c] = mark;}

bool Game::vacant(int row, int column) {
  if (positions[row][column] == ' ') {return true;}
  return false;
}

bool Game::tieState() {
  for (int i = 0; i <= 2; i++) {
    for (int j = 0; j <= 2; j++) {
      if (vacant(i, j)) {return false;}
      }
  }   
  return true;
}

bool Game::victoryState() {
  if (winner == 'X' || winner == 'O') {return true;} return false;
}

bool Game::endState() {
  victoryDiagnostics();
  if (victoryState() || tieState()) {return true;} return false;
}

void Game::runEndState() {
  if (winner == playerX_mark) {declareVictory(playerX_name); return;}
  else if (winner == playerO_mark) {declareVictory(playerO_name); return;}
  else if (tieState()) {declareTie();}
  else {cout << "ERROR IN END STATE." << endl;}
  return;
}

char Game::getVictor() {return winner;}

void Game::display() {
  cout << endl;
  cout << "     " << '0'             << "     " << '1'             << "     " << '2'                       << endl << endl;
  cout << " 0   " << positions[0][0] << "  |  " << positions[0][1] << "  |  " << positions[0][2] << "   0" << endl << endl;
  cout << " 1   " << positions[1][0] << "  |  " << positions[1][1] << "  |  " << positions[1][2] << "   1" << endl << endl;
  cout << " 2   " << positions[2][0] << "  |  " << positions[2][1] << "  |  " << positions[2][2] << "   2" << endl << endl;
  cout << "     " << '0'             << "     " << '1'             << "     " << '2'                       << endl << endl;
}