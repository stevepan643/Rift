#pragma once

#include "utils/app/Application.h"
#include "utils/log/Logger.h"

extern Rift::Application *Rift::CreateApplication();

int main(int argc, char **argv) {
  Rift::Log::Init();

  RF_CORE_TRACE("Test Trace");
  RF_CORE_DEBUG("Test Debug");
  RF_CORE_INFO("Test Info");
  RF_CORE_WARN("Test Warn");
  RF_CORE_ERROR("Test Error");

  auto app = Rift::CreateApplication();
  app->Run();

  delete app;
}
