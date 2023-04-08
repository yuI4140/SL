#include "third-party/c_cb/os/window.h"
#include "Err.c"
#include "sl_funcs.c"
int main() {
  string WinName;
  OS_Window *win = OS_WindowCreate(200, 300, L"WIDNOW");
  OS_WindowShow(win);
  while (OS_WindowIsOpen(win)) {
  }
  if (!OS_WindowIsOpen(win)) {
    OS_WindowClose(win);
  }
}
