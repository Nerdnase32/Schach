
#include "Command.h"

Command::Command(const std::string& command) : command(command)
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
  std::string typeStr = command;

  auto it = typeStr.find('-');
  if (it != std::string::npos)
    typeStr = typeStr.substr(0, it);

  Tool::trim(typeStr);

  if (Tool::toUpper(typeStr) == TYPE_EXIT || Tool::toUpper(typeStr) == TYPE_QUIT)
    type = Type::EXIT;
  else if (Tool::toUpper(typeStr) == TYPE_LOG)
    type = Type::LOG;
  else if (Tool::validFieldName(typeStr))
    type = Type::COORD;
}

void Command::encodeArgument()
{
  std::string optionStr = command;

  auto it = optionStr.find('-');
  if (it != std::string::npos)
    optionStr = optionStr.substr(it);
    
  Tool::trim(optionStr);

  if (optionStr == OPT_ONLY_MOVE)
    arg = Argument::ONLY_MOVED;
}

void Command::encodeCoord()
{
  std::string coordStr = command;

  auto it = coordStr.find('-');
  if (it != std::string::npos)
    coordStr = coordStr.substr(0, it);

  Tool::trim(coordStr);

  if (Tool::validFieldName(coordStr))
    coord = Tool::toCoord(coordStr);
}
