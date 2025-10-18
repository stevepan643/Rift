namespace Rift {
class Application {
public:
  Application();
  ~Application();

  void Run();
};

Application* CreateApplication();
} // namespace Rift
