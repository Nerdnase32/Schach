
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