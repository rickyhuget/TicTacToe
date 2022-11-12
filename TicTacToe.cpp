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
    char positions[3][3] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};

    void victoryDiagnostics() {diagnostics(positions);}

    void diagnostics(char (&p)[3][3]) {
      if ( (p[0][0] != ' ')  && (p[0][0] == p[1][0]) && (p[1][0] == p[2][0]) ) {winner = p[0][0];} // 1 left vertical
      if ( (p[0][1] != ' ')  && (p[0][1] == p[1][1]) && (p[1][1] == p[2][1]) ) {winner = p[1][0];} // 2 middle vertical
      if ( (p[0][2] != ' ')  && (p[0][2] == p[1][2]) && (p[1][2] == p[2][2]) ) {winner = p[2][0];} // 3 right vertical
      if ( (p[0][0] != ' ')  && (p[0][0] == p[0][1]) && (p[0][1] == p[0][2]) ) {winner = p[0][0];} // 4 top across
      if ( (p[1][0] != ' ')  && (p[1][0] == p[1][1]) && (p[1][1] == p[1][2]) ) {winner = p[1][0];} // 5 middle across
      if ( (p[2][0] != ' ')  && (p[2][0] == p[2][1]) && (p[2][1] == p[2][2]) ) {winner = p[2][0];} // 6 bottom across
      if ( (p[0][0] != ' ')  && (p[0][0] == p[1][1]) && (p[1][1] == p[2][2]) ) {winner = p[0][0];} // 7 top-left to bottom right
      if ( (p[2][0] != ' ')  && (p[2][0] == p[1][1]) && (p[1][1] == p[0][2]) ) {winner = p[2][0];} // 8 bottom-right to top left
    }

  public:

    void markPosition(int r, int c, char mark) {positions[r][c] = mark;}

    bool vacant(int row, int column) {
      if (positions[row][column] == ' ') {return true;}
      return false;
    }

    bool tieState() {
      for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
          if (vacant(i, j)) {return false;}
          }
      }   
      return true;
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
      cout << endl;
      cout << "     " << '0'             << "     " << '1'             << "     " << '2'                       << endl << endl;
      cout << " 0   " << positions[0][0] << "  |  " << positions[0][1] << "  |  " << positions[0][2] << "   0" << endl << endl;
      cout << " 1   " << positions[1][0] << "  |  " << positions[1][1] << "  |  " << positions[1][2] << "   1" << endl << endl;
      cout << " 2   " << positions[2][0] << "  |  " << positions[2][1] << "  |  " << positions[2][2] << "   2" << endl << endl;
      cout << "     " << '0'             << "     " << '1'             << "     " << '2'                       << endl << endl;
    }
};

void promptMenu() {
  char quit;
  cout << "Press any key to quit." << endl;
  cin >> quit;
}

void playerTurn(GameState &game, Player &player) {
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

void beginTurns(GameState& g, Player& pX, Player& pO) {
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

int main() {
  GameState game;
  vector<Player> players;

  generatePlayers(players);
  beginTurns(game, players[0], players[1]);
  game.runEndState(players[0], players[1]);
  game.display();
  promptMenu();
  
  return 0;
}