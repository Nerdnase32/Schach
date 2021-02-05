
#include "Chess.h"

Chess::Chess()
{
  engine.init();
}

Chess::~Chess()
{
}

std::string Chess::processRequest(const std::string& entry)
{
  std::string result = "ERROR";

  Command command(entry);

  if (command.getType() == Type::COORD)
  {
    result = engine.processNewCoords(command.getCoord());
  }
  else if (command.getType() == Type::LOG)
  {
    engine.processLogFigures(command.getArgument());
  }
  else if (command.getType() == Type::EXIT)
  {
    processExit(EXIT_SUCCESS);
  }
  else
    std::cout << "unknown command type\n";

  return result;
}

void Chess::processExit(int exitCode)
{
  exit(exitCode);
}
