
#ifndef CHECKER_H
#define CHECKER_H

#include "Player.h"

class Checker
{
public:
  Checker(const FieldMat& board);
  ~Checker();

  bool checkPath(Coord origCoord, Coord targetCoord);
  bool checkMove(FigurPtr activeFigur, FieldPtr targetField, bool capture);
  bool checkCheck(PlayerPtr activePlayer, PlayerPtr inactivePlayer);

public:
  static bool checkCoord(Coord coord);

private:
  bool checkCheck(PlayerPtr activePlayer, FieldPtr kingField);

private:
  const FieldMat& board;
};

#endif // !CHECKER_H