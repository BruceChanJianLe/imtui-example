#include "imtui_handler.hpp"

int main (int argc, char *argv[])
{
  tui_util::ImtuiHandler handler;
  // GUI Loop
  handler.UIInit();
  while (handler.UIOk())
  {
    // Start a new frame for gui
    handler.UINewFrame();
    // Update gui content
    handler.Update();
    // Render gui
    handler.UIRender();
  }

  return 0;
}
