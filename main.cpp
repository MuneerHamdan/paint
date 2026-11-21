#include <unistd.h>
#include <X11/Xlib.h>
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

  bool holding = 0;

  while(running)
  {
    while(XPending(display))
    {
      XNextEvent(display, &event);
      if(event.type == ButtonPress && event.xbutton.button == Button1)
      {
        holding = 1;
      }
      if (event.type == ButtonRelease && event.xbutton.button == Button1)
      {
        holding = 0;
      }
    }
    if(holding)
    {
      printf("holding\n");
      if(event.xbutton.x > 0 && event.xbutton.x < 100 && event.xbutton.x > 0 && event.xbutton.y < 50)
      {
        XSetForeground(display, *win.getgc(), 0xFF0000);
      }
      else if(event.xbutton.x > 100 && event.xbutton.x < 200 && event.xbutton.x > 0 && event.xbutton.y < 50)
      {
        XSetForeground(display, *win.getgc(), 0xFF9900);
      }
      else if(event.xbutton.x > 200 && event.xbutton.x < 300 && event.xbutton.x > 0 && event.xbutton.y < 50)
      {
        XSetForeground(display, *win.getgc(), 0xFFFF00);
      }
      else if(event.xbutton.x > 300 && event.xbutton.x < 400 && event.xbutton.x > 0 && event.xbutton.y < 50)
      {
        XSetForeground(display, *win.getgc(), 0x00FF00);
      }
      else if(event.xbutton.x > 400 && event.xbutton.x < 500 && event.xbutton.x > 0 && event.xbutton.y < 50)
      {
        XSetForeground(display, *win.getgc(), 0x0099FF);
      }
      else if(event.xbutton.x > 500 && event.xbutton.x < 600 && event.xbutton.x > 0 && event.xbutton.y < 50)
      {
        XSetForeground(display, *win.getgc(), 0x0000FF);
      }
      else if(event.xbutton.x > 600 && event.xbutton.x < 700 && event.xbutton.x > 0 && event.xbutton.y < 50)
      {
        XSetForeground(display, *win.getgc(), 0x9900FF);
      }
      else if(event.xbutton.x > 700 && event.xbutton.x < 800 && event.xbutton.x > 0 && event.xbutton.y < 50)
      {
        XSetForeground(display, *win.getgc(), 0xFFFFFF);
      }
      else if(event.xbutton.x > 800 && event.xbutton.x < 900 && event.xbutton.x > 0 && event.xbutton.y < 50)
      {
        XSetForeground(display, *win.getgc(), 0x000000);
      }
      else
      {
        XFillRectangle(display, *win.getwin(), *win.getgc(), event.xbutton.x-5, event.xbutton.y-5, 10, 10);
        XFlush(display);
      }
    }
//    usleep(100);

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

    switch(event.type)
    {
      case(ButtonPress):
        printf("mouse press: %d\n", event.xbutton.button);
        break;
      case(Expose):
        //        XSetForeground(display, *win.getgc(), 0xFF0000);
        //        XDrawPoint(display, *win.getwin(), *win.getgc(), 20, 20);

        XSetForeground(display, *win.getgc(), 0x999999);
        XFillRectangle(display, *win.getwin(), *win.getgc(), 0, 0, 1000, 51);

        XSetForeground(display, *win.getgc(), 0xFF0000);
        XFillRectangle(display, *win.getwin(), *win.getgc(), 0, 0, 100, 50);

        XSetForeground(display, *win.getgc(), 0xFF9900);
        XFillRectangle(display, *win.getwin(), *win.getgc(), 100, 0, 100, 50);

        XSetForeground(display, *win.getgc(), 0xFFFF00);
        XFillRectangle(display, *win.getwin(), *win.getgc(), 200, 0, 100, 50);

        XSetForeground(display, *win.getgc(), 0x00FF00);
        XFillRectangle(display, *win.getwin(), *win.getgc(), 300, 0, 100, 50);

        XSetForeground(display, *win.getgc(), 0x0099FF);
        XFillRectangle(display, *win.getwin(), *win.getgc(), 400, 0, 100, 50);

        XSetForeground(display, *win.getgc(), 0x0000FF);
        XFillRectangle(display, *win.getwin(), *win.getgc(), 500, 0, 100, 50);

        XSetForeground(display, *win.getgc(), 0x9900FF);
        XFillRectangle(display, *win.getwin(), *win.getgc(), 600, 0, 100, 50);

        XSetForeground(display, *win.getgc(), 0xFFFFFF);
        XFillRectangle(display, *win.getwin(), *win.getgc(), 700, 0, 100, 50);

        XSetForeground(display, *win.getgc(), 0x000000);
        XFillRectangle(display, *win.getwin(), *win.getgc(), 800, 0, 100, 50);

        XSetForeground(display, *win.getgc(), 0xFFFFFF);
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
  XFreeGC(display, *win.getgc());
  XDestroyWindow(display, *win.getwin());
  XCloseDisplay(display);

  return 0;
}
