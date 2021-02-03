
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

bool Checker::checkPath(Coord origCoord, Coord targetCoord)
{
  size_t startX = std::min(origCoord.x, targetCoord.x);
  size_t endX   = std::max(origCoord.x, targetCoord.x);
  size_t startY = std::min(origCoord.y, targetCoord.y);
  size_t endY   = std::max(origCoord.y, targetCoord.y);

  if (startX == endX)
  {
    for (size_t y = startY + 1; y < endY; y++)
    {
      if (checkCoord(Coord(startX, y)))
      {
        if (board[startX][y]->getActiveFigur())
          return false;
      }
      else
        return false;
    }
  }
  else if (startY == endY)
  {
    for (size_t x = startX + 1; x < endX; x++)
    {
      if (checkCoord(Coord(x, startY)))
      {
        if (board[x][startY]->getActiveFigur())
          return false;
      }
      else
        return false;
    }
  }
  else if ((targetCoord.x - origCoord.x) / (targetCoord.y - origCoord.y) > 0)
  {
    for (size_t x = startX + 1, y = startY + 1; x < endX && y < endY; x++, y++)
    {
      if (checkCoord(Coord(x, y)))
      {
        if (board[x][y]->getActiveFigur())
          return false;
      }
      else
        return false;
    }
  }
  else
  {
    for (size_t x = startX + 1, y = endY - 1; x < endX && y > startY; x++, y--)
    {
      if (checkCoord(Coord(x, y)))
      {
        if (board[x][y]->getActiveFigur())
          return false;
      }
      else
        return false;
    }
  }
  return true;
}

bool Checker::checkMove(FigurPtr activeFigur, FieldPtr targetField, bool capture)
{
  bool result = false;

  if (activeFigur->validMove(targetField->getCoord(), capture))
  {
    if (activeFigur->canJump() || checkPath(activeFigur->getCoord(), targetField->getCoord()))
      result = true;
  }

  return result;
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
