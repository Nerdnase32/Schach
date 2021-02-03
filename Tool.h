
#ifndef TOOL_H
#define TOOL_H

#include <stdlib.h>
#include <ctype.h>
#include <algorithm>
#include <functional>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <map>
#include "defines.h"

struct Coord
{
  Coord();
  Coord(size_t x, size_t y);

  size_t x = 0;
  size_t y = 0;
};

class Tool
{
public:
  static uint        toUint(char c)                               { return strtoul(&c, nullptr, 0); }
  static uint        letterToInt(char c)                          { return toUpper(c) - 64; }
  static char        toUpper(char c)                              { return toupper(c); }
  static bool        validFieldName(const std::string& fieldName);
  static std::string toUpper(const std::string& str);
  static std::string ltrim(std::string& str);
  static std::string rtrim(std::string& str);
  static std::string trim(std::string& str);
  static std::string colorToString(Color color);
  static std::string coordToString(Coord coord);
  static Coord       toCoord(const std::string& name);
  static Color       toOppoColor(Color color);
};

#endif // !TOOL_H