
#include "Chess.h"

Chess::Chess()
{
  engine.init();
}

Chess::~Chess()
{
}

WSTRING Chess::processRequest(const WSTRING& entry)
{
  WSTRING result = L"ERROR";

  Command command(entry);

  if (command.getType() == Type::COORD)
  {
    result = engine.processNewCoords(command.getCoord());
  }
  else if (command.getType() == Type::INIT)
  {
    result = engine.processInitFigures(command.getArgument());
  }
  else if (command.getType() == Type::EXIT)
  {
    processExit(EXIT_SUCCESS);
  }
  else
    _tprintf(L"unknown command type\n");

  return result;
}

void Chess::processExit(int exitCode)
{
  exit(exitCode);
}
