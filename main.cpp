#include <unistd.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "paint.h"
#include "win.h"

void changecolor(Display* display, Win* win, int x){
  if (x < 100)
    XSetForeground(display, *win->getgc(), 0xFF0000);
  else if (x < 200)
    XSetForeground(display, *win->getgc(), 0xFF9900);
  else if (x < 300)
    XSetForeground(display, *win->getgc(), 0xFFFF00);
  else if (x < 400)
    XSetForeground(display, *win->getgc(), 0x00FF00);
  else if (x < 500)
    XSetForeground(display, *win->getgc(), 0x0099FF);
  else if (x < 600)
    XSetForeground(display, *win->getgc(), 0x0000FF);
  else if (x < 700)
    XSetForeground(display, *win->getgc(), 0x9900FF);
  else if (x < 800)
    XSetForeground(display, *win->getgc(), 0xFFFFFF);
  else if (x < 900)
    XSetForeground(display, *win->getgc(), 0x000000);
}

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

  while (running)
  {
    XNextEvent(display, &event);

    switch (event.type)
    {
      case ButtonPress:
        if (event.xbutton.button == Button1){
          holding = true;
          int x = event.xbutton.x;
          int y = event.xbutton.y;
          if(y < 50)
          {
            changecolor(display, &win, x);
          }
          else{
            XFillRectangle
              (
               display,
               *win.getwin(),
               *win.getgc(),
               event.xbutton.x,
               event.xbutton.y,
               10,
               10
              );
          }
          XFlush(display);
        }
        break;

      case ButtonRelease:
        if (event.xbutton.button == Button1)
          holding = false;
        break;

      case MotionNotify:
        if (holding)
        {
          int x = event.xmotion.x;
          int y = event.xmotion.y;

          if (y < 50)
          {
            changecolor(display, &win, x);
          }
          XFillRectangle(
              display,
              *win.getwin(),
              *win.getgc(),
              x - 5,
              y - 5,
              10,
              10
              );
        }

        XFlush(display);
        break;
      case KeyPress:
        if (XLookupKeysym(&event.xkey, 0) == XK_q)
          running = false;
        break;

      case Expose:
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
    }
  }
  //    usleep(100);


  //    if(event.type == MotionNotify)
  //    {
  //      printf("hello2");
  //      break;
  //    }
  XFreeGC(display, *win.getgc());
  XDestroyWindow(display, *win.getwin());
  XCloseDisplay(display);

  return 0;
}
