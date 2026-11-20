#include <X11/Xlib.h>//learn
#include <xcb/xcb.h>//check later
#include <stdio.h>
#include <stdlib.h>
#include "paint.h"
#include "win.h"
int main()
{
  Display *display = XOpenDisplay(NULL);
  if(!display)
  {
    fprintf(stderr, "nodisplay\n");
    return 1;
  }
  int screen = DefaultScreen(display);
  Win win(display, screen);

  XEvent event;
  bool running = True;
  while(running)
  {
    XGrabPointer(display,
        *win.getwin(),
        True,
        PointerMotionMask | ButtonPressMask | ButtonReleaseMask,
        GrabModeAsync,
        GrabModeAsync,
        None,
        None,
        CurrentTime);
    XAllowEvents(display,AsyncPointer, CurrentTime);
    XNextEvent(display, &event);

    switch(event.type)
    {
      case(ButtonPress):
        printf("mouse press: %d\n", event.xbutton.button);
        XSetForeground(display, *win.getgc(), 0xFF00FF);
        XFillRectangle(display, *win.getwin(), *win.getgc(), event.xbutton.x, event.xbutton.y, 100, 100);
        XFlush(display);
        break;
      case(Expose):
        XSetForeground(display, *win.getgc(), 0xFF0000);
        XDrawPoint(display, *win.getwin(), *win.getgc(), 50, 50);
        XFillRectangle(display, *win.getwin(), *win.getgc(), 0, 0, 100, 100);
        XSetForeground(display, *win.getgc(), 0x00FF00);
        XFillRectangle(display, *win.getwin(), *win.getgc(), 50, 0, 100, 100);
        XFlush(display);
        break;
      case(KeyPress):
        printf("key press %d\n", event.xkey.keycode);
        switch(event.xkey.keycode)
        {
          case(24):
            printf("q");
            running = False;
            break;
          case(57):
//            mkwindow();
            break;
        }
        break;
    }
    //    if(event.type == MotionNotify)
    //    {
    //      printf("hello2");
    //      break;
    //    }
  }
//  XFreeGC(display, cgc);
  XFreeGC(display, *win.getgc());
  XDestroyWindow(display, *win.getwin());
  XCloseDisplay(display);


  Color* color = makeColor(5, 5, 5);
  Point* point = makePoint(5, 5, color);


  free(color);
  free(point);


  return 0;
}
