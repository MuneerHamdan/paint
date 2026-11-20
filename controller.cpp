  Window controller = XCreateSimpleWindow(
      display,
      RootWindow(display, screen),
      100, 100,
      500, 300,
      1,
      BlackPixel(display, screen),
      WhitePixel(display, screen)
      );
  XStoreName(display, controller, "controller");
  XSelectInput(display, controller, ExposureMask | KeyPressMask);
  XMapWindow(display, controller);
  XDestroyWindow(display, controller);
