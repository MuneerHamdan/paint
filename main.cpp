#include <X11/Xlib.h>//learn
#include <xcb/xcb.h>//check later
#include <stdio.h>
#include <stdlib.h>
#include "paint.h"
int main(){
  Display *display = XOpenDisplay(NULL);
  if(!display){
    fprintf(stderr, "nodisplay\n");
    return 1;
  }
  int screen = DefaultScreen(display);
  Window window = XCreateSimpleWindow(
      display,
      RootWindow(display, screen),
      100, 100,
      500, 300,
      1,
      BlackPixel(display, screen),
      WhitePixel(display, screen)
      );
  GC gc = XCreateGC(display, window, 0, NULL);
  XStoreName(display, window, "c window");
  XSelectInput(display, window, ExposureMask | KeyPressMask);
  XMapWindow(display, window);
  XEvent event;
  while(1){
    XNextEvent(display, &event);
    if(event.type == KeyPress)
      break;
    if(event.type == Expose){
      XSetForeground(display, gc, 0xFF0000);
      XDrawPoint(display, window, gc, 50, 50);
      XFillRectangle(display, window, gc, 50, 50, 100, 100);
      XFlush(display);
    }
  }
  XDestroyWindow(display, window);
  XCloseDisplay(display);


  Color* color = makeColor(5, 5, 5);
  Point* point = makePoint(5, 5, color);


  free(color);
  free(point->color);
  free(point);


  return 0;
}
