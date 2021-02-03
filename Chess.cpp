
#include "Chess.h"

Chess::Chess()
{
  engine.init();
}

Chess::~Chess()
{
}

void Chess::run()
{
  for (;;)
  {
    std::cout << engine.getOutput();

    std::string entry;
    std::getline(std::cin, entry);

    processRequest(entry);
  }
}

void Chess::processRequest(const std::string& entry)
{
  Command command(entry);

  if (command.getType() == Type::COORD)
  {
    engine.processNewCoords(command.getCoord());
  }
  else if (command.getType() == Type::LOG)
  {
    engine.processLogFigures(command.getArgument());
  }
  else if (command.getType() == Type::EXIT)
  {
    processExit();
  }
  else
    std::cout << "unknown command type\n";
}

void Chess::processExit(int exitCode)
{
  exit(exitCode);
}
