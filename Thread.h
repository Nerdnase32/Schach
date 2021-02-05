
#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <mutex>
#include <condition_variable>

typedef unsigned long ulong;

class Thread
{
public:
  Thread();
  ~Thread();

  void lock();
  void unlock();
  void wait();
  void signal();
  void start();
  void join();

private:
  virtual void run() = 0;
  void entryPoint();

private:
  std::thread* thread = nullptr;
  std::mutex mutex;
  std::condition_variable condition;
  std::lock_guard<std::mutex>* outsideLock = nullptr;
};

#endif // !THREAD_H