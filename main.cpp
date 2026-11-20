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
  bool run = True;
  while(run){
    XGrabPointer(display,
        window,
        True,
        PointerMotionMask | ButtonPressMask | ButtonReleaseMask,
        GrabModeAsync,
        GrabModeAsync,
        None,
        None,
        CurrentTime);
    XAllowEvents(display,AsyncPointer, CurrentTime);
    XNextEvent(display, &event);
    if(event.type == KeyPress){
      printf("key press %d\n", event.xkey.keycode);
      switch(event.xkey.keycode){
        case(24):
          printf("q");
          run = False;
          break;
      }
    }
//    if(event.type == MotionNotify){
//      printf("hello2");
//      break;
//    }
    if(event.type == ButtonPress){
      printf("mouse press\n");
      XSetForeground(display, gc, 0x0000FF);
      XFillRectangle(display, window, gc, event.xbutton.x, event.xbutton.y, 100, 100);
      XFlush(display);
    }
    if(event.type == Expose){
      XSetForeground(display, gc, 0xFF0000);
      XDrawPoint(display, window, gc, 50, 50);
      XFillRectangle(display, window, gc, 0, 0, 100, 100);
      XSetForeground(display, gc, 0x00FF00);
      XFillRectangle(display, window, gc, 50, 0, 100, 100);
      XFlush(display);
    }
  }
  XDestroyWindow(display, window);
  XCloseDisplay(display);


  Color* color = makeColor(5, 5, 5);
  Point* point = makePoint(5, 5, color);


  free(color);
  free(point);


  return 0;
}
