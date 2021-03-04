
#include "Command.h"

Command::Command(const WSTRING& command) : command(command)
{
  encodeType();
  encodeArgument();
  encodeCoord();
}

Command::~Command()
{
}

void Command::encodeType()
{
  WSTRING typeStr = command;

  auto it = typeStr.find('-');
  if (it != WSTRING::npos)
    typeStr = typeStr.substr(0, it);

  if (Tool::toUpper(typeStr) == TYPE_EXIT || Tool::toUpper(typeStr) == TYPE_QUIT)
    type = Type::EXIT;
  else if (Tool::toUpper(typeStr) == TYPE_INIT)
    type = Type::INIT;
  else if (Tool::validFieldName(typeStr))
    type = Type::COORD;
}

void Command::encodeArgument()
{
  WSTRING optionStr = command;

  auto it = optionStr.find('-');
  if (it != WSTRING::npos)
    optionStr = optionStr.substr(it);

  if (optionStr == OPT_ONLY_MOVE)
    arg = Argument::ONLY_MOVED;
}

void Command::encodeCoord()
{
  WSTRING coordStr = command;

  auto it = coordStr.find('-');
  if (it != WSTRING::npos)
    coordStr = coordStr.substr(0, it);

  if (Tool::validFieldName(coordStr))
    coord = Tool::toCoord(coordStr);
}
