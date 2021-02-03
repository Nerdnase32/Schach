
#ifndef CHESS_H
#define CHESS_H

#include "Engine.h"
#include "Command.h"

class Chess
{
public:
  Chess();
  ~Chess();

  void run();
  void processRequest(const std::string& entry);

private:
  void processExit(int exitCode = EXIT_SUCCESS);

private:
  Engine& engine = *Engine::getEngine();
};

#endif // !CHESS_H