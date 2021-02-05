
#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include "Windows.h"
#include "Thread.h"

#define BUFSIZE 512

class Connection : public Thread
{
public:
  Connection(HANDLE lpvParam, ulong threadId);
  ~Connection();

private:
  void run();
  void getAnswerToRequest(LPTSTR pchRequest, LPTSTR pchReply, ulong& pchBytes);

private:
  LPTSTR reply = nullptr;
  ulong threadId;
  HANDLE pipe;
};

#endif // !CONNECTION_H
