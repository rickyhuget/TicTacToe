#ifndef GAME_H
#define GAME_H
#include <string>
using namespace std;

class Game {
  private:
    char winner = ' ';
    char positions[3][3] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    string playerX_name;
    string playerO_name;
    const char playerX_mark = 'X';
    const char playerO_mark = 'O';

    void victoryDiagnostics();
    void diagnostics(char (&p)[3][3]);

  public:
    Game(string p1, string p2);

    void markPosition(int r, int c, char mark);
    bool vacant(int row, int column);
    bool tieState();
    bool victoryState();
    bool endState();
    void runEndState();
    char getVictor();
    void display();
};

#endif