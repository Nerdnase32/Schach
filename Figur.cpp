
#include "Figur.h"
#include "Engine.h"

Figur::Figur(Color color) : color(color)
{
  name = "Figur";
}

Figur::~Figur()
{
}

void Figur::setAttackers()
{
  clearAttackedField();
  setAttackedFields();
}

void Figur::clearAttackedField()
{
  const FieldMat& board = Engine::getEngine()->getBoard();
  for (const auto& row : board)
  {
     for (const auto& field : row)
      field->removeAttacker(this);
  }
}

void Figur::addAttacker(size_t x, size_t y)
{
  FieldPtr field = Engine::getEngine()->getField(Coord(x, y));
  if (field)
    field->addAttacker(this);
}

void Figur::setAttackersStraightFields()
{
  for (int x = coord.x + 1; x < 8; x++)
  {
    FieldPtr field = Engine::getEngine()->getField(Coord(x, coord.y));
    if (field)
    {
      addAttacker(x, coord.y);
      if (field->getActiveFigur())
        break;
    }
    else
      break;
  }
  for (int x = coord.x - 1; x > 0; x--)
  {
    FieldPtr field = Engine::getEngine()->getField(Coord(x, coord.y));
    if (field)
    {
      addAttacker(x, coord.y);
      if (field->getActiveFigur())
        break;
    }
    else
      break;
  }
  for (int y = coord.y + 1; y < 8; y++)
  {
    FieldPtr field = Engine::getEngine()->getField(Coord(coord.x, y));
    if (field)
    {
      addAttacker(coord.x, y);
      if (field->getActiveFigur())
        break;
    }
    else
      break;
  }
  for (int y = coord.y - 1; y > 0; y--)
  {
    FieldPtr field = Engine::getEngine()->getField(Coord(coord.x, y));
    if (field)
    {
      addAttacker(coord.x, y);
      if (field->getActiveFigur())
        break;
    }
    else
      break;
  }
}

void Figur::setAttackersDiagonalFields()
{
  for (int x = coord.x + 1, y = coord.y + 1; x < 8 && y < 8; x++, y++)
  {
    FieldPtr field = Engine::getEngine()->getField(Coord(x, y));
    if (field)
    {
      addAttacker(x, y);
      if (field->getActiveFigur())
        break;
    }
    else
      break;
  }
  for (int x = coord.x - 1, y = coord.y + 1; x > 0 && y < 8; x--, y++)
  {
    FieldPtr field = Engine::getEngine()->getField(Coord(x, y));
    if (field)
    {
      addAttacker(x, y);
      if (field->getActiveFigur())
        break;
    }
    else
      break;
  }
  for (int x = coord.x + 1, y = coord.y - 1; x < 8 && y > 0; x++, y--)
  {
    FieldPtr field = Engine::getEngine()->getField(Coord(x, y));
    if (field)
    {
      addAttacker(x, y);
      if (field->getActiveFigur())
        break;
    }
    else
      break;
  }
  for (int x = coord.x - 1, y = coord.y - 1; x > 0 && y > 0; x--, y--)
  {
    FieldPtr field = Engine::getEngine()->getField(Coord(x, y));
    if (field)
    {
      addAttacker(x, y);
      if (field->getActiveFigur())
        break;
    }
    else
      break;
  }
}

Pawn::Pawn(Color color) : Figur(color)
{
  name = "Pawn";
}

Pawn::~Pawn()
{
}

bool Pawn::validMove(Coord targetCoord, bool capture)
{
  bool result = false;

  if (!capture && coord.y == targetCoord.y)
  {
    int diff = targetCoord.x - coord.x;

    if (color == Color::WHITE)
      result = diff == 1 || (!moved && diff == 2);
    else if (color == Color::BLACK)
      result = diff == -1 || (!moved && diff == -2);
  }
  else if (capture && abs((int)(coord.y - targetCoord.y)) == 1)
  {
    int diff = targetCoord.x - coord.x;

    result = color == Color::WHITE ? diff == 1 : diff == -1;
  }

  return result;
}

void Pawn::setAttackedFields()
{
  size_t x = color == Color::WHITE ? coord.x + 1 : coord.x - 1;
  size_t y = coord.y + 1;

  addAttacker(x, y);

  y = coord.y - 1;
  addAttacker(x, y);
}

Knight::Knight(Color color) : Figur(color)
{
  name = "Knight";
  jump = true;
}

Knight::~Knight()
{
}

bool Knight::validMove(Coord targetCoord, bool capture)
{
  int diffX = targetCoord.x - coord.x;
  int diffY = targetCoord.y - coord.y;

  return (abs(diffX) == 2 && abs(diffY) == 1) || (abs(diffX) == 1 && abs(diffY) == 2);
}

void Knight::setAttackedFields()
{
  for (int i = 1; i <= 8; i++)
  {
    size_t x;
    size_t y;
    if (i <= 4)
    {
      x = i % 2 == 0 ? coord.x + 1 : coord.x - 1;
      y = i % 2 != 0 ? coord.y + 2 : coord.x - 2;
    }
    else
    {
      x = i % 2 == 0 ? coord.x + 2 : coord.x - 2;
      y = i % 2 != 0 ? coord.y + 1 : coord.x - 1;
    }

    addAttacker(x, y);
  }
}

Queen::Queen(Color color) : Figur(color)
{
  name = "Queen";
}

Queen::~Queen()
{
}

bool Queen::validMove(Coord targetCoord, bool capture)
{
  int diffX = coord.x - targetCoord.x;
  int diffY = coord.y - targetCoord.y;

  return coord.x == targetCoord.x || coord.y == targetCoord.y || abs(diffX) == abs(diffY);
}

void Queen::setAttackedFields()
{
  setAttackersStraightFields();
  setAttackersDiagonalFields();
}

King::King(Color color) : Figur(color)
{
  name = "King";
  invincible = true;
}

King::~King()
{
}

bool King::validMove(Coord targetCoord, bool capture)
{
  int diffX = coord.x - targetCoord.x;
  int diffY = coord.y - targetCoord.y;

  return abs(diffX) <= 1 && abs(diffY) <= 1;
}

void King::setAttackedFields()
{
  for (int i = 1; i <= 8; i++)
  {
    int x;
    int y;

    if (i <= 6)
    {
      x = i % 2 == 0 ? coord.x - 1 : coord.x + 1;
      y = i <= 3 ? coord.y - 1 : coord.y + 1;
    }
    else
    {
      x = 0;
      y = i % 2 == 0 ? coord.y + 1 : coord.y - 1;
    }
    addAttacker(x, y);
  }
}

Rook::Rook(Color color) : Figur(color)
{
  name = "Rook";
}

Rook::~Rook()
{
}

bool Rook::validMove(Coord targetCoord, bool capture)
{
  return coord.x == targetCoord.x || coord.y == targetCoord.y;
}

void Rook::setAttackedFields()
{
  setAttackersStraightFields();
}

Bishop::Bishop(Color color) : Figur(color)
{
  name = "Bishop";
}

Bishop::~Bishop()
{
}

bool Bishop::validMove(Coord targetCoord, bool capture)
{
  int diffX = coord.x - targetCoord.x;
  int diffY = coord.y - targetCoord.y;

  return abs(diffX) == abs(diffY);
}

void Bishop::setAttackedFields()
{
  setAttackersDiagonalFields();
}
