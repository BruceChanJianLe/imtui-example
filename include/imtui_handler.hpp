#pragma once
// Imtui
#include "imtui/imtui.h"
#include "imtui/imtui-impl-ncurses.h"

namespace tui_util
{
  class ImtuiHandler
  {
  public:
    ImtuiHandler();
    virtual ~ImtuiHandler();

    /**
     * \brief initialize ui, call before using
     */
    virtual void UIInit() final;

    /**
     * \brief Must be called before Update()
     */
    virtual void UINewFrame() final;

    /**
     * \brief Render your ui, must be called after Update()
     */
    virtual void UIRender() final;

    /**
     * \brief Render your ui, must be called after Update()
     */
    virtual bool UIOk() const final;

    /**
     * \brief Your implementation goes here!
     */
    void Update();

  private:
    /**
     * \brief This will be automatically called in destructor
     */
    virtual void UIShutdown() final;

    bool init_ui_;
    bool show_another_window_;
    ImVec4 clear_color_;
    ImGuiIO io_;
    ImTui::TScreen* screen_;
  };

} // tui_util

