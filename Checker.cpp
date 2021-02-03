
#include "Checker.h"

Checker::Checker(const FieldMat& board) : board(board)
{
}

Checker::~Checker()
{
}

bool Checker::checkCoord(Coord coord)
{
  return coord.x >= 0 && coord.x < 8 && coord.y >= 0 && coord.y < 8;
}

bool Checker::checkCheck(PlayerPtr activePlayer, PlayerPtr inactivePlayer)
{
  KingPtr king = inactivePlayer->getKing();
  Coord coord = king->getCoord();
  if (checkCoord(coord))
  {
    FieldPtr kingField = board[coord.x][coord.y];
    return checkCheck(activePlayer, kingField);
  }

  return false;
}

bool Checker::checkCheck(PlayerPtr activePlayer, FieldPtr kingField)
{
  for (FigurPtr figur : activePlayer->getFigures())
  {
    const FieldSet& attackedFields = figur->getAttackedFields();
    if (attackedFields.find(kingField) != attackedFields.end())
    {
      std::cout << Tool::colorToString(Tool::toOppoColor(activePlayer->getColor())) << " checked by " << figur->getName() << "\n";
      return true;
    }
  }

  return false;
}
