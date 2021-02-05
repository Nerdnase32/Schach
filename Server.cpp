
#include "Server.h"

Server::Server(Chess& chess) : chess(chess)
{
}

Server::~Server()
{
}

int Server::run(void)
{
  LPCTSTR lpszPipename = TEXT(PIPE_NAME);

  for (;;)
  {
    _tprintf(TEXT("\nPipe Server: Main thread awaiting client connection on %s\n"), lpszPipename);

    ulong  openMode = PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT;
    HANDLE pipe     = CreateNamedPipe(lpszPipename, PIPE_ACCESS_DUPLEX, openMode, PIPE_UNLIMITED_INSTANCES, BUFSIZE, BUFSIZE, 0, NULL);

    if (pipe == INVALID_HANDLE_VALUE)
    {
      _tprintf(TEXT("CreateNamedPipe failed, GLE=%d.\n"), GetLastError());
      return -1;
    }

    BOOL fConnected = ConnectNamedPipe(pipe, NULL) ? TRUE : GetLastError() == ERROR_PIPE_CONNECTED;

    if (fConnected)
    {
      printf("Client connected, creating a processing thread.\n");

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
        return -1;
      }

      if (pchRequest == NULL)
      {
        printf("\nERROR - Pipe Server Failure:\n");
        printf("   InstanceThread got an unexpected NULL heap allocation.\n");
        printf("   InstanceThread exitting.\n");
        if (pchReply != NULL) HeapFree(hHeap, 0, pchReply);
        return -1;
      }

      if (pchReply == NULL)
      {
        printf("\nERROR - Pipe Server Failure:\n");
        printf("   InstanceThread got an unexpected NULL heap allocation.\n");
        printf("   InstanceThread exitting.\n");
        if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
        return -1;
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

        std::string reply = chess.processRequest(pchRequest);

        ulong cbReplyBytes = 0;
        getAnswerToRequest(reply.c_str(), pchRequest, pchReply, cbReplyBytes);

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
    else
      CloseHandle(pipe);
  }

  return 0;
}

void Server::getAnswerToRequest(LPCTSTR reply, LPTSTR pchRequest, LPTSTR pchReply, ulong& pchBytes)
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