
#ifndef PLAYER_H
#define PLAYER_H

#include "Figur.h"

class Player;

typedef std::shared_ptr<Player> PlayerPtr;

class Player
{
public:
  Player(Color color);
  ~Player();

  bool        isCheck()                   const { return check; }
  Color       getColor()                  const { return color; }
  std::string getName()                   const { return Tool::colorToString(color); }

  void        setCheck(bool check)              { this->check = check; }
  void        addLostFigure(FigurPtr activeFigur)     { lostFigures.push_back(activeFigur); }

private:
  FigurVec lostFigures;

  bool   check  = false;
  double points = 0;
  Color  color  = Color::UNKNOWN;
}; 

#endif // !PLAYER_H