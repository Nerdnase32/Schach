
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

  bool        isCheck()                     const { return check; }
  Color       getColor()                    const { return color; }
  std::string getName()                     const { return Tool::colorToString(color); }
  FigurVec    getLostFigures()              const { return lostFigures; }
  FigurVec    getFigures()                  const { return figures; }
  KingPtr     getKing()                     const { return king; }

  void        setCheck(bool check)                { this->check = check; }
  void        setKing(KingPtr king)               { this->king = king; }
  void        addLostFigure(FigurPtr activeFigur) { this->lostFigures.push_back(activeFigur); }
  void        addFigure(FigurPtr figur)           { this->figures.push_back(figur); }

private:
  FigurVec lostFigures;
  FigurVec figures;
  KingPtr  king;

  bool   check  = false;
  double points = 0;
  Color  color  = Color::UNKNOWN;
}; 

#endif // !PLAYER_H