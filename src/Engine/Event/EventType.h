#pragma once

namespace Engine {

enum class EventType {
  None,

  KeyDown,
  KeyUp,

  MouseMove,
  MouseDown,
  MouseUp,
  MouseWheel,

  WindowClose,
  WindowResize,
  WindowFocus,
  WindowLostFocus
};

}
