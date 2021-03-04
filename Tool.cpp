
#include "Tool.h"

Coord::Coord()
{
}

Coord::Coord(UINT x, UINT y) : x(x), y(y)
{
}

BOOL Tool::validFieldName(const WSTRING& fieldName)
{
  BOOL result = false;

  if (fieldName.length() == 2)
  {
    INT x = letterToInt(fieldName[0]);
    INT y = UINT(fieldName[1]);

    result = x > 0 && x <= 8 && y > 0 && y <= 8;
  }

  return result;
}

WSTRING Tool::toUpper(const WSTRING& str)
{
  WSTRING upperStr;
  for (const auto& c : str)
    upperStr += toupper(c);

  return upperStr;
}

WSTRING Tool::colorToString(Color color)
{
  WSTRING result = TEXT("unknown");

  switch (color)
  {
  case Color::WHITE:
    result = TEXT("White");
    break;
  case Color::BLACK:
    result = TEXT("Black");
    break;
  }

  return result;
}

WSTRING Tool::coordToString(Coord coord)
{
  WCHAR x = WCHAR(coord.y + 65);
  WCHAR y = WCHAR(coord.x + 1);

  return WSTRING(1, x + y);
}

Coord Tool::toCoord(const WSTRING& name)
{
  Coord coord;

  if (name.length() == 2)
  {
    coord.x = Tool::toUint(name[1]) - 1;
    coord.y = Tool::letterToInt(name[0]) - 1;
  }

  return coord;
}

Color Tool::toOppoColor(Color color)
{
  switch (color)
  {
  case Color::WHITE:
    return Color::BLACK;
  case Color::BLACK:
      return Color::WHITE;
  default:
    return Color::UNKNOWN;
  }
}
