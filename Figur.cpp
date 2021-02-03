
#include "Figur.h"
#include "Engine.h"

Figur::Figur(Color color) : color(color)
{
  name = "Figur";
}

Figur::~Figur()
{
}

void Figur::updateAttackedFields()
{
  clearAttackedField();
  setAttackedFields();
}

void Figur::clearAttackedField()
{
  attackedFields.clear();
}

bool Figur::validMove(FieldPtr targetField)
{
  return attackedFields.find(targetField) != attackedFields.end();
}

void Figur::addAttacker(size_t x, size_t y)
{
  FieldPtr field = Engine::getEngine()->getField(Coord(x, y));
  if (field)
    attackedFields.insert(field);
}

void Figur::setAttackersStraightFields()
{
  int coordX = (int)coord.x;
  int coordY = (int)coord.y;

  for (int x = coordX + 1; x < 8; x++)
  {
    FieldPtr field = Engine::getEngine()->getField(Coord(x, coordY));
    if (field)
    {
      addAttacker(x, coordY);
      if (field->getActiveFigur())
        break;
    }
    else
      break;
  }
  for (int x = coordX - 1; x > 0; x--)
  {
    FieldPtr field = Engine::getEngine()->getField(Coord(x, coordY));
    if (field)
    {
      addAttacker(x, coordY);
      if (field->getActiveFigur())
        break;
    }
    else
      break;
  }
  for (int y = coordY + 1; y < 8; y++)
  {
    FieldPtr field = Engine::getEngine()->getField(Coord(coordX, y));
    if (field)
    {
      addAttacker(coordX, y);
      if (field->getActiveFigur())
        break;
    }
    else
      break;
  }
  for (int y = coordY - 1; y > 0; y--)
  {
    FieldPtr field = Engine::getEngine()->getField(Coord(coordX, y));
    if (field)
    {
      addAttacker(coordX, y);
      if (field->getActiveFigur())
        break;
    }
    else
      break;
  }
}

void Figur::setAttackersDiagonalFields()
{
  int coordX = (int)coord.x;
  int coordY = (int)coord.y;

  for (int x = coordX + 1, y = coordY + 1; x < 8 && y < 8; x++, y++)
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
  for (int x = coordX - 1, y = coordY + 1; x >= 0 && y < 8; x--, y++)
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
  for (int x = coordX + 1, y = coordY - 1; x < 8 && y >= 0; x++, y--)
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
  for (int x = coordX - 1, y = coordY - 1; x >= 0 && y >= 0; x--, y--)
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

bool Pawn::validMove(FieldPtr targetField)
{
  bool result = false;

  

  if (targetField->getActiveFigur())
  {
    result = Figur::validMove(targetField);
  }
  else
  {
    Coord targetCoord = targetField->getCoord();
    int diff = (int)targetCoord.x - (int)coord.x;

    if (color == Color::WHITE)
      result = coord.y == targetCoord.y && diff == 1 || (!moved && diff == 2);
    else if (color == Color::BLACK)
      result = coord.y == targetCoord.y && diff == -1 || (!moved && diff == -2);
  }

  return result;
}

void Pawn::setAttackedFields()
{
  int x = color == Color::WHITE ? (int)coord.x + 1 : (int)coord.x - 1;
  int y = (int)coord.y + 1;

  addAttacker(x, y);

  y = (int)coord.y - 1;
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

void Knight::setAttackedFields()
{
  for (int i = 1; i <= 8; i++)
  {
    int x = (int)coord.x;
    int y = (int)coord.y;

    if (i <= 2)
    {
      x = i % 2 == 0 ? x + 1 : x - 1;
      y = i % 2 != 0 ? y + 2 : y - 2;
    }
    else if (i <= 4)
    {
      x = i % 2 == 0 ? x + 2 : x - 2;
      y = i % 2 != 0 ? y + 1 : y - 1;
    }
    else if (i <= 6)
    {
      x = i % 2 == 0 ? x + 1 : x - 1;
      y = i % 2 == 0 ? y + 2 : y - 2;
    }
    else 
    {
      x = i % 2 == 0 ? x + 2 : x - 2;
      y = i % 2 == 0 ? y + 1 : y - 1;
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

void King::setAttackedFields()
{
  int coordX = (int)coord.x;
  int coordY = (int)coord.y;

  for (int x = coordX - 1; x <= coordX + 1; x++)
  {
    for (int y = coordY - 1; y <= coordY + 1; y++)
    {
      if (x != coordX || y != coordY)
        addAttacker(x, y);
    }
  }
}

Rook::Rook(Color color) : Figur(color)
{
  name = "Rook";
}

Rook::~Rook()
{
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

void Bishop::setAttackedFields()
{
  setAttackersDiagonalFields();
}
