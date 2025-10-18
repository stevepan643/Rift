#pragma once

#include "utils/app/Application.h"
#include "utils/log/Logger.h"

extern Rift::Application *Rift::CreateApplication();

int main(int argc, char **argv) {
  Rift::Log::Init();
  auto app = Rift::CreateApplication();
  app->Run();

  delete app;
}
