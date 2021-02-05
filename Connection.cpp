
#include "Connection.h"

Connection::Connection(HANDLE pipe, ulong threadId) : pipe(pipe), threadId(threadId)
{
}

Connection::~Connection()
{
}

void Connection::run()
{
  HANDLE hHeap = GetProcessHeap();
  TCHAR* pchRequest = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));
  TCHAR* pchReply = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));

  if (pipe == NULL)
  {
    printf("\nERROR - Pipe Server Failure:\n");
    printf("   InstanceThread got an unexpected NULL value in lpvParam.\n");
    printf("   InstanceThread exitting.\n");
    if (pchReply != NULL) HeapFree(hHeap, 0, pchReply);
    if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
    return;
  }

  if (pchRequest == NULL)
  {
    printf("\nERROR - Pipe Server Failure:\n");
    printf("   InstanceThread got an unexpected NULL heap allocation.\n");
    printf("   InstanceThread exitting.\n");
    if (pchReply != NULL) HeapFree(hHeap, 0, pchReply);
    return;
  }

  if (pchReply == NULL)
  {
    printf("\nERROR - Pipe Server Failure:\n");
    printf("   InstanceThread got an unexpected NULL heap allocation.\n");
    printf("   InstanceThread exitting.\n");
    if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
    return;
  }

  printf("InstanceThread created, receiving and processing messages.\n");


  for (;;)
  {
    ulong cbBytesRead = 0;
    BOOL fSuccess = ReadFile(pipe, pchRequest, BUFSIZE * sizeof(TCHAR), &cbBytesRead, NULL);

    if (!fSuccess || cbBytesRead == 0)
    {
      if (GetLastError() == ERROR_BROKEN_PIPE)
      {
        _tprintf(TEXT("InstanceThread: client disconnected.\n"));
      }
      else
      {
        _tprintf(TEXT("InstanceThread ReadFile failed, GLE=%d.\n"), GetLastError());
      }
      break;
    }

    wait();

    ulong cbReplyBytes = 0;
    getAnswerToRequest(pchRequest, pchReply, cbReplyBytes);

    ulong cbWritten = 0;
    fSuccess = WriteFile(pipe, pchReply, cbReplyBytes, &cbWritten, NULL);

    if (!fSuccess || cbReplyBytes != cbWritten)
    {
      _tprintf(TEXT("InstanceThread WriteFile failed, GLE=%d.\n"), GetLastError());
      break;
    }
  }

  FlushFileBuffers(pipe);
  DisconnectNamedPipe(pipe);
  CloseHandle(pipe);

  HeapFree(hHeap, 0, pchRequest);
  HeapFree(hHeap, 0, pchReply);

  printf("InstanceThread exiting.\n");
}

void Connection::getAnswerToRequest(LPTSTR pchRequest, LPTSTR pchReply, ulong& pchBytes)
{
  _tprintf(TEXT("Client Request String:\"%s\"\n"), pchRequest);

  if (FAILED(StringCchCopy(pchReply, BUFSIZE, reply)))
  {
    pchBytes = 0;
    pchReply[0] = 0;
    printf("StringCchCopy failed, no outgoing message.\n");
    return;
  }
  pchBytes = (lstrlen(pchReply) + 1) * sizeof(TCHAR);
}