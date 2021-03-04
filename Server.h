
#ifndef SERVER_H
#define SERVER_H

#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include "Windows.h"
#include "Chess.h"
#include <string>

#define BUFSIZE 1024
#define PIPE_NAME "\\\\.\\pipe\\Pipe"

class Server
{
public:
  Server(Chess& chess);
  ~Server();

  int run(void);

private:
  void convertReply(const WSTRING& reply, LPTSTR pchReply, DWORD& pchBytes);
  HANDLE openPipe(LPCTSTR pipeName);

private:
  Chess& chess;
};

#endif // !SERVER_H