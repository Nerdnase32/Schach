
#include "Tool.h"

Coord::Coord()
{
}

Coord::Coord(size_t x, size_t y) : x(x), y(y)
{
}

bool Tool::validFieldName(const std::string& fieldName)
{
  bool result = false;

  if (fieldName.length() == 2)
  {
    int x = letterToInt(fieldName[0]);
    int y = atoi(&fieldName[1]);

    result = x > 0 && x <= 8 && y > 0 && y <= 8;
  }

  return result;
}

std::string Tool::toUpper(const std::string& str)
{
  std::string upperStr;
  for (auto c : str)
    upperStr += toupper(c);

  return upperStr;
}

std::string Tool::ltrim(std::string& str)
{
  str.erase(str.begin(), std::find_if(str.begin(), str.end(),
    std::not1(std::ptr_fun<int, int>(std::isspace))));

  return str;
}

std::string Tool::rtrim(std::string& str)
{
  str.erase(std::find_if(str.rbegin(), str.rend(),
    std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());

  return str;
}

std::string Tool::trim(std::string& str)
{
  ltrim(str);
  rtrim(str);

  return str;
}

std::string Tool::colorToString(Color color)
{
  std::string result = "unknown";

  switch (color)
  {
  case Color::WHITE:
    result = "White";
    break;
  case Color::BLACK:
    result = "Black";
    break;
  }

  return result;
}

std::string Tool::coordToString(Coord coord)
{
  char c = (char)coord.y + 65;

  return c + std::to_string(coord.x + 1);
}

Coord Tool::toCoord(const std::string& name)
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
