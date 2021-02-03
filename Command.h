
#ifndef COMMAND_H
#define COMMAND_H

#include "Tool.h"

class Command
{
public:
  Command(const std::string& command);
  ~Command();

  Type     getType()     { return type; }
  Argument getArgument() { return arg; }
  Coord    getCoord()    { return coord; }

private:
  void encodeType();
  void encodeArgument();
  void encodeCoord();

private:
  std::string command;

  Type     type = Type::UNKNOWN;
  Argument arg  = Argument::UNKNOWN;
  Coord    coord;
};

#endif // !COMMAND_H