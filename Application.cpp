#include "Application.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::run()
{
}

std::string Application::get()
{
  std::string entry = queue.front();
  queue.pop();

  return entry;
}
