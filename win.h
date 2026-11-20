#include <X11/Xlib.h>//learn
class Win{
  private:
    Window m_win;
    GC m_gc;
  public:
    Win(Display* display, int screen);
    Window* getwin();
    GC* getgc();
};
