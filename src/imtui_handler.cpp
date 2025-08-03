#include "imtui_handler.hpp"


namespace tui_util
{
  ImtuiHandler::ImtuiHandler()
    : screen_{nullptr}
  {
  }

  ImtuiHandler::~ImtuiHandler()
  {
    UIShutdown();
  }

  void ImtuiHandler::UIInit()
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    screen_ = ImTui_ImplNcurses_Init(true);
    ImTui_ImplText_Init();

    init_ui_ = true;
  }

  void ImtuiHandler::UINewFrame()
  {
    ImTui_ImplNcurses_NewFrame();
    ImTui_ImplText_NewFrame();
    ImGui::NewFrame();
  }

  void ImtuiHandler::UIRender()
  {
    ImGui::Render();
    ImTui_ImplText_RenderDrawData(ImGui::GetDrawData(), screen_);
    ImTui_ImplNcurses_DrawScreen();
  }

  bool ImtuiHandler::UIOk() const
  {
    return init_ui_;
  }

  void ImtuiHandler::Update()

  {
    if (init_ui_)
    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

      ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
      ImGui::Checkbox("Another Window", &show_another_window_);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3("clear color", (float*)&clear_color_); // Edit 3 floats representing a color

      if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
      {
        counter++;
      }
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io_.Framerate, io_.Framerate);
      ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window_)
    {
      ImGui::Begin("Another Window", &show_another_window_);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me"))
      {
        show_another_window_ = false;
      }
      ImGui::End();
    }
  }

  void ImtuiHandler::UIShutdown()
  {
    ImTui_ImplText_Shutdown();
    ImTui_ImplNcurses_Shutdown();
  }

} // tui_util
