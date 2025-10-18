#include "spdlog/common.h"
#include "utils/log/Logger.h"
#include <utils/app/EntryPoint.h>

class Sandbox : public Rift::Application {
public:
  Sandbox() {
      RF_CORE_ERROR("Test Error");
  }
  ~Sandbox() {}
};

Rift::Application *Rift::CreateApplication() { return new Sandbox(); }
