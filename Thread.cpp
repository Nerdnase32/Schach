#include "Thread.h"

Thread::Thread()
{
}

Thread::~Thread()
{
  if (thread)
  {
    thread->join();
    delete thread;
  }
  thread = nullptr;
}

void Thread::lock()
{
  if (outsideLock == nullptr)
    outsideLock = new std::lock_guard<std::mutex>(mutex);
}

void Thread::unlock()
{
  if (outsideLock)
    delete outsideLock;
  outsideLock = nullptr;
}

void Thread::entryPoint()
{
  run();
}

void Thread::wait()
{
  std::unique_lock<std::mutex> lock(mutex);
  condition.wait(lock);
  lock.unlock();
}

void Thread::signal()
{
  condition.notify_one();
}

void Thread::start()
{
  thread = new std::thread(&Thread::entryPoint, this);
}

void Thread::join()
{
  if (thread)
    thread->join();
}