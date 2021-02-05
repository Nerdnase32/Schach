
#ifndef SERVER_H
#define SERVER_H

#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include "Windows.h"
#include "Chess.h"

#define BUFSIZE 512
#define PIPE_NAME "\\\\.\\pipe\\Pipe"

typedef unsigned long ulong;

class Server
{
public:
  Server(Chess& chess);
  ~Server();

  int run(void);

private:
  void getAnswerToRequest(LPCTSTR reply, LPTSTR pchRequest, LPTSTR pchReply, ulong& pchBytes);

private:
  Chess& chess;
};

#endif // !SERVER_H