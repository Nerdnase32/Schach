
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

  void updateFigures();

  bool        isCheck()                     const { return check; }
  Color       getColor()                    const { return color; }
  std::string getName()                     const { return Tool::colorToString(color); }
  KingPtr     getKing()                     const { return king; }

  const FigurSet& getLostFigures()          const { return lostFigures; }
  const FigurSet& getFigures()              const { return figures; }

  void        setCheck(bool check)                { this->check = check; }
  void        setKing(KingPtr king)               { this->king = king; }
  void        addLostFigure(FigurPtr activeFigur) { this->lostFigures.insert(activeFigur); }
  void        addFigure(FigurPtr figur)           { this->figures.insert(figur); }
  void        removeFigure(FigurPtr figur)        { this->figures.erase(figur); }

private:
  FigurSet lostFigures;
  FigurSet figures;
  KingPtr  king;

  bool   check  = false;
  double points = 0;
  Color  color  = Color::UNKNOWN;
}; 

#endif // !PLAYER_H