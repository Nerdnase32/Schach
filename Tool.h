
#ifndef TOOL_H
#define TOOL_H

#include <stdlib.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h> 
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
#include <string>
#include "windows.h"
#include "defines.h"

struct Coord
{
  Coord();
  Coord(UINT x, UINT y);

  UINT x = 0;
  UINT y = 0;
};

class Tool
{
public:
  static UINT    toUint(TCHAR c)                           { return _ttoi(&c); }
  static UINT    letterToInt(TCHAR c)                      { return toUpper(c) - 64; }
  static TCHAR   toUpper(TCHAR c)                          { return toupper(c); }
  static BOOL    validFieldName(const WSTRING& fieldName);
  static WSTRING toUpper(const WSTRING& str);
  static WSTRING colorToString(Color color);
  static WSTRING coordToString(Coord coord);
  static Coord   toCoord(const WSTRING& name);
  static Color   toOppoColor(Color color);
};

#endif // !TOOL_H