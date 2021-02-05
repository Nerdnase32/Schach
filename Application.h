#ifndef APPLICATION_H
#define APPLICATION_H

#include <queue>
#include <string>

class Application
{
public:
  Application();
  ~Application();

  void run();

  void add(std::string entry) { this->queue.push(entry); }
  std::string get();

private:
  std::queue<std::string> queue;
};

#endif // !APPLICATION_H