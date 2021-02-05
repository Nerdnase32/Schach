
#ifndef CHESS_H
#define CHESS_H

#include "Engine.h"
#include "Command.h"

class Chess
{
public:
  Chess();
  ~Chess();

  std::string processRequest(const std::string& entry);

private:
  void processExit(int exitCode);

private:
  Engine& engine = *Engine::getEngine();
};

#endif // !CHESS_H