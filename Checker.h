
#ifndef CHECKER_H
#define CHECKER_H

#include "Figur.h"

class Checker
{
public:
  Checker(const FieldMat& board);
  ~Checker();

  bool checkPath(Coord origCoord, Coord targetCoord);
  bool checkMove(FigurPtr activeFigur, FieldPtr targetField, bool capture);
  bool checkCheck(Color color);

public:
  static bool checkCoord(Coord coord);

private:
  bool checkCheck(FieldPtr kingField);

private:
  const FieldMat& board;
};

#endif // !CHECKER_H