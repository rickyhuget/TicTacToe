#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;


class Player {
  public:
    string name;
    char mark;
    Player(string s, char c);
};

#endif