
#include "Field.h"
#include "Figur.h"

Field::Field(size_t x, size_t y)
{
  coord.x = x;
  coord.y = y;
}

Field::~Field()
{
}

void Field::setActiveFigur(FigurPtr activeFigur)
{
  if (activeFigur)
    activeFigur->setCoord(coord);

  this->activeFigur = activeFigur;
}

void Field::addAttacker(Figur* attacker)
{
  attackers[attacker->getColor()].insert(attacker);
}

void Field::removeAttacker(Figur* attacker)
{
  attackers[attacker->getColor()].erase(attacker);
}

bool Field::hasAttackers(Color color)
{
  Color oppoColor = Tool::toOppoColor(color);
  return attackers.find(oppoColor) != attackers.end() ? attackers[oppoColor].size() : false;;
}
