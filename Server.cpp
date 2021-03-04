
#include "Server.h"

Server::Server(Chess& chess) : chess(chess)
{
}

Server::~Server()
{
}

int Server::run(void)
{
  for (;;)
  {
    HANDLE pipe = openPipe(TEXT(PIPE_NAME));
    if (pipe)
    {
      printf("Client connected, creating a processing thread.\n");

      HANDLE heap = GetProcessHeap();
      LPTSTR pchRequest = (LPTSTR)HeapAlloc(heap, 0, BUFSIZE * sizeof(CHAR));
      LPTSTR pchReply   = (LPTSTR)HeapAlloc(heap, 0, BUFSIZE * sizeof(CHAR));

      for (;;)
      {
        DWORD cbBytesRead = 0;

        TCHAR pchRequest;
        BOOL fSuccess = ReadFile(pipe, &pchRequest, BUFSIZE * sizeof(CHAR), &cbBytesRead, NULL);

        if (!fSuccess || cbBytesRead == 0)
        {
          if (GetLastError() == ERROR_BROKEN_PIPE)
            _tprintf(TEXT("Client disconnected.\n"));
          else
            _tprintf(TEXT("ReadFile failed, GLE=%d.\n"), GetLastError());

          break;
        }

        WSTRING reply = chess.processRequest(&pchRequest);

        DWORD cbReplyBytes = 0;
        convertReply(reply.c_str(), pchReply, cbReplyBytes);

        DWORD cbWritten = 0;
        fSuccess = WriteFile(pipe, pchReply, cbReplyBytes, &cbWritten, NULL);

        if (!fSuccess || cbReplyBytes != cbWritten)
        {
          _tprintf(TEXT("WriteFile failed, GLE=%d.\n"), GetLastError());
          break;
        }
      }

      FlushFileBuffers(pipe);
      DisconnectNamedPipe(pipe);
      CloseHandle(pipe);

      HeapFree(heap, 0, pchRequest);
      HeapFree(heap, 0, pchReply);
    }
    else
      return -1;
  }

  return 0;
}

void Server::convertReply(const WSTRING& reply, LPTSTR pchReply, DWORD& pchBytes)
{
  if (FAILED(StringCchCopy(pchReply, BUFSIZE, reply.c_str())))
  {
    pchBytes = 0;
    pchReply[0] = 0;
    printf("StringCchCopy failed, no outgoing message.\n");
    return;
  }
  pchBytes = (lstrlen(pchReply) + 1) * sizeof(CHAR);
}

HANDLE Server::openPipe(LPCTSTR pipeName)
{
  _tprintf(TEXT("\nPipe Server awaiting client connection on %s\n"), pipeName);

  DWORD  openMode = PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT;
  HANDLE pipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, openMode, PIPE_UNLIMITED_INSTANCES, BUFSIZE, BUFSIZE, 0, NULL);

  if (pipe == INVALID_HANDLE_VALUE)
  {
    _tprintf(TEXT("CreateNamedPipe failed, GLE=%d.\n"), GetLastError());
    return nullptr;
  }

  ConnectNamedPipe(pipe, NULL);

  return pipe;
}