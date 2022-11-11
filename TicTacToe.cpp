#include <iostream>
#include <string>
#include <vector>
using namespace std;


void declareVictory(string s) {
  cout << "\nGame over. " << s << " wins!" << endl;
}

void declareTie() {
  cout << "\nGame over. It's a tie!. Nobody wins." << endl;
}

void promptPlayer(string p) {
  cout << p << "\'s turn. Pick a position (i.e. a1): ";
}

bool isValidMark(string s) {
  if ( (s == "a1") || (s == "a2") || (s == "a3") ||
       (s == "b1") || (s == "b2") || (s == "b3") ||
       (s == "c1") || (s == "c2") || (s == "c3") ) {
    return true;
  }
  return false;
}

class Player {
  public:
    string name;
    char mark;

    Player(string s, char c) {
      name = s;
      mark = c;
    }
};

class GameState {
  private:
    char winner = ' ';
    char pos_a1 = ' ';
    char pos_b1 = ' ';
    char pos_c1 = ' ';
    char pos_a2 = ' ';
    char pos_b2 = ' ';
    char pos_c2 = ' ';
    char pos_a3 = ' ';
    char pos_b3 = ' ';
    char pos_c3 = ' ';
    vector<string> occupiedPositions;

    void victoryDiagnostics() {
      if ( (pos_a1 != ' ') && (pos_a1 == pos_a2) && (pos_a2 == pos_a3) ) {winner = pos_a1;} // 1
      if ( (pos_b1 != ' ') && (pos_b1 == pos_b2) && (pos_b2 == pos_b3) ) {winner = pos_b1;} // 2
      if ( (pos_c1 != ' ') && (pos_c1 == pos_c2) && (pos_c2 == pos_c3) ) {winner = pos_c1;} // 3
      if ( (pos_a1 != ' ') && (pos_a1 == pos_b1) && (pos_b1 == pos_c1) ) {winner = pos_a1;} // 4
      if ( (pos_a2 != ' ') && (pos_a2 == pos_b2) && (pos_b2 == pos_c2) ) {winner = pos_a2;} // 5
      if ( (pos_a3 != ' ') && (pos_a3 == pos_b3) && (pos_b3 == pos_c3) ) {winner = pos_a3;} // 6
      if ( (pos_a1 != ' ') && (pos_a1 == pos_b2) && (pos_b2 == pos_c3) ) {winner = pos_a1;} // 7
      if ( (pos_a3 != ' ') && (pos_a3 == pos_b2) && (pos_b2 == pos_c1) ) {winner = pos_a1;} // 8
    }

  public:
    void markPosition_a1(char mark) {pos_a1 = mark;}
    void markPosition_a2(char mark) {pos_a2 = mark;}
    void markPosition_a3(char mark) {pos_a3 = mark;}
    void markPosition_b1(char mark) {pos_b1 = mark;}
    void markPosition_b2(char mark) {pos_b2 = mark;}
    void markPosition_b3(char mark) {pos_b3 = mark;}
    void markPosition_c1(char mark) {pos_c1 = mark;}
    void markPosition_c2(char mark) {pos_c2 = mark;}
    void markPosition_c3(char mark) {pos_c3 = mark;}

    void markPosition(string position, char mark) {
      if      (position == "a1") {markPosition_a1(mark);}
      else if (position == "a2") {markPosition_a2(mark);}
      else if (position == "a3") {markPosition_a3(mark);}
      else if (position == "b1") {markPosition_b1(mark);}
      else if (position == "b2") {markPosition_b2(mark);}
      else if (position == "b3") {markPosition_b3(mark);}
      else if (position == "c1") {markPosition_c1(mark);}
      else if (position == "c2") {markPosition_c2(mark);}
      else if (position == "c3") {markPosition_c3(mark);}
      else {cout << "Not a valid position. Please choose again." << endl; return;}
    }

    void markPositionOccupied(string s) {
      occupiedPositions.push_back(s);
    }

    bool isOccupied(string s) {
      for (int i = 0; i < occupiedPositions.size(); i++) {
        if (s == occupiedPositions[i]) {return true;}
      }
      return false;
    }

    bool tieState () {
      if (occupiedPositions.size() >= 9) {return true;}
      return false;
    }

    bool victoryState() {
      if (winner == 'X' || winner == 'O') {return true;} return false;
    }

    bool endState() {
      victoryDiagnostics();
      if (victoryState() || tieState()) {return true;} return false;
    }

    void runEndState(Player p1, Player p2) {
      if (winner == p1.mark) {declareVictory(p1.name); return;}
      else if (winner == p2.mark) {declareVictory(p2.name); return;}
      else if (tieState()) {declareTie();}
      else {cout << "ERROR IN END STATE." << endl;}
      return;
    }

    char getVictor() {return winner;}

    void display() {
      cout << "\t    " << 'A'    << "     " << 'B'    << "     " << 'C'    << endl << endl;
      cout << "\t1   " << pos_a1 << "  |  " << pos_b1 << "  |  " << pos_c1 << "   1" << endl << endl;
      cout << "\t2   " << pos_a2 << "  |  " << pos_b2 << "  |  " << pos_c2 << "   2" << endl << endl;
      cout << "\t3   " << pos_a3 << "  |  " << pos_b3 << "  |  " << pos_c3 << "   3" << endl << endl;
      cout << "\t    " << 'A'    << "     " << 'B'    << "     " << 'C'             << endl << endl;
    }

    
};

void playerTurn(GameState &game, Player &player) {
  string position;
  game.display();
  promptPlayer(player.name);
  
  do {
    cin >> position;
    if (!game.isOccupied(position)) {
      game.markPosition(position, player.mark);
    }
    else {
      cout << "That position is already occupied. Please choose again." << endl;
    }
  } while (!isValidMark(position) || game.isOccupied(position));

  game.markPositionOccupied(position);
}

int main() {
  GameState game;
  string input;

  cout << "Enter player name for X's: ";
  cin >> input;
  Player player_X(input, 'X');
  cout << endl;
  cout << "Enter player name for O's: ";
  cin >> input;
  Player player_O(input, 'O');
  cout << endl;

  do {
    playerTurn(game, player_X);
    if (game.endState()) {break;}
    playerTurn(game, player_O);
    if (game.endState()) {break;}
  } while (true);

  game.runEndState(player_X, player_O);
  game.display();
  
  char quit;
  cout << "Press 'q' to quit." << endl;
  cin >> quit;

  if (quit == 'q') {return 0;}
  
  return 0;
}