#include "Application.h"

#include "event/ApplicationEvent.h"
#include "utils/log/Logger.h"

namespace Rift {
    Application::Application() {}
    Application::~Application() {}
    void Application::Run() {
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication)) {
            RF_TRACE(e.ToString());
        }
        if (e.IsInCategory(EventCategoryInput)) {
            RF_TRACE(e.ToString());
        }

        while (true);
    }
}
