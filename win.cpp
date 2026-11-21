#include <X11/Xlib.h>
#include "win.h"
Win::Win(Display* display, int screen){
  m_win = XCreateSimpleWindow( 
      display, 
      RootWindow(display, screen), 
      100, 100, 
      500, 300, 
      1, 
      BlackPixel(display, screen), 
      BlackPixel(display, screen)
//      WhitePixel(display, screen) 
      );
  m_gc = XCreateGC(display, m_win, 0, NULL);
  XStoreName(display, m_win, "window");
//  XSelectInput(display, m_win, ExposureMask | KeyPressMask);
  XSelectInput(display, m_win, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);
  XMapWindow(display, m_win);
}
Window* Win::getwin(){
  return &m_win;
}
GC* Win::getgc(){
  return &m_gc;
}
