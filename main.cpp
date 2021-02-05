
#include "Chess.h"
#include "Server.h"

int main()
{
  Chess chess;

  Server server(chess);
  server.run();
}